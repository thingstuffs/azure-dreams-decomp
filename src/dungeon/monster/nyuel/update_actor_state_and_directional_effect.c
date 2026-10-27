#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/nyuel.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80173564_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80173564_0;   /* arg0 in update_actor_state_and_directional_effect */

extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
#include "dungeon/player/object/action_state.h"
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void func_801737C4(void *, void *, void *, void *);

extern u8 nyuel_action_resume_address[];
extern u8 nyuel_frame_set_2[];
extern u8 nyuel_frame_set_1[];

/* Updates the actor state and selects its directional effect. */
void update_actor_state_and_directional_effect(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor) {
    u8 state;
    u8 *effect_table;
    s32 direction;

    state = controller->action_phase;
    switch (state) {
    case 0:
    {
        u8 *initial_effects;

        if ((sprite->flags & 0xE000) == 0) {
            return;
        }

        initial_effects = nyuel_frame_set_1;
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        sprite->frameTable = initial_effects;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        select_sprite_entry(sprite, initial_effects[direction & 7], 0);
        controller->action_phase++;
        return;
    }
    case 1:
        if (actor->mp == 0) {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }

            if ((actor->hp_delta != 0) &&
                begin_ready_actor_directional_action(controller, context, sprite, 0)) {
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
                return;
            }

            if (((u32)actor->flags1C) & ACTOR_PUSH_PENDING) {
                begin_pushed_actor_move(controller, context, sprite, actor);
                return;
            }

            if (((u32)actor->flags1C) & ACTOR_LIFTED) {
                begin_actor_move_to_target_facing(controller, context, sprite, actor);
                func_801737C4(controller, context, sprite, actor);
                return;
            }

            if (actor->pending_turn_updates == 0) {
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
                ActorRecord *owner;

                owner = primary_actor_record;
                if ((s16)check_entity_relation(actor, (u8 *)owner->previous_actor_header + 0x20) != 0) {
                    return;
                }
            }

            update_actor_status_and_mp(actor);
            on_actor_status_updated(actor);
            if (actor->mp == 0) {
                return;
            }
        }

        effect_table = nyuel_frame_set_2;
        sprite->frameTable = effect_table;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        select_sprite_entry(sprite, effect_table[direction & 7], 0);
        actor->flags1C &= ~ACTOR_ASLEEP;
        ((S_80173564_0 *)controller)->unk_8C = nyuel_action_resume_address;
        break;
    default:
        return;
    }
}
