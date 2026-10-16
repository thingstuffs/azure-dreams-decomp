#include "modules/dungeon_ovl_ccb000.h"

void func_8015B72C(void *actor_in, s32 actor_index, void *target, void *entity_in)
{
    EntityRec *entity = entity_in;
    s32 state;
    s32 entity_flags;
    s32 direction;
    DungeonGlobalStatus *shared_state;
    state = ((CL_CCB000_8017372C_S_801740DC_0 *)actor_in)->unk_9B;
    switch (state) {
    case 0:
    if (!(((Rec_D_80082E80 *)target)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &dungeonStatus;
        shared_counter->unk_0A--;
    }
    (*(void * *)((u8 *)target + 0x2C)) = D_8015D2FC;
    direction = (gameWork.view.viewAngle + entity->facing + 0x100) >> 9;
    func_80047784(target, D_8015D2FC[direction & 7], 0);
    ((CL_CCB000_8017372C_S_801740DC_0 *)actor_in)->unk_9B++;
    return;

    case 1:
    if (entity->tileY != 0) {
        DungeonGlobalStatus *shared_counter;

        (*(void * *)((u8 *)target + 0x2C)) = D_8015D304;
        direction = (gameWork.view.viewAngle + entity->facing + 0x100) >> 9;
        func_80047784(target, D_8015D304[direction & 7], 0);
        shared_counter = &dungeonStatus;
        shared_counter->unk_0A++;
        ((CL_CCB000_8017372C_S_801740DC_0 *)actor_in)->unk_9B++;
        return;
    } else {
        shared_state = &dungeonStatus;
        if (shared_state->flags & 0x1000) {
            return;
        }
        if (entity->unk_64 != 0) {
            if (dungeonBeginReadyActorDirectionalAction(actor_in, actor_index, target, 0) != 0) {
                return;
            }
        }
        if ((func_800A2C34(entity) << 16) != 0) {
            return;
        }
        entity_flags = entity->flags1C;
        if (entity_flags & 0x100) {
            dungeonBeginPushedActorMove(actor_in, actor_index, target, entity);
            return;
        }
        if (entity_flags & 0x80000) {
            func_800AA888(actor_in, actor_index, target, entity);
            func_8015BA38(actor_in, actor_index, target, entity);
            return;
        }
        if (entity->unk_6D == 0) {
            return;
        }
        if ((func_800A2C34(entity) << 16) != 0) {
            if ((dungeonCheckEntityRelation(entity,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                return;
            }
            func_800A9A0C(entity);
        } else {
            func_800A9A0C(entity);
        }
        func_800A9A04(entity);
        if (entity->tileY == 0) {
            return;
        }
        (*(void * *)((u8 *)target + 0x2C)) = D_8015D304;
        direction = (gameWork.view.viewAngle + entity->facing + 0x100) >> 9;
        func_80047784(target, D_8015D304[direction & 7], 0);
        shared_state->unk_0A++;
    }
    ((CL_CCB000_8017372C_S_801740DC_0 *)actor_in)->unk_9B++;
    return;

    case 2:
    if (!(((Rec_D_80082E80 *)target)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &dungeonStatus;
        shared_counter->unk_0A--;
    }
    ((CL_CCB000_8017372C_S_801740DC_0 *)actor_in)->unk_8C = func_8015902C;

    return;
    default:
        return;
    }
}
