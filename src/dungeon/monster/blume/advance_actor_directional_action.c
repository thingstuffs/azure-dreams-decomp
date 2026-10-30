#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"

/* Sparse views for fields not covered by the existing record types. */



typedef struct S_801741D8_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_801741D8_2;   /* arg3 in advance_actor_directional_action */

extern s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
extern void clear_slots_of_type(ActorRecord *owner, s8 match_type);
extern void select_sprite_entry(void *, s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s16 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
extern s32 generate_random_value(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void func_80174890(void *, void *, void *, void *);

extern u8 blume_action_resume_address[];
#include "dungeon/monster/blume.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"

extern u8 D_8017540C[];

/* Advance the actor action state and update its directional animation. */
void advance_actor_directional_action(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor_in) {
    void *actor;
    u8 state;
    DungeonGlobalStatus *global_state;
    void *check_target;
    void *active_actor;
    s8 tile;

    state = controller->action_phase.u;
    actor = actor_in;
    switch (state) {
    case 0:
        if (sprite->flags & 0xE000) {
            DungeonGlobalStatus *counter;

            (sprite->frameTable) = blume_direction_frames_2;
            select_sprite_entry(sprite,
                blume_direction_frames_2[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801741D8_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            counter = &g_dungeon_status;
            (*(u16 *)&counter->activity_counts.parts.pending_action_count)--;
            controller->action_phase.u++;
            break;
        }
        break;

    case 1:
        if ((s16)get_entity_effect_value(actor, STATUS_SLEEP) != 0) {
        global_state = &g_dungeon_status;
        if (global_state->flags & 0x1000) {
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(controller, context, sprite, 0) != 0) {
                break;
            }
        }

        if (((S_801741D8_2 *)actor)->unk_25 == 0) {
            if (global_state->flags & 0x2008) {
                break;
            }
            advance_actor_pending_action(controller, context, sprite, actor);
            break;
        }

        if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_1C & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(controller, context, sprite, actor);
            break;
        }

        if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_1C & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(controller, context, sprite, actor);
            func_80174890(controller, context, sprite, actor);
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_6D == 0) {
            break;
        }

        if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
            {
                ObjectNodeHeader *previous_node;
                void *previous_body;
                ActorRecord *previous_actor;

                previous_node = primary_actor_record->previous_actor_header;
                previous_body = previous_node + 1;
                previous_actor = previous_body;
                if ((s16)check_entity_relation(
                        actor, previous_actor) != 0) {
                    break;
                }
            }
        }

        update_actor_status_and_mp(actor);
        on_actor_status_updated(actor);
        do {
            if ((s16)get_entity_effect_value(actor, STATUS_SLEEP) != 0) {
                check_target = ((u8 *)(&reference_tile_object));
                tile = *(s8 *)&sprite->room_index;
            if (tile != reference_tile_object.room_index || tile < 0) {
                    s16 distance;

                    distance = get_tile_chebyshev_distance(((u8 *)(&reference_tile_object)), sprite);
                    active_actor = actor;
                    if (distance >= 2) {
                        break;
                    }
                    check_target = active_actor;
                }
                if ((generate_random_value(check_target) & 7) == 0) {
                    clear_slots_of_type(actor, STATUS_SLEEP);
                }
            }
            active_actor = actor;

        } while (0);

        if ((s16)get_entity_effect_value(active_actor, STATUS_SLEEP) != 0) {
            break;
        }
        }

        (sprite->frameTable) = D_8017540C;
        select_sprite_entry(sprite,
            D_8017540C[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801741D8_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        if (sprite->flags & 0x8000) {
            controller->unk_8C.address = blume_action_resume_address;
            break;
        } else {
            DungeonGlobalStatus *counter_m = &g_dungeon_status;
            counter_m->activity_counts.parts.pending_action_count++;
        }


        controller->action_phase.u++;
        break;

    case 2:
        if (sprite->flags & 0xE000) {
            DungeonGlobalStatus *counter_m = &g_dungeon_status;
            counter_m->activity_counts.parts.pending_action_count--;

            controller->unk_8C.address = blume_action_resume_address;
        }
        break;

    default:
        break;
    }
    return;
}
