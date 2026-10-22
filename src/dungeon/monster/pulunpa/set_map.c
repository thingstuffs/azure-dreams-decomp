/* Pulunpa map selection and actor action and animation updates. */
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

typedef s32 M2C_UNK;
typedef struct S_800AA258_2 S_800AA258_2;
#include "records/Rec_func_800AA258_arg2.h"
typedef struct S_8017405C_1 S_8017405C_1;


typedef struct S_set_map_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_set_map_0;   /* arg3 in set_map */


typedef struct S_80173B98_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80173B98_2;   /* arg2 in update_creature_actions_and_animation */



void select_sprite_entry(void *sprite, u8 frame, s32 mode);
s32 check_entity_relation(void *creature, s32 offset);
s8 find_active_rect_containing_point(u8 tile_x, u8 tile_y);
s32 test_neighbor_position_relation(u8 source_x, u8 source_y, u8 target_x, u8 target_y);
s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
s32 can_entity_gain_level(void *creature);
void update_actor_status_and_mp(void *creature);
extern void begin_pushed_actor_move(Rec_func_800A9E70_arg0 *state, void *unused, S_800AA258_2 *position, ActorRecord *actor);
extern s32 begin_ready_actor_directional_action(void *entity, s32 context, Rec_func_800AA258_arg2 *sprite, s32 direction_frames);
extern s32 advance_actor_pending_action(void *actor_state, s32 action, void *status, void *actor);
extern void begin_actor_move_to_target_facing(Rec_func_800A9E70_arg0 *state, void *unused, Rec_func_800AA258_arg2 *position, ActorRecord *entity);
s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern s32 process_selected_actor_record(s32 buffer_addr, s32 source, s32 unused, ActorRecord *record);
extern void update_object_or_select_directional_data(void *object_arg, void *context, void *source_arg, void *target_arg);
extern void choose_heading_and_advance_actor(void *context, s32 action, S_8017405C_1 *actor, void *movement);
void func_80174924(void);
extern s32 check_object_action_and_clear_flags(void *object, s32 query_x, s32 query_y, s32 action_override);
extern s32 select_nearby_target_and_start_action(void *action_state, void *unused, void *actor_pos_arg, void *actor);

extern u8 D_80176320[];
extern M2C_UNK D_80176358;
extern M2C_UNK D_80176360;
extern M2C_UNK D_80176370;

static __inline__ void set_map(void *sprite, void *creature, u8 *direction_map) {
    (((S_80173B98_2 *)sprite)->unk_2C) = (void *)direction_map;
    select_sprite_entry(sprite, direction_map[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((S_set_map_0 *)creature)->unk_2A + 0x100)
        >> 9) & 7], 0);
}

/* Updates dungeon creature actions, facing direction, and animation. */
/* Dispatches alternate Pulunpa's movement and target actions, handles turn processing, and restores its
 * idle frames. */
void update_creature_actions_and_animation(void *actor, s32 context, void *sprite, ActorRecord *creature) {
    s32 direction_aux;
    s32 status_flags;
    s8 tile_index;
    u16 action_flags;

    if (g_dungeon_status.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 14;
        func_80174924();
        return;
    }
    if (creature->mp == 0) {
        advance_actor_pending_action(actor, context, sprite, creature);
        if (((S_80173B98_2 *)sprite)->unk_2C == &D_80176360) {
            return;
        }
        set_map(sprite, creature, (u8 *)&D_80176358);
        return;
    }
    if (creature->flags1C & 0x200) {
        if (((S_80173B98_2 *)sprite)->unk_2C == &D_80176360) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 13;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_s8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            creature->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, &D_80176358) != 0) {
            return;
        }
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        if (creature->flags1C & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, creature);
            return;
        }
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 14) {
            if (((S_80173B98_2 *)sprite)->unk_2C != (void *)D_80176320) {
                set_map(sprite, creature, D_80176320);
            }
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 14;
        }
        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 0xFFF3);
        if (creature->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, &D_80176370) != 0) {
                return;
            }
        }
        if (creature->flags1C & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, creature);
            update_object_or_select_directional_data(actor, context, sprite, creature);
            return;
        }
        if ((can_entity_gain_level(creature) << 0x10) != 0) {
            process_selected_actor_record(actor, context, sprite, creature);
        }
    }
    tile_index = find_active_rect_containing_point(((S_80173B98_2 *)sprite)->unk_24.at00.v, ((S_80173B98_2 *)sprite)->unk_24.at01.v);
    ((S_80173B98_2 *)sprite)->unk_26 = tile_index;
    if (creature->pending_turn_updates > 0) {
        if (creature->flags1C & 0x20) {
            update_actor_status_and_mp(creature);
            return;
        }
        if (((S_80173B98_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            choose_heading_and_advance_actor(actor, context, sprite, creature);
            return;
        }
        if (!(creature->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(creature, ((s32)primary_actor_record->previous_actor_header) + 0x20) << 0x10) != 0) {
                    return;
                }
            }
            if ((check_object_action_and_clear_flags(actor, context, sprite, 0) << 0x10) == 0) {
                return;
            }
            action_flags = creature->action_flags | 0x4000;
            creature->action_flags = action_flags;
            if (!(action_flags & 0x8000)) {
                choose_heading_and_advance_actor(actor, context, sprite, creature);
                return;
            }
        }
        switch (creature->action_flags & ACTOR_ACTION_CODE_MASK) {
        case 9:
            if (select_nearby_target_and_start_action(actor, context, sprite, creature) != 0) {
                return;
            }
            choose_heading_and_advance_actor(actor, context, sprite, creature);
            return;
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        case 7:
        case 8:
        case 12:
            update_actor_status_and_mp(creature);
            return;
        case 4:
        case 10:
        case 11:
        default:
            choose_heading_and_advance_actor(actor, context, sprite, creature);
            return;
        }
    }
    status_flags = creature->flags1C;
    if (!(status_flags & 0x2000)) {
        if (tile_index >= 0 && (dungeon_rooms[tile_index].flags & 2)) {
        } else if (!(status_flags & 0x430)) {
            if ((test_neighbor_position_relation(((S_80173B98_2 *)sprite)->unk_24.at00.v, ((S_80173B98_2 *)sprite)->unk_24.at01.v,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 0x10) != 0) {
                creature->facing = get_rounded_facing_and_rounding_flag(((S_80173B98_2 *)sprite)->unk_24.at00.v,
                    ((S_80173B98_2 *)sprite)->unk_24.at01.v, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
            }
        }
    }
    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((S_80173B98_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    if (((S_80173B98_2 *)sprite)->unk_2C == (void *)D_80176320) {
        return;
    }
    set_map(sprite, creature, D_80176320);
}
