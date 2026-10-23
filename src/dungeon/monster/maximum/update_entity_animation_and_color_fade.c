#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_80173204_arg0.h"

typedef struct S_80173204_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173204_7;   /* counter in update_entity_animation_and_color_fade */

extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, s32);
extern s16 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, s32, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, s32, void *, s32);
extern void advance_actor_pending_action(void *, s32, void *, void *);
extern void begin_actor_move_to_target_facing(void *, s32, void *, void *);
extern void advance_actor_state_with_child(void *, s32, void *, void *);

extern u8 D_80170E54;
extern u8 D_80173C9C[];
extern u8 maximum_frame_set_1[];

/* Updates entity state, directional animation, and color fading. */
void update_entity_animation_and_color_fade(Rec_func_80173204_arg0 *controller, s32 update_mode, SpriteFrameState *sprite, ActorRecord *entity)
{
    s32 state;
    s32 flags;
    s8 floor;
    DungeonGlobalStatus *counter_base;
    TileObject *floor_base;

    if (controller->unk_9B < 2U) {
        if (sprite->color.c.r >= 0x33U) {
            sprite->color.word += -0x30303;
        }
    } else if (sprite->color.c.r < 0x80U) {
        sprite->color.word += 0x30303;
    }

    state = controller->unk_9B;
    switch (state) {
    case 0:
        entity->flags1C |= 0x10000000;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = D_80173C9C;
        select_sprite_entry(
            sprite,
            D_80173C9C[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        counter_base = &g_dungeon_status;
        counter_base->activity_counts.parts.pending_action_count =
            ((u16)counter_base->activity_counts.parts.pending_action_count) - 1;
        controller->unk_9B++;
        return;

    case 1:
        if ((get_entity_effect_value(entity, STATUS_SLEEP) << 16) == 0) {
            sprite->frameTable = maximum_frame_set_1;
            select_sprite_entry(
                sprite,
                maximum_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            if (sprite->flags & 0x8000) {
                entity->flags1C &= ~ACTOR_ASLEEP;
                entity->flags1C &= 0xEFFFFFFF;
                sprite->color.word = 0x808080;
                controller->unk_8C.as_pu8 = &D_80170E54;
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count++;
            controller->unk_9B++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }
        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(controller, update_mode, sprite, 0) != 0) {
                return;
            }
        }
        if (entity->mp == 0) {
            if (g_dungeon_status.flags & 0x2008) {
                return;
            }
            advance_actor_pending_action(controller, update_mode, sprite, entity);
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        flags = entity->flags1C;
        if (flags & 0x100) {
            begin_pushed_actor_move(controller, update_mode, sprite, entity);
            return;
        }
        if (flags & 0x80000) {
            begin_actor_move_to_target_facing(controller, update_mode, sprite, entity);
            advance_actor_state_with_child(controller, update_mode, sprite, entity);
            return;
        }
        if (entity->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(
                     entity,
                     ((s32)primary_actor_record->previous_actor_header) + 0x20) << 16) != 0) {
                return;
            }
        }
        update_actor_status_and_mp(entity);
        on_actor_status_updated(entity);
        if ((get_entity_effect_value(entity, STATUS_SLEEP) << 16) != 0) {
            floor_base = &reference_tile_object;
            floor = *(s8 *)&sprite->unk_26;
            if (((floor == floor_base->room_index) && (floor >= 0)) ||
                get_tile_chebyshev_distance(floor_base, sprite) < 2) {
                if ((generate_random_value() & 7) == 0) {
                    clear_slots_of_type(entity, STATUS_SLEEP);
                }
            }
        }

        if ((get_entity_effect_value(entity, STATUS_SLEEP) << 16) != 0) {
            return;
        }
        sprite->frameTable = maximum_frame_set_1;
        select_sprite_entry(
            sprite,
            maximum_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        if (sprite->flags & 0x8000) {
            entity->flags1C &= ~ACTOR_ASLEEP;
            entity->flags1C &= 0xEFFFFFFF;
            sprite->color.word = 0x808080;
            controller->unk_8C.as_pu8 = &D_80170E54;
            return;
        }
        {
            u8 *counter;

            counter = ((u8 *)(&g_dungeon_status));
            ((S_80173204_7 *)counter)->unk_0A++;
        }

        controller->unk_9B++;
        return;

    case 2:
        if (!(sprite->flags & 0x8000)) {
            if (sprite->color.c.r < 0x80U) {
                return;
            }
        }
        {
            u8 *counter = ((u8 *)(&g_dungeon_status));
            ((S_80173204_7 *)counter)->unk_0A--;
        }
        entity->flags1C &= 0xEFFFFFFF;
        sprite->color.word = 0x808080;
        entity->flags1C &= ~ACTOR_ASLEEP;
        controller->unk_8C.as_pu8 = &D_80170E54;

        return;
    default:
        return;
    }
}
