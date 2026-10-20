#include "modules/dungeon_ovl_cd7000.h"

void func_8014F72C(void *actor_in, s32 actor_index, void *target, void *entity_in)
{
    EntityRec *entity = entity_in;
    s32 state;
    s32 entity_flags;
    s32 direction;
    DungeonGlobalStatus *shared_state;
    state = ((CL_CD7000_8017372C_S_801740DC_0 *)actor_in)->unk_9B;
    switch (state) {
    case 0:
    if (!(((Rec_D_80082E80 *)target)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &g_dungeon_status;
        shared_counter->unk_0A--;
    }
    (*(void * *)((u8 *)target + 0x2C)) = D_801512FC;
    direction = (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9;
    select_sprite_entry(target, D_801512FC[direction & 7], 0);
    ((CL_CD7000_8017372C_S_801740DC_0 *)actor_in)->unk_9B++;
    return;

    case 1:
    if (entity->tileY != 0) {
        DungeonGlobalStatus *shared_counter;

        (*(void * *)((u8 *)target + 0x2C)) = D_80151304;
        direction = (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(target, D_80151304[direction & 7], 0);
        shared_counter = &g_dungeon_status;
        shared_counter->unk_0A++;
        ((CL_CD7000_8017372C_S_801740DC_0 *)actor_in)->unk_9B++;
        return;
    } else {
        shared_state = &g_dungeon_status;
        if (shared_state->flags & 0x1000) {
            return;
        }
        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor_in, actor_index, target, 0) != 0) {
                return;
            }
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }
        entity_flags = entity->flags1C;
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor_in, actor_index, target, entity);
            return;
        }
        if (entity_flags & 0x80000) {
            begin_actor_move_to_target_facing(actor_in, actor_index, target, entity);
            func_8014FA38(actor_in, actor_index, target, entity);
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
            update_actor_status_and_food(entity);
        } else {
            update_actor_status_and_food(entity);
        }
        on_actor_status_updated(entity);
        if (entity->tileY == 0) {
            return;
        }
        (*(void * *)((u8 *)target + 0x2C)) = D_80151304;
        direction = (g_game_work.view.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(target, D_80151304[direction & 7], 0);
        shared_state->unk_0A++;
    }
    ((CL_CD7000_8017372C_S_801740DC_0 *)actor_in)->unk_9B++;
    return;

    case 2:
    if (!(((Rec_D_80082E80 *)target)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &g_dungeon_status;
        shared_counter->unk_0A--;
    }
    ((CL_CD7000_8017372C_S_801740DC_0 *)actor_in)->unk_8C = func_8014D02C;

    return;
    default:
        return;
    }
}
