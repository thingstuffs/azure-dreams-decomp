#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_8017313C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017313C_0;   /* arg0 in update_entity_dimming_and_brightness */

extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_801737C4(void *, void *, void *, void *);

extern u8 D_80170E9C[];
extern u8 D_80174F00[];

/* Updates entity dimming, status behavior, and brightness recovery. */
void update_entity_dimming_and_brightness(S_8017313C_0 *controller, void *context, SpriteFrameState *sprite, ActorRecord *entity)
{
    s32 entity_flags;
    u16 fade_ticks;
    s32 state;
    u8 shade;

    state = controller->unk_9B;
    switch (state) {
    case 0:
        shade = sprite->color.c.b - 0xC;
        sprite->color.c.b = shade;
        sprite->color.c.g = shade;
        sprite->color.c.r = shade;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = D_80174F00;
        sprite->color.c.b = 0x40;
        sprite->color.c.g = 0x40;
        sprite->color.c.r = 0x40;
        select_sprite_entry(sprite,
            (*(u8 **)&sprite->frameTable)[
                ((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        {
            u8 next_state = controller->unk_9B + 1;

            controller->unk_9B = next_state;
            return;
        }

    case 1:
        if ((get_entity_effect_value(entity, 1) << 16) == 0) {
            if (sprite->flags & 0x8000) {
                s32 cleared_flags;

                sprite->color.c.b = 0x80;
                sprite->color.c.g = 0x80;
                sprite->color.c.r = 0x80;
                cleared_flags = entity->flags1C & 0xEFFFFFFF;
                entity->flags1C = cleared_flags & ~0x200;
                controller->unk_8C = D_80170E9C;
                return;
            }
        } else {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }
            if (entity->unk_64 != 0) {
                if (begin_ready_actor_directional_action(controller, context, sprite, 0) != 0) {
                    return;
                }
            }
            if (entity->mp == 0) {
                if (g_dungeon_status.flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(controller, context, sprite, entity);
                return;
            }
            if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
                return;
            }
            entity_flags = entity->flags1C;
            if (entity_flags & 0x100) {
                begin_pushed_actor_move(controller, context, sprite, entity);
                return;
            }
            if (entity_flags & 0x80000) {
                begin_actor_move_to_target_facing(controller, context, sprite, entity);
                func_801737C4(controller, context, sprite, entity);
                return;
            }
            if (entity->pending_turn_updates == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
                ActorRecord *owner = primary_actor_record;

                if ((check_entity_relation(entity,
                        (u8 *)owner->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_mp(entity);
            on_actor_status_updated(entity);
            if ((get_entity_effect_value(entity, 1) << 16) != 0) {
                TileObject *origin = &reference_tile_object;
                s8 tile = *(s8 *)&sprite->unk_26;

                if (((tile == origin->room_index) && (tile >= 0)) ||
                    ((s16)get_tile_chebyshev_distance(origin, sprite) < 2)) {
                    if (!(generate_random_value() & 7)) {
                        clear_slots_of_type(entity, 1);
                    }
                }
            }
            if ((get_entity_effect_value(entity, 1) << 16) != 0) {
                return;
            }

            if (sprite->flags & 0x8000) {
                s32 cleared_flags;

                sprite->color.c.b = 0x80;
                sprite->color.c.g = 0x80;
                sprite->color.c.r = 0x80;
                cleared_flags = entity->flags1C & 0xEFFFFFFF;
                entity->flags1C = cleared_flags & ~0x200;
                controller->unk_8C = D_80170E9C;
                return;
            }
        }
        {

            g_dungeon_status.activity_counts.parts.pending_action_count++;
        }
        controller->unk_96 = 6;
        {
            u8 next_state = controller->unk_9B + 1;

            controller->unk_9B = next_state;
            return;
        }

    case 2:
    {
        s32 cleared_flags;

        shade = sprite->color.c.b + 0xC;
        sprite->color.c.b = shade;
        sprite->color.c.g = shade;
        sprite->color.c.r = shade;
        fade_ticks = controller->unk_96 - 1;
        controller->unk_96 = fade_ticks;
        if ((fade_ticks << 16) > 0) {
            return;
        }
        {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        cleared_flags = entity->flags1C & 0xEFFFFFFF;
        entity->flags1C = cleared_flags & ~0x200;
        controller->unk_8C = D_80170E9C;
    }

        return;
    }
}
