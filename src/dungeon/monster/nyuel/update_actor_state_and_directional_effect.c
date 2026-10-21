#include "common.h"
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
extern s32 has_pending_actor_or_turn_action(void *);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_801737C4(void *, void *, void *, void *);

extern u8 D_80170E9C[];
extern u8 D_80174EE0[];
extern u8 D_80174F00[];

/* Updates the actor state and selects its directional effect. */
void update_actor_state_and_directional_effect(void *controller, void *context, void *sprite, ActorRecord *actor)
{
    u8 state;
    u8 *effect_table;
    s32 direction;

    state = ((S_80173564_0 *)controller)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *initial_effects;

        if ((((SpriteFrameState *)sprite)->flags & 0xE000) == 0) {
            return;
        }

        initial_effects = D_80174F00;
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        ((SpriteFrameState *)sprite)->frameTable = initial_effects;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        select_sprite_entry(sprite, initial_effects[direction & 7], 0);
        ((S_80173564_0 *)controller)->unk_9B++;
        return;
    }
    case 1:
        if (actor->mp == 0) {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }

            if ((actor->unk_64 != 0) &&
                begin_ready_actor_directional_action(controller, context, sprite, 0)) {
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
                return;
            }

            if (((u32)actor->flags1C) & 0x100) {
                begin_pushed_actor_move(controller, context, sprite, actor);
                return;
            }

            if (((u32)actor->flags1C) & 0x80000) {
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
                if ((s16)check_entity_relation(actor, (u8 *)owner->unk_58 + 0x20) != 0) {
                    return;
                }
            }

            update_actor_status_and_food(actor);
            on_actor_status_updated(actor);
            if (actor->mp == 0) {
                return;
            }
        }

        effect_table = D_80174EE0;
        ((SpriteFrameState *)sprite)->frameTable = effect_table;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        select_sprite_entry(sprite, effect_table[direction & 7], 0);
        actor->flags1C &= ~0x200;
        ((S_80173564_0 *)controller)->unk_8C = D_80170E9C;
        break;
    default:
        return;
    }
}
