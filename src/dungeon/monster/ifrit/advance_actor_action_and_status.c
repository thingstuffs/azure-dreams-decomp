#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/system/random.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon.h"
#include "dungeon/level.h"
#include "dungeon/monster/ifrit.h"
#include "engine/entity.h"


extern s16 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/monster/ifrit_frames.h"

#include "dungeon/actor/state.h"

extern void func_80173F28(void *, void *, void *, void *);

extern u8 ifrit_action_resume_address[];

/* Advance the actor action through animation setup, status handling, and completion. */
void advance_actor_action_and_status(ActorRecord *in_action, ObjectPosition *in_context, SpriteFrameState *in_sprite, ActorRecord *in_actor) {
    void *context = in_context;
    void *actor = in_actor;
    s32 state;

    state = in_action->action_phase;
    switch (state) {
    case 0:
        if (in_sprite->flags & 0xE000) {
            u8 *direction_frames;
            DungeonGlobalStatus *system_base;

            direction_frames = ifrit_frame_set;
            (in_sprite->frameTable) = direction_frames;
            select_sprite_entry(in_sprite,
                direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
                0);
            system_base = &g_dungeon_status;
            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)--;
            in_action->action_phase++;
        }
        return;

    case 1:
        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
            s32 actor_flags;
            DungeonGlobalStatus *system_base;

            system_base = &g_dungeon_status;
            if (system_base->flags & 0x1000) {
                return;
            }

            if ((((ActorRecord *)actor)->hp_delta != 0) &&
                (begin_ready_actor_directional_action(in_action, context, in_sprite, 0) != 0)) {
                return;
            }

            if (((ActorRecord *)actor)->mp_value.parts.whole == 0) {
                if (system_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(in_action, context, in_sprite, actor);
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }

            actor_flags = ((ActorRecord *)actor)->flags1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(in_action, context, in_sprite, actor);
                return;
            }

            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(in_action, context, in_sprite, actor);
                func_80173F28(in_action, context, in_sprite, actor);
                return;
            }

            if (((ActorRecord *)actor)->pending_turn_updates == 0) {
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = NODE_BODY(previous_node);
                    previous_actor = previous_body;
                    if ((check_entity_relation(actor,
                        previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }

            update_actor_status_and_mp(actor);
            on_actor_status_updated(actor);

            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                TileObject *origin;
                s8 coordinate;

                origin = &reference_tile_object;
                coordinate = ((s8)(in_sprite->room_index));
                if ((((coordinate == origin->room_index) &&
                    (coordinate >= 0)) ||
                    (get_tile_chebyshev_distance(origin, in_sprite) < 2)) &&
                    ((generate_random_value() & 7) == 0)) {
                    clear_slots_of_type(actor, STATUS_SLEEP);
                }
            }

            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                return;
            }
        }

        if (!(in_sprite->flags & 0x8000)) {
            DungeonGlobalStatus *system_base = &g_dungeon_status;

            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)++;
            in_action->action_phase++;
            return;
        }
        break;

    case 2:
        if (!(in_sprite->flags & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *system_base = &g_dungeon_status;
            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)--;
        }

        break;
    default:
        return;
    }
    ((ActorRecord *)actor)->flags1C &= ~ACTOR_ASLEEP;
    in_action = (void *)&in_action->unk_8C.address; /* BYTES: retiring this parameter as the callback-slot cursor preserves the retail save order. */
    *(void **)in_action = ifrit_action_resume_address;
}
