#include "modules/dungeon_ovl_e0365c.h"

void handle_actor_pending_action(void *action, void *context, void *sprite, EntityRec *entity)
{
    void *saved_context;
    u8 state;

    saved_context = context;
#define context saved_context
#define sprite sprite

    state = ((E_80173254_S_80173254_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            u8 *direction_anims;

            direction_anims = D_80174538;
            (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
            select_sprite_entry(sprite,
                direction_anims[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            g_dungeon_status.unk_0A--;
            ((E_80173254_S_80173254_0 *)action)->unk_9B++;
        }
        return;
    case 1:
        if ((get_entity_effect_value(entity, 1) << 16) != 0) {
            s32 entity_flags;

            if (g_dungeon_status.flags & 0x1000) {
                return;
            }

            if ((entity->unk_64 != 0) &&
                (begin_ready_actor_directional_action(action, context, sprite, 0) != 0)) {
                return;
            }

            if (entity->tileY == 0) {
                if (g_dungeon_status.flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(action, context, sprite, entity);
                return;
            }

            if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
                return;
            }

            entity_flags = entity->flags1C;
            if (entity_flags & 0x100) {
                begin_pushed_actor_move(action, context, sprite, entity);
                return;
            }

            if (entity_flags & 0x80000) {
                begin_actor_move_to_target_facing(action, context, sprite, entity);
                update_actor_landing_and_trap(action, context, sprite, entity);
                return;
            }

            if (entity->unk_6D == 0) {
                return;
            }

            if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
                if ((check_entity_relation(entity,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }

            update_actor_status_and_food(entity);
            on_actor_status_updated(entity);

            if ((get_entity_effect_value(entity, 1) << 16) != 0) {
                TileObject *origin;
                s8 coordinate;

                origin = &D_80082E80;
                coordinate = ((Rec_D_80082E80 *)sprite)->unk_26.as_s8;
                if ((((coordinate == origin->unk_026) &&
                            (coordinate >= 0)) ||
                     (get_tile_chebyshev_distance(origin, sprite) < 2)) &&
                    ((generate_random_value() & 7) == 0)) {
                    clear_slots_of_type(entity, 1);
                }
            }

            if ((get_entity_effect_value(entity, 1) << 16) != 0) {
                return;
            }
        }

        {
            u8 *direction_anims;

            direction_anims = D_80174520;
            (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
            select_sprite_entry(sprite,
                direction_anims[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            entity->flags1C &= ~0x200;
            ((E_80173254_S_80173254_0 *)action)->unk_8C = update_actor_behavior_facing_and_animation_2;
        }
    }
}
