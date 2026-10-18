#include "modules/dungeon_ovl_e0365c.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x2C];
    void *field_2C;
} SpriteFieldView_80DE5D7C;


void handle_actor_action_effects(void *controller, void *context, void *sprite, EntityRec *actor)
{
    u8 state;
    u8 *effect;
    s32 direction;

    state = ((E_8017357C_S_8017357C_0 *)controller)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *initial_effect;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        initial_effect = D_80174538;
        g_dungeon_status.unk_0A--;
        (((SpriteFieldView_80DE5D7C *)sprite)->field_2C) = initial_effect;
        direction = (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9;
        func_80047784(sprite, initial_effect[direction & 7], 0);
        ((E_8017357C_S_8017357C_0 *)controller)->unk_9B++;
        return;
    }
    case 1:
        if (actor->tileY == 0) {
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

            {
                void *call_controller = controller;

                if (((u32)actor->flags1C) & 0x100) {
                    do {
                        begin_pushed_actor_move(call_controller, context, sprite, actor);
                    } while (0);
                    return;
                }

                if (((u32)actor->flags1C) & 0x80000) {
                    begin_actor_move_to_target_facing(call_controller, context, sprite, actor);
                    update_actor_landing_and_trap(controller, context, sprite, actor);
                    return;
                }
            }

            if (actor->unk_6D == 0) {
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
                EntityRec *owner;

                owner = D_800814A8;
                if ((s16)check_entity_relation(actor, (u8 *)owner->unk_58 + 0x20) != 0) {
                    return;
                }
            }

            update_actor_status_and_food(actor);
            func_800A9A04(actor);
            if (actor->tileY == 0) {
                return;
            }
        }

        effect = D_80174520;
        (((SpriteFieldView_80DE5D7C *)sprite)->field_2C) = effect;
        direction = (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9;
        func_80047784(sprite, effect[direction & 7], 0);
        ((E_8017357C_S_8017357C_0 *)controller)->unk_8C = update_actor_behavior_facing_and_animation_2;
        actor->flags1C &= ~0x200;
    }
}
