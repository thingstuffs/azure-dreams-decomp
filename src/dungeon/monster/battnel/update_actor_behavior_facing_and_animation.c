#include "shared/object_node.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80170E5C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { s16 s; u16 u; } unk_A4;   /* accessed as both */
} S_80170E5C_0;   /* arg0 in update_actor_behavior_facing_and_animation_2 */

typedef struct S_80170E5C_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80170E5C_1;   /* arg3 in update_actor_behavior_facing_and_animation_2 */

extern void select_sprite_entry(void *, s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s32 find_active_rect_containing_point(s32, s32);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void advance_actor_path_script_step(void *controller, ObjectPosition *context, void *entity, void *path_state);
extern void func_8017162C(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data);
extern s32 func_80171DD8(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite_arg, ActorRecord *actor);
extern void select_and_start_target_action(ActorRecord *action_state, ObjectPosition *action_context, void *sprite, ActorRecord *actor);
extern s32 func_801720B4(void *, void *, void *, s32);
extern void func_80173AC0(void *, void *, void *, void *);

#include "dungeon/monster/battnel.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor/state.h"

extern u8 D_80173D14[];
extern u8 D_80173D1C[];
extern u8 D_80173D3C[];
extern u8 battnel_frame_set[];
extern u8 D_80173D4C[];

/* Update actor behavior, facing, and animation from dungeon state. */
/* Selects Battnel's movement, attacks, spells, and turn processing, with a ten-tick transition back to its
 * idle frames. */
void update_actor_behavior_facing_and_animation_2(void *actor, ObjectPosition *context, SpriteFrameState *sprite, void *status) {
    u8 *anim_table;
    s32 room_id;
    u16 direction_aux;
    s16 anim_ticks;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        ((S_80170E5C_0 *)actor)->unk_9A = 0xE;
        advance_actor_path_script_step(actor, context, sprite, status);
        return;
    }

    if (((S_80170E5C_1 *)status)->unk_25 == 0) {
        advance_actor_pending_action(actor, context, sprite, status);
        if (sprite->frameTable == D_80173D4C) {
            return;
        }
        (sprite->frameTable) = battnel_frame_set;
        select_sprite_entry(sprite,
            battnel_frame_set[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170E5C_1 *)status)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80170E5C_1 *)status)->unk_1C & 0x200) {
        if (sprite->frameTable == D_80173D4C) {
            ((S_80170E5C_0 *)actor)->unk_9A = 0xD;
            ((S_80170E5C_0 *)actor)->unk_9B = 1;
            ((S_80170E5C_0 *)actor)->unk_8C = 0;
            ((S_80170E5C_1 *)status)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, battnel_frame_set)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((S_80170E5C_1 *)status)->unk_1C & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, status);
            return;
        }

        if (((S_80170E5C_0 *)actor)->unk_9A != 0xE) {
            u8 next_state = 0xE;

            if (sprite->frameTable != battnel_direction_frames) {
                s32 anim_delay = 10;

                ((S_80170E5C_0 *)actor)->unk_A4.s = anim_delay;
                (sprite->frameTable) = D_80173D14;
                select_sprite_entry(sprite,
                    D_80173D14[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170E5C_1 *)status)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
            ((S_80170E5C_0 *)actor)->unk_9A = next_state;
        }

        ((S_80170E5C_0 *)actor)->unk_98 &= 0xFFF3;
        if (((S_80170E5C_1 *)status)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80173D1C)) {
                return;
            }
        }

        if (((S_80170E5C_1 *)status)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, status);
            func_80173AC0(actor, context, sprite, status);
            return;
        }

        if ((s16)can_entity_gain_level(status) != 0) {
            process_selected_actor_record(actor, context, sprite, status);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;

    if (((S_80170E5C_1 *)status)->unk_6D > 0) {
        if (((S_80170E5C_1 *)status)->unk_1C & 0x20) {
            update_actor_status_and_mp(status);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            func_8017162C(actor, context, sprite, status);
            return;
        }
        if (!(((S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((s16)check_entity_relation(status,
                        previous_actor) != 0) {
                        return;
                    }
                }
            }
            if ((s16)func_801720B4(actor, context, sprite, 0) == 0) {
                return;
            }
            ((S_80170E5C_1 *)status)->unk_46 |= 0x4000;
            if (!(((S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
                func_8017162C(actor, context, sprite, status);
                return;
            }
        }

        switch ((((S_80170E5C_1 *)status)->unk_46 & 0x3FFF) - 1) {
        case 7:
        case 8:
            if ((s16)func_80171DD8(actor, context, sprite, status) == 0) {
                select_and_start_target_action(actor, context, sprite, status);
            }
            return;

        case 4:
        case 5:
        case 6:
            {
                ActorRecord *global_actor;
                s32 direction;

                direction = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &direction_aux);
                global_actor = primary_actor_record;
                ((S_80170E5C_1 *)status)->unk_2A = direction;
                if (global_actor->action_id.u == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_80173D3C, update_actor_behavior_facing_and_animation_2);
                    return;
                }
            }

        case 11:
            update_actor_status_and_mp(status);
            return;

        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(actor, context, sprite, D_80173D3C, update_actor_behavior_facing_and_animation_2);
            return;

        case 3:
        case 9:
        case 10:
        default:
            func_8017162C(actor, context, sprite, status);
            return;

        }
    }

    if (!(((S_80170E5C_1 *)status)->unk_1C & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((S_80170E5C_1 *)status)->unk_1C & 0x430)) {

                if ((s16)test_neighbor_position_relation(sprite->tile_x,
                    sprite->tile_y, reference_tile_object.tile_position.parts.tile_x,
                    reference_tile_object.tile_position.parts.tile_y) != 0) {
                    ((S_80170E5C_1 *)status)->unk_2A = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_aux);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (sprite->flags & 0x40) {
        return;
    }
    anim_table = battnel_direction_frames;
    if (sprite->frameTable == anim_table) {
        return;
    }
    anim_ticks = ((S_80170E5C_0 *)actor)->unk_A4.u - 1;
    ((S_80170E5C_0 *)actor)->unk_A4.s = anim_ticks;
    if (anim_ticks > 0) {
        return;
    }
    ((S_80170E5C_0 *)actor)->unk_A4.s = -1;

    (sprite->frameTable) = anim_table;
    select_sprite_entry(sprite,
        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170E5C_1 *)status)->unk_2A + 0x100) >> 9) & 7],
        0);
}
