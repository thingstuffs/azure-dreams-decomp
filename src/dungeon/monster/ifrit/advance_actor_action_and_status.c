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

typedef struct S_8017388C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_8017388C_0;   /* arg0 in advance_actor_action_and_status */

typedef struct S_8017388C_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_8017388C_2;   /* arg3 in advance_actor_action_and_status */

extern s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
extern void clear_slots_of_type(ActorRecord *owner, s8 match_type);
extern void select_sprite_entry(void *, s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s16 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
extern s32 generate_random_value(void);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void func_80173F28(void *, void *, void *, void *);

extern u8 ifrit_action_resume_address[];
extern u8 ifrit_frame_set[];

/* Advance the actor action through animation setup, status handling, and completion. */
void advance_actor_action_and_status(ActorRecord *in_action, ObjectPosition *in_context, SpriteFrameState *in_sprite, ActorRecord *in_actor) {
    void *context = in_context;
    void *actor = in_actor;
    s32 state;

    state = in_action->action_phase.u;
    switch (state) {
    case 0:
        if (in_sprite->flags & 0xE000) {
            u8 *direction_frames;
            DungeonGlobalStatus *system_base;

            direction_frames = ifrit_frame_set;
            (in_sprite->frameTable) = direction_frames;
            select_sprite_entry(in_sprite,
                direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8017388C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            system_base = &g_dungeon_status;
            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)--;
            in_action->action_phase.u++;
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

            if ((((S_8017388C_2 *)actor)->unk_64 != 0) &&
                (begin_ready_actor_directional_action(in_action, context, in_sprite, 0) != 0)) {
                return;
            }

            if (((S_8017388C_2 *)actor)->unk_25 == 0) {
                if (system_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(in_action, context, in_sprite, actor);
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }

            actor_flags = ((S_8017388C_2 *)actor)->unk_1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(in_action, context, in_sprite, actor);
                return;
            }

            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(in_action, context, in_sprite, actor);
                func_80173F28(in_action, context, in_sprite, actor);
                return;
            }

            if (((S_8017388C_2 *)actor)->unk_6D == 0) {
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
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
                coordinate = *(s8 *)&in_sprite->room_index;
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
            in_action->action_phase.u++;
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
    ((S_8017388C_2 *)actor)->unk_1C &= ~ACTOR_ASLEEP;
    in_action = (void *)&in_action->unk_8C.address; /* BYTES: retiring this parameter as the callback-slot cursor preserves the retail save order. */
    *(void **)in_action = ifrit_action_resume_address;
}
