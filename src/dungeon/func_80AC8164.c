#include "common.h"

typedef struct S_80173964_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173964_0;   /* arg0 in func_80173964 */

typedef struct S_80173964_1 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x1];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
} S_80173964_1;   /* arg3 in func_80173964 */

typedef struct S_80173964_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80173964_2;   /* arg2 in func_80173964 */

typedef struct S_80173964_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173964_3;   /* arg1 in func_80173964 */



extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80171728;
extern u8 D_80174DEC[];
extern u8 D_80174DFC[];
extern u8 D_80174E24[];

void func_80173964(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s16 timer;
    u16 counter;
    u8 next_state;
    s32 ax;
    s32 dy;
    s32 ax2;
    s32 dy2;
    s32 global_value;
    s32 *global_base;

    state = ((S_80173964_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    func_800AD4D0(arg3);
    ((S_80173964_0 *)arg0)->unk_96.s = 12;
    ((S_80173964_0 *)arg0)->unk_9B++;
    if (((S_80173964_1 *)arg3)->unk_28 == 0) {
        goto initialize;
    }
    if (((S_80173964_2 *)arg2)->unk_14 & 0x8000) {
        ((S_80173964_0 *)arg0)->unk_96.s = 0;
        ((S_80173964_0 *)arg0)->unk_9B = 3;
    }
    goto done;

state_1:
    counter = ((S_80173964_0 *)arg0)->unk_96.u - 1;
    ((S_80173964_0 *)arg0)->unk_96.u = counter;
    timer = counter;
    if (timer >= 11) {
        ((S_80173964_3 *)arg1)->unk_0C =
            *(s16 *)((u8 *)&D_8006CCD8 +
                     ((((S_80173964_1 *)arg3)->unk_6A >> 8) & 0xE)) << 20;
        ((S_80173964_3 *)arg1)->unk_10 =
            *(s16 *)((u8 *)&D_8006CCE8 +
                     ((((S_80173964_1 *)arg3)->unk_6A >> 8) & 0xE)) << 20;
        ((S_80173964_2 *)arg2)->unk_14 |= 0x800;
        goto done;
    }
    if (timer >= 7) {
        ((S_80173964_3 *)arg1)->unk_0C /= 4;
        ((S_80173964_3 *)arg1)->unk_10 /= 4;
        goto done;
    }
    if (timer >= 2) {
        ((S_80173964_3 *)arg1)->unk_10 = 0;
        ((S_80173964_3 *)arg1)->unk_0C = 0;
        goto done;
    }
    if (timer == state) {
        ((S_80173964_2 *)arg2)->unk_14 &= 0xF7FF;
        goto done;
    }
    if (timer != 0) {
        goto done;
    }
    next_state = ((S_80173964_0 *)arg0)->unk_9B;
    timer = 4;
    ((S_80173964_0 *)arg0)->unk_96.s = timer;
    goto increment_state;

state_2:
    if (((S_80173964_1 *)arg3)->unk_28 != 0) {
        goto calculate;
    }

initialize:
    ((S_80173964_3 *)arg1)->unk_14 = 0;
    ((S_80173964_3 *)arg1)->unk_10 = 0;
    ((S_80173964_3 *)arg1)->unk_0C = 0;
    func_800AAA54(arg0, arg1, arg2, D_80174E24);
    goto done;

calculate:
    timer = ((S_80173964_0 *)arg0)->unk_96.s;
    if (timer != 0) {
        ax = ((S_80173964_2 *)arg2)->unk_24 << 6;
        dy = ((S_80173964_3 *)arg1)->unk_02 - 0x20;
        ((S_80173964_3 *)arg1)->unk_0C = ((ax - dy) << 16) / timer;
        ax2 = ((S_80173964_2 *)arg2)->unk_25 << 6;
        dy2 = ((S_80173964_3 *)arg1)->unk_06 - 0x20;
        ((S_80173964_3 *)arg1)->unk_10 =
            ((ax2 - dy2) << 16) / ((S_80173964_0 *)arg0)->unk_96.s;
    }
    counter = ((S_80173964_0 *)arg0)->unk_96.u;
    ((S_80173964_0 *)arg0)->unk_96.u = counter - 1;
    if ((s32)(counter << 16) > 0) {
        goto done;
    }
    ((S_80173964_3 *)arg1)->unk_14 = 0;
    ((S_80173964_3 *)arg1)->unk_10 = 0;
    ((S_80173964_3 *)arg1)->unk_0C = 0;
    next_state = ((S_80173964_0 *)arg0)->unk_9B;

increment_state:
    ((S_80173964_0 *)arg0)->unk_9B = next_state + 1;
    goto done;

state_3:
    ((S_80173964_3 *)arg1)->unk_14 = 0;
    ((S_80173964_3 *)arg1)->unk_10 = 0;
    ((S_80173964_3 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_80173964_2 *)arg2)->unk_24, ((S_80173964_2 *)arg2)->unk_25);
    if (((S_80173964_2 *)arg2)->unk_2C == D_80174DFC) {
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174DEC;
        func_80047784(
            arg2,
            D_80174DEC[((D_80083228 + ((S_80173964_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
    global_base = &D_80083460;
    global_value = global_base[4];
    if (global_value == (s32)((u8 *)arg3 - 0x20)) {
        global_base[4] = global_value & 0x7FFFFFFF;
    }
    ((S_80173964_0 *)arg0)->unk_8C = &D_80171728;

done:
    return;
}

/* MECHANISM: Four live arguments naturally produce the 0x28 frame and s1/s0/s2/s3 save roles.
   A distinct u8 next_state plus timer-held constant 4 fixes v0/v1 lifetimes and the bgtz store slot.
   The named D_80083460 pointer forces retail's split lui/addiu base before the final field load. */
