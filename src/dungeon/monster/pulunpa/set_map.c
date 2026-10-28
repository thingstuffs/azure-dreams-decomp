#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
/* Pulunpa map selection and actor action and animation updates. */
#include "shared/sprite_frame_state.h"
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
s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
s8 find_active_rect_containing_point(u8 tile_x, u8 tile_y);
s32 test_neighbor_position_relation(u8 source_x, u8 source_y, u8 target_x, u8 target_y);
s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
s32 can_entity_gain_level(void *creature);
void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *state, void *unused,void *position,void *actor);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern s32 advance_actor_pending_action(void *actor_state, void *action, void *status, void *actor);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);
extern s32 process_selected_actor_record(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void update_object_or_select_directional_data(void *object_arg, void *context, void *source_arg, void *target_arg);
extern void choose_heading_and_advance_actor(void *context, s32 action, S_8017405C_1 *actor, void *movement);
void func_80174924(ActorRecord *action, ObjectPosition *action_id, SpriteFrameState *entity, ActorRecord *move_state);
extern s32 check_object_action_and_clear_flags(void *object, s32 query_x, s32 query_y, s32 action_override);
s32 select_nearby_target_and_start_action(ActorRecord *action_state, ObjectPosition *unused, SpriteFrameState *actor_pos_arg, ActorRecord *actor);

extern u8 pulunpa_frame_set_2[];
extern u8 D_80176358[];
extern M2C_UNK pulunpa_frame_set_3;
extern u8 D_80176370[];

/*
 * Installs the supplied sprite direction map and selects its eight-way entry using creature facing
 * relative to the camera.
 */
static __inline__ void set_map(SpriteFrameState *sprite, void *creature, u8 *direction_map) {
    (sprite->frameTable) = (void *)direction_map;
    select_sprite_entry(sprite, direction_map[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((S_set_map_0 *)creature)->unk_2A + 0x100)
        >> 9) & 7], 0);
}

/* Updates dungeon creature actions, facing direction, and animation. */
/* Dispatches alternate Pulunpa's movement and target actions, handles turn processing, and restores its
 * idle frames. */
void update_creature_actions_and_animation(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *creature) {
    u16 direction_aux;
    s32 status_flags;
    s8 tile_index;
    u16 action_flags;

    if (g_dungeon_status.flags & 0x1000) {
        actor->action_id.u = 14;
        func_80174924(actor, context, sprite, creature);
        return;
    }
    if (creature->mp_value.parts.whole == 0) {
        advance_actor_pending_action(actor, context, sprite, creature);
        if (sprite->frameTable == &pulunpa_frame_set_3) {
            return;
        }
        set_map(sprite, creature, (u8 *)&D_80176358);
        return;
    }
    if (creature->flags1C & ACTOR_ASLEEP) {
        if (sprite->frameTable == &pulunpa_frame_set_3) {
            actor->action_id.u = 13;
            actor->action_phase.s = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            creature->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, &D_80176358) != 0) {
            return;
        }
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        if (creature->flags1C & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor, context, sprite, creature);
            return;
        }
        if (actor->action_id.u != 14) {
            if (sprite->frameTable != (void *)pulunpa_frame_set_2) {
                set_map(sprite, creature, pulunpa_frame_set_2);
            }
            actor->action_id.u = 14;
        }
        actor->action_state_flags = (u16) (actor->action_state_flags & 0xFFF3);
        if (creature->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, &D_80176370) != 0) {
                return;
            }
        }
        if (creature->flags1C & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(actor, context, sprite, creature);
            update_object_or_select_directional_data(actor, context, sprite, creature);
            return;
        }
        if ((can_entity_gain_level(creature) << 0x10) != 0) {
            process_selected_actor_record(actor, context, sprite, creature);
        }
    }
    tile_index = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = tile_index;
    if (creature->pending_turn_updates > 0) {
        if (creature->flags1C & ACTOR_PARALYZED) {
            update_actor_status_and_mp(creature);
            return;
        }
        if (((S_80173B98_2 *)sprite)->unk_24.at00u.v == reference_tile_object.tile_position.word) {
            choose_heading_and_advance_actor(actor, context, sprite, creature);
            return;
        }
        if (!(creature->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((check_entity_relation(creature, previous_actor) << 0x10) != 0) {
                        return;
                    }
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
            if ((test_neighbor_position_relation(sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 0x10) != 0) {
                creature->facing = get_rounded_facing_and_rounding_flag(sprite->tile_x,
                    sprite->tile_y, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
            }
        }
    }
    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (sprite->flags & 0x40) {
        return;
    }
    if (sprite->frameTable == (void *)pulunpa_frame_set_2) {
        return;
    }
    set_map(sprite, creature, pulunpa_frame_set_2);
}
