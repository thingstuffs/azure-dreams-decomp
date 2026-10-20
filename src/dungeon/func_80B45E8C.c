#include "modules/dungeon_resource12_slot0.h"

void func_8017368C(void *in_controller, void *in_context, void *sprite, void *in_actor)
{
    void *context = in_context;
    void *actor = in_actor;
    s32 state;

    state = ((R12_8017368C_S_80173358_0 *)in_controller)->unk_9B;
    switch (state) {
    case 0:
        if (((R12_8017368C_S_80173358_1 *)sprite)->unk_14 & 0xE000) {
            u8 *direction_anims;
            DungeonGlobalStatus *system_base;

            direction_anims = ((u8 *)D_80175A9C);
            (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
            select_sprite_entry(sprite,
                direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_8017368C_S_80173358_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            system_base = &g_dungeon_status;
            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)--;
            ((R12_8017368C_S_80173358_0 *)in_controller)->unk_9B++;
        }
        return;

    case 1:
        if ((get_entity_effect_value(actor, 1) << 16) != 0) {
            s32 actor_flags;
            DungeonGlobalStatus *system_base;

            system_base = &g_dungeon_status;
            if (system_base->flags & 0x1000) {
                return;
            }

            if ((((R12_8017368C_S_80173358_2 *)actor)->unk_64 != 0) &&
                (begin_ready_actor_directional_action(in_controller, context, sprite, 0) != 0)) {
                return;
            }

            if (((R12_8017368C_S_80173358_2 *)actor)->unk_25 == 0) {
                if (system_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(in_controller, context, sprite, actor);
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }

            actor_flags = ((R12_8017368C_S_80173358_2 *)actor)->unk_1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(in_controller, context, sprite, actor);
                return;
            }

            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(in_controller, context, sprite, actor);
                func_80173D64(in_controller, context, sprite, actor);
                return;
            }

            if (((R12_8017368C_S_80173358_2 *)actor)->unk_6D == 0) {
                return;
            }

            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                if ((check_entity_relation(actor,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }

            update_actor_status_and_food(actor);
            on_actor_status_updated(actor);

            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                TileObject *origin;
                s8 coordinate;

                origin = &D_80082E80;
                coordinate = ((R12_8017368C_S_80173358_1 *)sprite)->unk_26;
                if ((((coordinate == origin->room_index) &&
                    (coordinate >= 0)) ||
                    (((s16)get_tile_chebyshev_distance(origin, sprite)) < 2)) &&
                    ((generate_random_value() & 7) == 0)) {
                    clear_slots_of_type(actor, 1);
                }
            }

            if ((get_entity_effect_value(actor, 1) << 16) != 0) {
                return;
            }
        }

        {
            u8 *direction_anims;

            direction_anims = ((u8 *)D_80175AA4);
            (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
            select_sprite_entry(sprite,
                direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((R12_8017368C_S_80173358_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }

        sprite = (u8 *)sprite + 0x14;
        if (!(*(u16 *)sprite & 0x8000)) {
            DungeonGlobalStatus *system_base = &g_dungeon_status;

            (*(u16 *)&system_base->activity_counts.parts.pending_action_count)++;
            ((R12_8017368C_S_80173358_0 *)in_controller)->unk_9B++;
            return;
        }
        break;

    case 2:
        if (!(((R12_8017368C_S_80173358_1 *)sprite)->unk_14 & 0xE000)) {
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
    ((R12_8017368C_S_80173358_2 *)actor)->unk_1C &= ~0x200;
    in_controller = (u8 *)in_controller + 0x8C;
    *(void **)in_controller = ((u8 *)update_actor_state_and_select_target);
}
