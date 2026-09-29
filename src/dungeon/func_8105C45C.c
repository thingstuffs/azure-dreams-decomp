#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80173C5C_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    u8 pad_A4[0xA];
    s16 unk_AE;
} S_80173C5C_0;   /* work in func_80173C5C */




typedef struct S_80173C5C_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173C5C_4;   /* counters in func_80173C5C */


extern u8 D_80173FD0[];
extern u8 D_80173FB8[];
extern s32 D_80170F68;
M2C_UNK func_800A2B04();
M2C_UNK func_800A48F0();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
s32 func_800A6D30();
extern u8 D_80173FD8;
extern M2C_UNK D_80173FE0;

/* Run the actor's eight-step sink animation, advancing its state and swapping the sprite each step. */
void func_80173C5C(S_80173C5C_0 *work, EntityRec *part_a, Rec_D_80082E80 *part_b, EntityRec *actor) {
    u8 *unused_ptr;
    s32 value;
    u16 flags;
    s32 state;
    s32 accum;
    s32 state_now;
    s32 timer;

    state = work->unk_9B;
    work->unk_96.s = (u16) (work->unk_96.s - 1);
    switch (state) {
case 0:
case 4:
    func_800A56E0(0x51C);
    flags = part_b->unk_14.at00_u16.v;
    if (!(flags & 0x8000)) {
        goto block_5;
    }
    work->unk_9B = 7;
    return;
block_5:
    if (!(flags & 0xE000)) {
        return;
    }
    part_b->unk_2C.as_pu8 = &D_80173FD8;
    func_80047784(part_b, (&D_80173FD8)[((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
    work->unk_98 = (u16) (work->unk_98 | 8);
    part_a->flags14 = 0xFFF00000;
    actor->flags1C = (s32) (actor->flags1C & 0xF7FFFFFF);
    work->unk_A0 = 0;
    state_now = work->unk_9B;
    state = 10;
    work->unk_96.s = state;
    goto block_e60;
case 1:
case 5:
    accum = work->unk_90;
    value = work->unk_A0;
    timer = work->unk_96.u;
    work->unk_90 = accum - value;
    if (timer == 0) {
        goto block_10;
    }
    accum = value;
    value = part_a->flags14;
    work->unk_A0 = (s32) (accum + value);
    part_a->flags14 = (s32) (part_a->flags14 + 0x30000);
block_10:
    accum = work->unk_90;
    value = work->unk_A0;
    timer = work->unk_96.u;
    work->unk_90 = accum + value;
    if (timer > 0) {
        return;
    }
    work->unk_90 = 0;
    work->unk_98 = (u16) (work->unk_98 & 0xFFF7);
    actor->flags1C = (s32) (actor->flags1C | 0x8000000);
    goto block_e5c;
case 2:
case 6:
    work->unk_98 = (u16) (work->unk_98 & 0xFFF7);
    part_a->flags14 = 0;
    part_a->unk_10 = 0;
    part_a->unk_0C = 0;
    func_800A2B04(part_a, part_b->unk_24, part_b->unk_25);
    part_b->unk_2C.as_pu8 = &D_80173FE0;
    func_80047784(part_b, ((u8 *) ((u32) ((((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7) + (u32) &D_80173FE0)))[0], 0);
    goto block_e5c;
case 3:
    if (!(part_b->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    part_b->unk_2C.as_pu8 = D_80173FD0;
    func_80047784(part_b, D_80173FD0[((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
    block_e5c:
    state_now = work->unk_9B;
    block_e60:
    work->unk_9B = (u8) (state_now + 1);
    return;
case 7:
    if (!(part_b->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    part_b->unk_2C.as_pu8 = D_80173FB8;
    func_80047784(part_b, D_80173FB8[((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
    dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
    func_800A4ACC(actor);
    actor->unk_6D = 0;
    actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
    work->unk_8C = &D_80170F68;
    work->unk_98 = (u16) (work->unk_98 | 0x8000);
    work->unk_AE = (s16) ((func_800A6D30() & 7) + 8);
    func_800A48F0(actor, 0x1A, (s8) work->unk_AE);
    return;
    default:
        return;
    }
}
