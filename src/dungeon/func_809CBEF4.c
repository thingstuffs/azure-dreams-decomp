#include "modules/dungeon_resource03_slot0.h"

void func_801736F4(void *controller, void *context, void *sprite, EntityRec *entity)
{
    s32 state;

    state = ((Rec_func_801736F4_arg0 *)controller)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }

        g_dungeon_status.unk_0A--;
        direction_anims = ((u8 *)D_80173CDC);
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
        select_sprite_entry(sprite,
            direction_anims[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (entity->tileY != 0) {

            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80173CD4);
            select_sprite_entry(sprite,
                ((u8 *)D_80173CD4)[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            (((u32)entity->flags1C)) |= 0x40000;
            g_dungeon_status.unk_0A++;
            ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }

        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(controller, context, sprite, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)entity->flags1C);
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(controller, context, sprite, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, sprite, entity);
            func_80173A30(controller, context, sprite, entity);
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
        if (entity->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80173CD4);
        select_sprite_entry(sprite,
            ((u8 *)D_80173CD4)[((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        g_dungeon_status.unk_0A++;
        ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
    }
        break;
    case 2:
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000) {

            g_dungeon_status.unk_0A--;
            entity->flags1C &= ~0x208;
            ((Rec_func_801736F4_arg0 *)controller)->unk_8C = ((void *)func_80170E54);
        }

        return;
    }
}
