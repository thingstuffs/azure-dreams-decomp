#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"


extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_801743E8(void *, s32, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80171728;
extern u8 D_80174E4C[];
extern u8 D_80174E54[];


typedef struct S_801740DC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801740DC_0;   /* arg0 in func_801740DC */


typedef struct S_801740DC_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801740DC_2;   /* counter_base in func_801740DC */


typedef struct S_801740DC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801740DC_4;   /* global_base in func_801740DC */


typedef struct S_801740DC_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801740DC_6;   /* counter_base2 in func_801740DC */

/* Updates actor state, directional animation, and the shared transition counter. */
void func_801740DC(void *actor_in, s32 actor_index_in, void *target_in, void *entity_in)
{
    register s32 actor_index ASM_REG("$19") = actor_index_in;
    register void *target ASM_REG("$17") = target_in;
    void *entity = entity_in;
    s32 state;
    s32 entity_flags;
    s32 direction;
    u8 *shared_state;
    state = ((S_801740DC_0 *)actor_in)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (!(((Rec_D_80082E80 *)target)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    {
        u8 *shared_counter;

        shared_counter = (u8 *)&D_80083460;
        ((S_801740DC_2 *)shared_counter)->unk_0A--;
    }
    (*(void * *)((u8 *)target + 0x2C)) = D_80174E4C;
    direction = (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(target, D_80174E4C[direction & 7], 0);
    goto increment_state;

state_one:
    if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v != 0) {
        u8 *shared_counter;

        (*(void * *)((u8 *)target + 0x2C)) = D_80174E54;
        direction = (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9;
        func_80047784(target, D_80174E54[direction & 7], 0);
        shared_counter = (u8 *)&D_80083460;
        ((S_801740DC_2 *)shared_counter)->unk_0A++;
        goto increment_state;
    }

    shared_state = (u8 *)&D_80083460;
    if (((S_801740DC_4 *)shared_state)->unk_02 & 0x1000) {
        goto done;
    }
    ASM_CLOBBER("$5");
    ASM_CLOBBER("$6");
    if (((Rec_D_800E3D7C *)entity)->unk_64.as_s16 != 0) {
        if (func_800AA6B4(actor_in, actor_index, target, 0) != 0) {
            goto done;
        }
    }
    if ((func_800A2C34(entity) << 16) != 0) {
        goto done;
    }
    entity_flags = ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32;
    if (entity_flags & 0x100) {
        func_800AA258(actor_in, actor_index, target, entity);
        goto done;
    }
    if (entity_flags & 0x80000) {
        func_800AA888(actor_in, actor_index, target, entity);
        func_801743E8(actor_in, actor_index, target, entity);
        goto done;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 == 0) {
        goto done;
    }
    if ((func_800A2C34(entity) << 16) != 0) {
        if ((func_8009A180(entity,
                (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
            goto done;
        }
        func_800A9A0C(entity);
    } else {
        func_800A9A0C(entity);
    }
    func_800A9A04(entity);
    if (((Rec_D_800E3D7C *)entity)->unk_24.at01_u8.v == 0) {
        goto done;
    }
    (*(void * *)((u8 *)target + 0x2C)) = D_80174E54;
    direction = (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(target, D_80174E54[direction & 7], 0);
    ((S_801740DC_4 *)shared_state)->unk_0A++;

increment_state:
    ((S_801740DC_0 *)actor_in)->unk_9B++;
    goto done;

state_two:
    if (!(((Rec_D_80082E80 *)target)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    {
        u8 *shared_counter;

        shared_counter = (u8 *)&D_80083460;
        ((S_801740DC_6 *)shared_counter)->unk_0A--;
    }
    ((S_801740DC_0 *)actor_in)->unk_8C = &D_80171728;

done:
    return;
}
