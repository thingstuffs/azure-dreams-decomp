#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 find_active_rect_containing_point(s32, s32);
extern s32 test_neighbor_position_relation(s32, s32, s32, s32);
extern s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, u8 *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, void * unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, void * effect_param, void *target, u8 *direction_table, void * next_state);
extern void func_80171510(void *, void *, void *, void *);
void update_actor_movement_choosing_direction_recording_path(ActorRecord *move_work, ObjectPosition *entry_context, SpriteFrameState *position, ActorRecord *actor);
s32 check_action_eligibility_updates_actor_state_directional_animation_success(ActorRecord *action_state, ObjectPosition *action_id, SpriteFrameState *sprite, ActorRecord *actor);
extern void func_80172110(void *, void *, void *, void *);
extern s32 func_80172228(void *, void *, void *, s32);
extern void func_80173900(void *, void *, void *, void *);
extern void handle_kill_actor_clear_flags_fire_burst_tile_post_death_message(void *, ObjectPosition *, void *, void *);

extern s32 tyrant_action_resume_address;
extern u8 tyrant_direction_frames[];
extern u8 D_80173FC0[];
extern u8 D_80173FF0[];
extern u8 D_80173FF8[];
extern u8 D_80174000[];

typedef struct S_80170F68_1 {
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
} S_80170F68_1;   /* arg3 in update_dungeon_actor_behavior */

/* Updates a dungeon actor's behavior, facing, and animation from its current state. */
void update_dungeon_actor_behavior(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *map_object_arg, ActorRecord *actor_state_arg) {
    u8 *anim_table;
    s32 tile_id;
    u16 distance;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xE;
        func_80171510(actor_arg, context_arg, map_object_arg, actor_state_arg);
        return;
    }

    if (actor_state_arg->mp == 0) {
        u8 *inactive_anims;

        advance_actor_pending_action(actor_arg, context_arg, map_object_arg, actor_state_arg);
        if (map_object_arg->frameTable != D_80174000) {
            inactive_anims = D_80173FF8;
            (map_object_arg->frameTable) = inactive_anims;
            select_sprite_entry(map_object_arg,
                inactive_anims[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state_arg->facing + 0x100)
                    >> 9) & 7],
                0);
        }
        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_AE = 0;
        clear_slots_of_type(actor_state_arg, 0x1A);
        return;
    }

    if (((S_80170F68_1 *)actor_state_arg)->unk_1C & ACTOR_ASLEEP) {
        if (map_object_arg->frameTable == D_80174000) {
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_8C = 0;
            ((S_80170F68_1 *)actor_state_arg)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor_arg, context_arg, map_object_arg, D_80173FF8)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((S_80170F68_1 *)actor_state_arg)->unk_1C & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 != 0xE) {
            u8 next_state = 0xE;

            anim_table = tyrant_direction_frames;
            if (map_object_arg->frameTable != anim_table) {
                (map_object_arg->frameTable) = anim_table;
                select_sprite_entry(map_object_arg,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state_arg->facing + 0x100)
                        >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = next_state;
        }

        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_98 &= 0xFFF3;
        if (actor_state_arg->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor_arg, context_arg, map_object_arg, D_80173FC0)) {
                return;
            }
        }

        if (((S_80170F68_1 *)actor_state_arg)->unk_1C & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(actor_arg, context_arg, map_object_arg, actor_state_arg);
            func_80173900(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        }

        if ((s16)can_entity_gain_level(actor_state_arg) != 0) {
            process_selected_actor_record(actor_arg, context_arg, map_object_arg, actor_state_arg);
        }
    }

    tile_id = find_active_rect_containing_point(map_object_arg->tile_x,
        map_object_arg->tile_y);
    map_object_arg->room_index = tile_id;

    if (actor_state_arg->pending_turn_updates > 0) {
        if (((S_80170F68_1 *)actor_state_arg)->unk_1C & ACTOR_PARALYZED) {
            update_actor_status_and_mp(actor_state_arg);
            return;
        }
        if (*(u16 *)&map_object_arg->tile_x == reference_tile_object.tile_position.word) {
            update_actor_movement_choosing_direction_recording_path(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        }
        if (!(actor_state_arg->action_flags & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(actor_state_arg,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172228(actor_arg, context_arg, map_object_arg, 0) == 0) {
                return;
            }
            actor_state_arg->action_flags |= 0x4000;
            if (!(actor_state_arg->action_flags & 0x8000)) {
                update_actor_movement_choosing_direction_recording_path(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
            }
        }

        switch (actor_state_arg->action_flags & 0x3FFF) {
        case 8:
            if ((s16)check_action_eligibility_updates_actor_state_directional_animation_success(actor_arg, context_arg, map_object_arg, actor_state_arg) == 0) {
                func_80172110(actor_arg, context_arg, map_object_arg, actor_state_arg);
                return;
            }
            return;
        case 9:
            handle_kill_actor_clear_flags_fire_burst_tile_post_death_message(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        case 5:
        case 6:
        case 7:
            {
                ActorRecord *player;
                s32 direction;

                direction = get_rounded_facing_and_rounding_flag(
                    map_object_arg->tile_x, map_object_arg->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &distance);
                player = primary_actor_record;
                actor_state_arg->facing = direction;
                if (player->action_id == 0x11) {
                    begin_actor_spell_action(actor_arg, context_arg, map_object_arg, D_80173FF0, &tyrant_action_resume_address);
                    return;
                }
            }
            /* fallthrough */
        case 12:
            update_actor_status_and_mp(actor_state_arg);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor_arg, context_arg, map_object_arg, D_80173FF0, &tyrant_action_resume_address);
            return;
        default:
            update_actor_movement_choosing_direction_recording_path(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        }
    } else if (!(((S_80170F68_1 *)actor_state_arg)->unk_1C & ACTOR_PLAYER_SIDE)) {
        s32 record_index = (s8)tile_id;

        if ((record_index < 0) || !(dungeon_rooms[record_index].flags & 2)) {
            if (!(((S_80170F68_1 *)actor_state_arg)->unk_1C & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((s16)test_neighbor_position_relation(map_object_arg->tile_x,
                        map_object_arg->tile_y, reference_tile_object.tile_position.parts.tile_x,
                        reference_tile_object.tile_position.parts.tile_y) != 0) {
                    actor_state_arg->facing = get_rounded_facing_and_rounding_flag(
                        map_object_arg->tile_x,
                            map_object_arg->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &distance);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (map_object_arg->flags & 0x40) {
        return;
    }
    anim_table = tyrant_direction_frames;
    if (map_object_arg->frameTable == anim_table) {
        return;
    }
    (map_object_arg->frameTable) = anim_table;
    select_sprite_entry(map_object_arg,
        ((((g_game_work.view.camera_rotation.parts.viewAngle + actor_state_arg->facing + 0x100) >> 9) & 7) + anim_table)[0],
        0);
}
