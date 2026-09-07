#include "common.h"

typedef struct S_8008DBE8_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    s16 unk_04;
} S_8008DBE8_0;   /* status in func_8008DBE8 */

typedef struct S_8008DBE8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8008DBE8_1;   /* arg2 in func_8008DBE8 */

typedef struct S_8008DBE8_2 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8008DBE8_2;   /* arg1 in func_8008DBE8 */

typedef struct S_8008DBE8_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x12];
    u16 unk_A2;
} S_8008DBE8_3;   /* arg0 in func_8008DBE8 */

typedef struct S_8008DBE8_4 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_8008DBE8_4;   /* arg3 in func_8008DBE8 */

typedef struct S_8008DBE8_5 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_8008DBE8_5;   /* late_status in func_8008DBE8 */


extern void func_80048A44(void *, u8, s32, s32);
extern void func_8008D94C(void *, void *, void *, void *);
extern void func_8008DCEC(void);
extern void func_8008DDC8(void);
extern s32 func_80094F74(void *, void *, void *, void *);
extern void func_800A2B04(void *, u8, u8);

extern u16 D_80013714;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008ACDC;
extern u8 D_800DD050[];


void func_8008DBE8(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *status = &D_80083460;
    void *late_status;
    u32 page;
    s32 mode;
    s32 quotient;
    s32 coordinate;
    s32 divisor2;
    s16 timer;
    u16 flags;

    if (((S_8008DBE8_0 *)status)->unk_02 & 0x80) {
        ((S_8008DBE8_0 *)status)->unk_04 = 0;
    }

    timer = ((S_8008DBE8_0 *)status)->unk_04;
    if (timer != 0) {
        quotient =
            ((((((S_8008DBE8_1 *)arg2)->unk_24 << 6) + 0x20) << 16) -
             ((S_8008DBE8_2 *)arg1)->unk_00) /
            timer;
        coordinate = ((S_8008DBE8_2 *)arg1)->unk_04;
        ((S_8008DBE8_2 *)arg1)->unk_0C = quotient;
        ASM_MEM_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
        divisor2 = ((S_8008DBE8_0 *)status)->unk_04;
        ((S_8008DBE8_2 *)arg1)->unk_10 =
            ((((((S_8008DBE8_1 *)arg2)->unk_25 << 6) + 0x20) << 16) -
             coordinate) /
            divisor2;
    }

    if (((S_8008DBE8_3 *)arg0)->unk_A2 & 0x100) {
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        mode = ((S_8008DBE8_0 *)status)->unk_04;
        if (D_80013714 & 8) {
            if (mode != 3) {
                func_8008DCEC();
                return;
            }
        } else if (mode != 6) {
            goto continue_update;
        }

        func_8008D94C(arg0, arg1, arg2, arg3);
        return;
    }

continue_update:
    flags = ((S_8008DBE8_3 *)arg0)->unk_A2;
    if (!(flags & 0x10)) {
        if (((S_8008DBE8_1 *)arg2)->unk_2C != D_800DD050) {
            ((S_8008DBE8_3 *)arg0)->unk_A2 = flags | 1;
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_800DD050;
            func_80048A44(
                arg2,
                D_800DD050[((D_80083228 + ((S_8008DBE8_4 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0,
                1);
        }
    }

    page = 0x80080000;
    ASM_KEEP(page);   /* MATCH pin: keeps a constant in a register as retail does */
    late_status = (void *)(page + 0x3460);
    timer = ((S_8008DBE8_5 *)late_status)->unk_04 - 1;
    ((S_8008DBE8_5 *)late_status)->unk_04 = timer;
    if (timer > 0) {
        return;
    }

    ((S_8008DBE8_5 *)late_status)->unk_04 = 0;
    ((S_8008DBE8_2 *)arg1)->unk_14 = 0;
    ((S_8008DBE8_2 *)arg1)->unk_10 = 0;
    ((S_8008DBE8_2 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_8008DBE8_1 *)arg2)->unk_24, ((S_8008DBE8_1 *)arg2)->unk_25);

    ((S_8008DBE8_1 *)arg2)->unk_14 |= 0x4000;
    if ((s16)func_80094F74(arg0, arg1, arg2, arg3) > 0) {
        ((S_8008DBE8_3 *)arg0)->unk_8C = (s32)&D_8008ACDC;
    }
}

/* MECHANISM: Separate s32 quotient/coordinate/divisor pseudos plus ASM_MEM_BARRIER reuse
   $a0 for the coordinate preload and force the signed timer reload into $v1.
   Widened mode + ASM_SCHED_BARRIER preserve the branch nop; zero-arg DCEC and
   the post-merge pinned page reproduce the tail ABI and late $v0 coloring. */
