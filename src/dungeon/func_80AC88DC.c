#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_801743E8(void *, s32, void *, void *);

extern s32 D_80171728;
extern u8 D_80174E4C[];
extern u8 D_80174E54[];


typedef struct S_801740DC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801740DC_0;   /* arg0 in func_801740DC */


/* Updates actor state, directional animation, and the shared transition counter. */
void func_801740DC(void *actor_in, s32 actor_index_in, void *target_in, void *entity_in)
{
    register s32 actor_index ASM_REG("$19") = actor_index_in;
    void *target = target_in;
    EntityRec *entity = entity_in;
    s32 state;
    s32 entity_flags;
    s32 direction;
    DungeonGlobalStatus *shared_state;
    state = ((S_801740DC_0 *)actor_in)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        return;
    }
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    if (!(((Rec_D_80082E80 *)target)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &dungeonStatus;
        shared_counter->unk_0A--;
    }
    (*(void * *)((u8 *)target + 0x2C)) = D_80174E4C;
    direction = (gameWork.view.viewAngle + entity->facing + 0x100) >> 9;
    func_80047784(target, D_80174E4C[direction & 7], 0);
    goto increment_state;

state_one:
    if (entity->tileY != 0) {
        DungeonGlobalStatus *shared_counter;

        (*(void * *)((u8 *)target + 0x2C)) = D_80174E54;
        direction = (gameWork.view.viewAngle + entity->facing + 0x100) >> 9;
        func_80047784(target, D_80174E54[direction & 7], 0);
        shared_counter = &dungeonStatus;
        shared_counter->unk_0A++;
    } else {
        shared_state = &dungeonStatus;
        if (shared_state->flags & 0x1000) {
            return;
        }
        if (entity->unk_64 != 0) {
            if (func_800AA6B4(actor_in, actor_index, target, 0) != 0) {
                return;
            }
        }
        if ((func_800A2C34(entity) << 16) != 0) {
            return;
        }
        entity_flags = entity->flags1C;
        if (entity_flags & 0x100) {
            func_800AA258(actor_in, actor_index, target, entity);
            return;
        }
        if (entity_flags & 0x80000) {
            func_800AA888(actor_in, actor_index, target, entity);
            func_801743E8(actor_in, actor_index, target, entity);
            return;
        }
        if (entity->unk_6D == 0) {
            return;
        }
        if ((func_800A2C34(entity) << 16) != 0) {
            if ((func_8009A180(entity,
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
        (*(void * *)((u8 *)target + 0x2C)) = D_80174E54;
        direction = (gameWork.view.viewAngle + entity->facing + 0x100) >> 9;
        func_80047784(target, D_80174E54[direction & 7], 0);
        shared_state->unk_0A++;
    }
increment_state:
    ((S_801740DC_0 *)actor_in)->unk_9B++;
    return;

state_two:
    if (!(((Rec_D_80082E80 *)target)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &dungeonStatus;
        shared_counter->unk_0A--;
    }
    ((S_801740DC_0 *)actor_in)->unk_8C = &D_80171728;

    return;
}
