#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_800DA014_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_800DA014_0;   /* in_arg0 in advance_actor_action_controller */

extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_record_entry_and_value(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s16 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
extern s32 generate_random_value(void);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void install_actor_action_handler_after_floor_trap_check(void *, void *, void *, void *);

extern u8 actor_action_frames[];

/* Advances the actor action state and updates its directional animation. */
void advance_actor_action_controller(void *controller, void *action_context, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 state;

    state = ((S_800DA014_0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        if (sprite->flags & 0xE000) {
            u8 *direction_table;
            DungeonGlobalStatus *system_base;

            direction_table = actor_action_frames;
            sprite->frameTable = direction_table;
            select_record_entry_and_value(sprite,
                *(void **)(direction_table + (((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 7) & 28)),
                0);
            system_base = &g_dungeon_status;
            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)--;
            ((S_800DA014_0 *)controller)->unk_9B++;
        }
        return;
    case 1:
    {
        s32 actor_flags;
        DungeonGlobalStatus *system_base;

        system_base = &g_dungeon_status;
        if (system_base->flags & 0x1000) {
            return;
        }

        if ((actor->hp_delta != 0) &&
            (begin_ready_actor_directional_action(controller, action_context, sprite, 0) != 0)) {
            return;
        }

        if (actor->mp_value.parts.whole == 0) {
            if (system_base->flags & 0x2008) {
                return;
            }
            advance_actor_pending_action(controller, action_context, sprite, actor);
            return;
        }

        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            return;
        }

        actor_flags = actor->flags1C;
        if (actor_flags & 0x100) {
            begin_pushed_actor_move(controller, action_context, sprite, actor);
            return;
        }

        if (actor_flags & 0x80000) {
            begin_actor_move_to_target_facing(controller, action_context, sprite, actor);
            install_actor_action_handler_after_floor_trap_check(controller, action_context, sprite, actor);
            return;
        }

        if (actor->pending_turn_updates == 0) {
            return;
        }

        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            if ((check_entity_relation(actor,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_mp(actor);
        on_actor_status_updated(actor);

        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
            TileObject *reference_sprite;
            s8 coordinate;

            reference_sprite = &reference_tile_object;
            coordinate = *(s8 *)&sprite->room_index;
            if ((((coordinate == reference_sprite->room_index) &&
                        (coordinate >= 0)) ||
                 (get_tile_chebyshev_distance(reference_sprite, sprite) < 2)) &&
                ((generate_random_value() & 7) == 0)) {
                clear_slots_of_type(actor, STATUS_SLEEP);
            }
        }

        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) == 0) {
            u8 *direction_table;

            direction_table = actor_action_frames;
            sprite->frameTable = direction_table;
            select_record_entry_and_value(sprite,
                *(void **)(direction_table + (((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 7) & 28)),
                0);
        } else {
            return;
        }
    }

        if (!(sprite->flags & 0x8000)) {
            DungeonGlobalStatus *system_base = &g_dungeon_status;

            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)++;
            ((S_800DA014_0 *)controller)->unk_9B++;
            return;
        }
        break;
    case 2:
        if (!(sprite->flags & 0xE000)) {
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

    actor->flags1C &= ~ACTOR_ASLEEP;
    ((S_800DA014_0 *)controller)->unk_8C = update_actor_facing_animation;
}
