#include "modules/dungeon_resource16_slot0.h"

void func_80173114(void *actor, void *context, void *animation, EntityRec *entity)
{
    s32 state;

    state = ((Rec_func_8017360C_arg0 *)actor)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        direction_anims = ((u8 *)D_8017425C);
        (*(void * *)((u8 *)animation + 0x2C)) = direction_anims;
        select_sprite_entry(animation,
            direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (entity->tileY != 0) {

            (*(void * *)((u8 *)animation + 0x2C)) = ((u8 *)D_80174264);
            select_sprite_entry(animation,
                ((u8 *)D_80174264)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            entity->flags1C |= 0x40000;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
            ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }

        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, animation, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)entity->flags1C);
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor, context, animation, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            u16 stored_value;
            u16 pending_decrement;

            begin_actor_move_to_target_facing(actor, context, animation, entity);
            stored_value = ((Rec_func_8017360C_arg0 *)actor)->unk_92;
            pending_decrement = ((Rec_func_8017360C_arg0 *)actor)->unk_A2;
            ((Rec_func_8017360C_arg0 *)actor)->unk_A2 = 0;
            ((Rec_func_8017360C_arg0 *)actor)->unk_9E = 0;
            ((Rec_func_8017360C_arg0 *)actor)->unk_92 = stored_value - pending_decrement;
            func_80173468(actor, context, animation, entity);
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

        (*(void * *)((u8 *)animation + 0x2C)) = ((u8 *)D_80174264);
        select_sprite_entry(animation,
            ((u8 *)D_80174264)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
    }
        break;
    case 2:
        if (((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000) {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
            entity->flags1C &= ~8;
            ((Rec_func_8017360C_arg0 *)actor)->unk_8C.as_pv = ((void *)update_actor_state_and_dispatch_transition);
        }

        return;
    }
}
