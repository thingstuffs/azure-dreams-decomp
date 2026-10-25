#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_8015F0EC_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   /* accessed as both */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    u8 pad_A4[0xE];
    s16 unk_B2;
} S_8015F0EC_0;   /* arg0 in update_actor_animation_and_dispatch_current */

extern s32 get_entity_effect_value(void *, s32);
extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 test_neighbor_position_relation(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8015F69C(void *, void *, void *, void *);
extern void func_8015F854(void *, void *, void *, void *);
extern s32 func_8015FF9C(void *, void *, void *, void *);
extern void func_80160234(void *, void *, void *, void *);
extern void func_80160358(void *, void *, void *, void *);
extern s32 func_8016066C(void *, void *, void *, s32);
extern void func_80162574(void *, void *, void *, void *);

extern u8 D_80163E40[];
extern u8 D_80163E48[];
extern u8 D_80163E98[];
extern u8 D_80163EA0[];
extern u8 D_80163EB0[];
extern u8 D_80163EB8[];

/* Update a dungeon actor's animation and dispatch its current behavior. */
void update_actor_animation_and_dispatch_current(void *actor, void *context, SpriteFrameState *sprite, ActorRecord *entity)
{
    u16 distance;
    s8 room_id;
    u16 action_flags;

    if (g_dungeon_status.flags & 0x1000) {
        ((S_8015F0EC_0 *)actor)->unk_9A = 0xE;
        func_8015F69C(actor, context, sprite, entity);
        return;
    }

    if (entity->mp == 0) {
        u8 *anim_table;

        advance_actor_pending_action(actor, context, sprite, entity);
        if (sprite->frameTable == D_80163EA0) {
            return;
        }
        anim_table = D_80163EB0;
        (sprite->frameTable) = anim_table;
        select_sprite_entry(sprite,
            anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)entity->flags1C) & ACTOR_ASLEEP) {
        if (sprite->frameTable == D_80163EA0) {
            ((S_8015F0EC_0 *)actor)->unk_9A = 0xD;
            ((S_8015F0EC_0 *)actor)->unk_9B = 1;
            ((S_8015F0EC_0 *)actor)->unk_8C = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_80163EB0) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }

        {
            void *current_anims;
            u8 *anim_table;

            if (((S_8015F0EC_0 *)actor)->unk_9A != 0xE) {
                ((S_8015F0EC_0 *)actor)->unk_9A = 0xE;
                ((S_8015F0EC_0 *)actor)->unk_B2 = 0;
            }

            current_anims = sprite->frameTable;
            if (current_anims == D_80163EB8) {
                if (sprite->flags & 0xE000) {
                    u8 *idle_anims = D_80163E40;

                    (sprite->frameTable) = idle_anims;
                    select_sprite_entry(sprite,
                        idle_anims[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    sprite->frame_ticks = 1;
                    ((S_8015F0EC_0 *)actor)->unk_A2.s = 0;
                    ((S_8015F0EC_0 *)actor)->unk_9E = 0;
                }
            } else {
                anim_table = D_80163E40;
                if (current_anims != anim_table) {
                    (sprite->frameTable) = anim_table;
                    select_sprite_entry(sprite,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    sprite->frame_ticks = 1;
                    ((S_8015F0EC_0 *)actor)->unk_A2.s = 0;
                    ((S_8015F0EC_0 *)actor)->unk_9E = 0;
                }
            }
        }

        entity->flags1C |= 0x40000;
        ((S_8015F0EC_0 *)actor)->unk_98 &= 0xFFF7;

        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80163E48) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & ACTOR_LIFTED) {
            s16 adjusted_offset;

            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            adjusted_offset = ((S_8015F0EC_0 *)actor)->unk_92.u - ((S_8015F0EC_0 *)actor)->unk_A2.u;
            ((S_8015F0EC_0 *)actor)->unk_A2.s = 0;
            ((S_8015F0EC_0 *)actor)->unk_9E = 0;
            ((S_8015F0EC_0 *)actor)->unk_92.s = adjusted_offset;
            func_80162574(actor, context, sprite, entity);
            return;
        }

        if ((can_entity_gain_level(entity) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, entity);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;

    if (entity->pending_turn_updates > 0) {
        if (((u32)entity->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            func_8015F854(actor, context, sprite, entity);
            return;
        }
        if (!(entity->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(entity,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8016066C(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = entity->action_flags | 0x4000;
            entity->action_flags = action_flags;
            if (!(action_flags & 0x8000)) {
                func_8015F854(actor, context, sprite, entity);
                return;
            }
        }

        switch ((entity->action_flags & ACTOR_ACTION_CODE_MASK) - 1) {
        case 7:
        case 8:
sw_case89:
            if ((func_8015FF9C(actor, context, sprite, entity) << 16) != 0) {
                return;
            }
            func_80160234(actor, context, sprite, entity);
            return;

        case 4:
        case 5:
        case 6:
sw_case567:
            {
                ActorRecord *player;
                s16 heading;

                heading = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &distance);
                player = primary_actor_record;
                entity->facing = heading;
                if (player->action_id == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_80163E98, update_actor_animation_and_dispatch_current);
                    return;
                }
            }
                                /* fallthrough */

        case 11:
            update_actor_status_and_mp(entity);
            return;

        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(actor, context, sprite, D_80163E98, update_actor_animation_and_dispatch_current);
            return;

        default:
            func_8015F854(actor, context, sprite, entity);
            return;
        }
    }

    if (!(((u32)entity->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((test_neighbor_position_relation(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &distance);
                    return;
                }
            }
        }
    } else if ((get_entity_effect_value(entity, STATUS_PARALYSIS) << 16) == 0) {
        if (primary_actor_record->action_id == 0x17) {
            func_80160358(actor, context, sprite, entity);
        }
    }
}
