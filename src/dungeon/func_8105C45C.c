#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

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


extern s16 D_80083228[5];
extern u8 D_80173FD0[];
extern u8 D_80173FB8[];
extern s32 D_80083460[3];
extern s32 D_80170F68;
extern void *D_80170878[];
M2C_UNK func_800A2B04();
M2C_UNK func_800A48F0();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
s32 func_800A6D30();
extern u8 D_80173FD8;
extern M2C_UNK D_80173FE0;

/* Run the actor's eight-step sink animation, advancing its state and swapping the sprite each step. */
void func_80173C5C(S_80173C5C_0 *work, Rec_D_800E3D7C *part_a, Rec_D_80082E80 *part_b, Rec_D_800E3D7C *actor) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    u8 *unused_ptr;
    u16 *counters;
    s32 value;
    u16 flags;
    s32 state;
    s32 accum;
    s32 state_now;
    s32 timer;

    state = work->unk_9B;
    work->unk_96.s = (u16) (work->unk_96.s - 1);
    if (state >= 8U) {
        goto block_20;
    }
    (void)jt_keep; goto *D_80170878[(u32)(state)];
jt_c0:
jt_c4:
    func_800A56E0(0x51C);
    flags = part_b->unk_14.at00_u16.v;
    if (!(flags & 0x8000)) {
        goto block_5;
    }
    work->unk_9B = 7;
    goto block_20;
block_5:
    if (!(flags & 0xE000)) {
        goto block_20;
    }
    part_b->unk_2C.as_pu8 = &D_80173FD8;
    func_80047784(part_b, (&D_80173FD8)[((s32) (*D_80083228 + actor->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    work->unk_98 = (u16) (work->unk_98 | 8);
    part_a->unk_14.as_s32 = 0xFFF00000;
    actor->unk_1C.as_s32 = (s32) (actor->unk_1C.as_s32 & 0xF7FFFFFF);
    work->unk_A0 = 0;
    state_now = work->unk_9B;
    state = 10;
    work->unk_96.s = state;
    goto block_e60;
jt_c1:
jt_c5:
    accum = work->unk_90;
    value = work->unk_A0;
    timer = work->unk_96.u;
    work->unk_90 = accum - value;
    if (timer == 0) {
        goto block_10;
    }
    accum = value;
    value = part_a->unk_14.as_s32;
    work->unk_A0 = (s32) (accum + value);
    part_a->unk_14.as_s32 = (s32) (part_a->unk_14.as_s32 + 0x30000);
block_10:
    accum = work->unk_90;
    value = work->unk_A0;
    timer = work->unk_96.u;
    work->unk_90 = accum + value;
    if (timer > 0) {
        goto block_20;
    }
    work->unk_90 = 0;
    work->unk_98 = (u16) (work->unk_98 & 0xFFF7);
    actor->unk_1C.as_s32 = (s32) (actor->unk_1C.as_s32 | 0x8000000);
    goto block_e5c;
jt_c2:
jt_c6:
    work->unk_98 = (u16) (work->unk_98 & 0xFFF7);
    part_a->unk_14.as_s32 = 0;
    part_a->unk_10.at00_s32.v = 0;
    part_a->unk_0C.as_s32 = 0;
    func_800A2B04(part_a, part_b->unk_24, part_b->unk_25);
    part_b->unk_2C.as_pu8 = &D_80173FE0;
    func_80047784(part_b, ((u8 *) ((u32) ((((s32) (*D_80083228 + actor->unk_2A.as_s16 + 0x100) >> 9) & 7) + (u32) &D_80173FE0)))[0], 0);
    goto block_e5c;
jt_c3:
    if (!(part_b->unk_14.at00_u16.v & 0xE000)) {
        goto block_20;
    }
    part_b->unk_2C.as_pu8 = D_80173FD0;
    func_80047784(part_b, D_80173FD0[((s32) (*D_80083228 + actor->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    block_e5c:
    state_now = work->unk_9B;
    block_e60:
    work->unk_9B = (u8) (state_now + 1);
    goto block_20;
jt_c7:
    if (!(part_b->unk_14.at00_u16.v & 0xE000)) {
        goto block_20;
    }
    part_b->unk_2C.as_pu8 = D_80173FB8;
    func_80047784(part_b, D_80173FB8[((s32) (*D_80083228 + actor->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    counters = (u16 *) D_80083460;
    ((S_80173C5C_4 *)counters)->unk_0A = (u16) (((S_80173C5C_4 *)counters)->unk_0A - 1);
    func_800A4ACC(actor);
    actor->unk_6D.as_s8 = 0;
    actor->unk_44.at02_u16.v = (u16) (actor->unk_44.at02_u16.v & 0x7FFF);
    work->unk_8C = &D_80170F68;
    work->unk_98 = (u16) (work->unk_98 | 0x8000);
    work->unk_AE = (s16) ((func_800A6D30() & 7) + 8);
    func_800A48F0(actor, 0x1A, (s8) work->unk_AE);
block_20:
    return;
}
