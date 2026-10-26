#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/manoeva.h"

extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(u8, u8);
extern s32 test_neighbor_position_relation(u8, u8, u8, u8);
extern s16 get_rounded_facing_and_rounding_flag(u8, u8, u8, u8, s16 *);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, u8 *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, void * unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, void * effect_param, void *target, u8 *direction_table, void * next_state);

extern void func_80171460(void *, void *, void *, void *);
extern s32 func_80171E38(void *, void *, void *, void *);
extern void func_80171FFC(void *, void *, void *, void *);
extern s32 dispatch_actor_action_state(void *, void *, void *, s32);
extern void func_801737B8(void *, void *, void *, void *);
extern void initialize_object_and_clear_state(void *, void *, void *, void *);

extern u8 manoeva_action_resume_address[];
extern u8 manoeva_frame_set_1[];
extern u8 D_801765E0[];
extern u8 D_80176650[];
extern u8 D_80176660[];
extern u8 manoeva_frame_set_3[];

typedef struct S_80170EE4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80170EE4_0;   /* arg0 in update_actor_controller */

typedef struct S_80170EE4_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
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
} S_80170EE4_1;   /* arg3 in update_actor_controller */

/* Update dungeon actor behavior, facing, and directional animation. */
void update_actor_controller(void *actor_state_in, void *update_context_in, SpriteFrameState *map_object, void *actor_data)
{
    u32 dungeon_flags = g_dungeon_status.flags;
    s16 distance;
    s32 status_flags;
    s8 tile_index;
    s16 facing_angle;
    u16 action_flags;
    u8 *animation_table;
    ActorRecord *target_actor;

    if (dungeon_flags & 0x1000) {
        ((S_80170EE4_0 *)actor_state_in)->unk_9A = 14;
        func_80171460(actor_state_in, update_context_in, map_object, actor_data);
        return;
    }

    if (((S_80170EE4_1 *)actor_data)->unk_25 == 0) {
        advance_actor_pending_action(actor_state_in, update_context_in, map_object, actor_data);
        if (*(u8 **)&map_object->frameTable == D_80176650) {
            return;
        }
        (map_object->frameTable) = manoeva_frame_set_3;
        select_sprite_entry(
            map_object,
            manoeva_frame_set_3[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170EE4_1 *)actor_data)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80170EE4_1 *)actor_data)->unk_1C & 0x200) {
        if (*(u8 **)&map_object->frameTable == D_80176650) {
            ((S_80170EE4_0 *)actor_state_in)->unk_9A = 13;
            ((S_80170EE4_0 *)actor_state_in)->unk_9B = 1;
            ((S_80170EE4_0 *)actor_state_in)->unk_8C = 0;
            ((S_80170EE4_1 *)actor_data)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor_state_in, update_context_in, map_object, manoeva_frame_set_3) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (((S_80170EE4_1 *)actor_data)->unk_1C & 0x100) {
            begin_pushed_actor_move(actor_state_in, update_context_in, map_object, actor_data);
            return;
        }

        {
            u8 default_state = 14;
            if (((S_80170EE4_0 *)actor_state_in)->unk_9A != default_state) {
                if (*(u8 **)&map_object->frameTable != manoeva_frame_set_1) {
                    (map_object->frameTable) = manoeva_frame_set_1;
                    select_sprite_entry(
                        map_object,
                        manoeva_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170EE4_1 *)actor_data)->unk_2A + 0x100) >> 9) & 7],
                        0);
                }
                ((S_80170EE4_0 *)actor_state_in)->unk_9A = default_state;
            }
        }

        ((S_80170EE4_0 *)actor_state_in)->unk_98 &= 0xFFF3;

        if (((S_80170EE4_1 *)actor_data)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor_state_in, update_context_in, map_object, D_801765E0) != 0) {
                return;
            }
        }

        if (((S_80170EE4_1 *)actor_data)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(actor_state_in, update_context_in, map_object, actor_data);
            func_801737B8(actor_state_in, update_context_in, map_object, actor_data);
            return;
        }

        if ((s16)can_entity_gain_level(actor_data) != 0) {
            process_selected_actor_record(actor_state_in, update_context_in, map_object, actor_data);
        }
    }

    tile_index = find_active_rect_containing_point(map_object->tile_x,
        map_object->tile_y);
    map_object->room_index = tile_index;

    if (((S_80170EE4_1 *)actor_data)->unk_6D > 0) {
        if (((S_80170EE4_1 *)actor_data)->unk_1C & 0x20) {
            update_actor_status_and_mp(actor_data);
            return;
        }
        if (*(u16 *)&map_object->tile_x == reference_tile_object.tile_position.word) {
            advance_actor_turn_path(actor_state_in, update_context_in, map_object, actor_data);
            return;
        }
        action_flags = ((S_80170EE4_1 *)actor_data)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(
                        actor_data, (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)dispatch_actor_action_state(actor_state_in, update_context_in, map_object, 0) == 0) {
                return;
            }
            action_flags = ((S_80170EE4_1 *)actor_data)->unk_46 | 0x4000;
            ((S_80170EE4_1 *)actor_data)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                advance_actor_turn_path(actor_state_in, update_context_in, map_object, actor_data);
                return;
            }
        }

        switch (((S_80170EE4_1 *)actor_data)->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)func_80171E38(actor_state_in, update_context_in, map_object, actor_data) != 0) {
                return;
            }
            func_80171FFC(actor_state_in, update_context_in, map_object, actor_data);
            return;

        case 9:
            if (!(((S_80170EE4_1 *)actor_data)->unk_14 & 0x20000000)) {
                initialize_object_and_clear_state(actor_state_in, update_context_in, map_object, actor_data);
                return;
            }
            func_80171FFC(actor_state_in, update_context_in, map_object, actor_data);
            return;

        case 5:
        case 6:
        case 7:
            facing_angle = get_rounded_facing_and_rounding_flag(
                map_object->tile_x, map_object->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
            target_actor = primary_actor_record;
            ((S_80170EE4_1 *)actor_data)->unk_2A = facing_angle;
            if (target_actor->action_id == 0x11) {
                begin_actor_spell_action(actor_state_in, update_context_in, map_object, D_80176660, manoeva_action_resume_address);
                return;
            }

        case 12:
            update_actor_status_and_mp(actor_data);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor_state_in, update_context_in, map_object, D_80176660, manoeva_action_resume_address);
            return;

        case 11:
        default:
            advance_actor_turn_path(actor_state_in, update_context_in, map_object, actor_data);
            return;
        }
    }

    status_flags = ((S_80170EE4_1 *)actor_data)->unk_1C;
    if (!(status_flags & 0x2000)) {
        if ((tile_index < 0) ||
            !(dungeon_rooms[tile_index].flags & 2)) {
            if (!(status_flags & 0x430)) {
                if ((s16)test_neighbor_position_relation(
                        map_object->tile_x, map_object->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    ((S_80170EE4_1 *)actor_data)->unk_2A = get_rounded_facing_and_rounding_flag(
                        map_object->tile_x, map_object->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (map_object->flags & 0x40) {
        return;
    }
    animation_table = manoeva_frame_set_1;
    if (*(u8 **)&map_object->frameTable == animation_table) {
        return;
    }
    (map_object->frameTable) = animation_table;
    select_sprite_entry(
        map_object,
        *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170EE4_1 *)actor_data)->unk_2A + 0x100) >> 9) & 7)
                + (u32)animation_table),
        0);
}
