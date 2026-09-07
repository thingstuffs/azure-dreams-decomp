#include "common.h"
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

typedef struct S_801740DC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_801740DC_1;   /* arg2 in func_801740DC */

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

/* Advance actor state, updating directional animation and the shared counter. */
void func_801740DC(void *actor_in, s32 actor_index_in, void *target_in, void *entity_in)
{
    register void *actor ASM_REG("$18") = actor_in;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 actor_index ASM_REG("$19") = actor_index_in;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *target ASM_REG("$17") = target_in;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *entity ASM_REG("$16") = entity_in;   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 state;
    s32 entity_flags;
    s32 direction_index;
    u8 *shared_state;
    state = ((S_801740DC_0 *)actor)->unk_9B;
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
    if (!(((S_801740DC_1 *)target)->unk_14 & 0xE000)) {
        goto done;
    }
    {
        u8 *counter_base;

        counter_base = (u8 *)&D_80083460;
        ((S_801740DC_2 *)counter_base)->unk_0A--;
    }
    (*(void * *)((u8 *)target + 0x2C)) = D_80174E4C;
    direction_index = (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.s + 0x100) >> 9;
    func_80047784(target, D_80174E4C[direction_index & 7], 0);
    goto increment_state;

state_one:
    if (((Rec_D_800E3D7C *)entity)->unk_24.at01.v != 0) {
        u8 *counter_base;

        (*(void * *)((u8 *)target + 0x2C)) = D_80174E54;
        direction_index = (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.s + 0x100) >> 9;
        func_80047784(target, D_80174E54[direction_index & 7], 0);
        counter_base = (u8 *)&D_80083460;
        ((S_801740DC_2 *)counter_base)->unk_0A++;
        goto increment_state;
    }

    shared_state = (u8 *)&D_80083460;
    if (((S_801740DC_4 *)shared_state)->unk_02 & 0x1000) {
        goto done;
    }
    ASM_CLOBBER("$4");   /* MATCH pin: retail basic-block layout depends on it */
    ASM_CLOBBER("$5");   /* MATCH pin: retail basic-block layout depends on it */
    ASM_CLOBBER("$6");   /* MATCH pin: retail basic-block layout depends on it */
    if (((Rec_D_800E3D7C *)entity)->unk_64.s != 0) {
        if (func_800AA6B4(actor, actor_index, target, 0) != 0) {
            goto done;
        }
    }
    if ((func_800A2C34(entity) << 16) != 0) {
        goto done;
    }
    entity_flags = ((Rec_D_800E3D7C *)entity)->unk_1C.s;
    if (entity_flags & 0x100) {
        func_800AA258(actor, actor_index, target, entity);
        goto done;
    }
    if (entity_flags & 0x80000) {
        func_800AA888(actor, actor_index, target, entity);
        func_801743E8(actor, actor_index, target, entity);
        goto done;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_6D.s == 0) {
        goto done;
    }
    if ((func_800A2C34(entity) << 16) != 0) {
        if ((func_8009A180(entity,
                (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.p + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(entity);
    func_800A9A04(entity);
    if (((Rec_D_800E3D7C *)entity)->unk_24.at01.v == 0) {
        goto done;
    }
    (*(void * *)((u8 *)target + 0x2C)) = D_80174E54;
    direction_index = (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.s + 0x100) >> 9;
    func_80047784(target, D_80174E54[direction_index & 7], 0);
    ((S_801740DC_4 *)shared_state)->unk_0A++;

increment_state:
    ((S_801740DC_0 *)actor)->unk_9B++;
    goto done;

state_two:
    if (!(((S_801740DC_1 *)target)->unk_14 & 0xE000)) {
        goto done;
    }
    {
        u8 *counter_base;

        counter_base = (u8 *)&D_80083460;
        ((S_801740DC_6 *)counter_base)->unk_0A--;
    }
    ((S_801740DC_0 *)actor)->unk_8C = &D_80171728;

done:
    if (0) {
    }
    return;
}

/* MECHANISM: Four pinned parameter locals, declared in retail emission order, produce the
   0x28 frame and s2/a0, s3/a1, s1/a2 saves while delaying s0/a3 into the branch slot.
   Clobbering incoming a0-a2 at the call-group dominator forces retail's three ABI reload moves. */
