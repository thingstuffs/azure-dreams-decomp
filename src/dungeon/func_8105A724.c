#include "common.h"
#include "m2c_compat.h"

typedef struct S_80171F24_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80171F24_0;   /* arg3 in func_80171F24 */

typedef struct S_80171F24_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171F24_1;   /* arg2 in func_80171F24 */

typedef struct S_80171F24_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_80171F24_2;   /* arg0 in func_80171F24 */


void func_80047784(void *, u8, s32);
void func_8009C93C(void *, void *, s16, s32, s32);
s32 func_800A0134(s32, void *);
s32 func_800A04F0(void *, u8, u8, s16);
s32 func_800A2B5C(void *);
s32 func_800A2CB8(void *, s32);
void func_800C7930(void *, s32, s32, s32);
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80173FB8[];

s32 func_80171F24(void *arg0, s32 arg1, void *arg2, void *arg3) {
    volatile s64 frame_pad;
    s32 result;
    u16 flags;
    u16 dead_mask;

    ((S_80171F24_0 *)arg3)->unk_71 = (u8) (((S_80171F24_0 *)arg3)->unk_71 & 0x7F);
    if (D_80083462 & 0x2000) {
        goto late_failure;
    }

    result = func_800A04F0(arg3, ((S_80171F24_1 *)arg2)->unk_24,
        ((S_80171F24_1 *)arg2)->unk_25, ((S_80171F24_0 *)arg3)->unk_2A);

    if (!(((S_80171F24_2 *)arg0)->unk_98 & 0x8000)) {
        goto no_flag;
    }
    if (result != 0) {
        goto checks;
    }
early_zero:
    return 0;

no_flag:
    if ((func_800A2CB8(arg3, result) << 0x10) == 0) {
        goto return_zero;
    }

checks:
    flags = D_80083462;
    if (flags & 0x2000) {
        return -1;
    }
    if (!(((S_80171F24_0 *)arg3)->unk_46 & 0x8000)) {
        if (flags & 8) {
            return -1;
        }
    }

    if ((u32)(((0 - func_800A0134(result, arg3)) + 0x40) & 0xFFFF) < 0x81U) {
        goto range_ok;
    }
return_zero:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail branch polarity depends on it */
    return 0;

range_ok:
    if ((func_800A2B5C(arg3) << 0x10) != 0) {
        return -1;
    }

    func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300);
    if ((func_800A2B5C(arg3) << 0x10) == 0) {
        goto success;
    }

late_failure:
    return -1;

success:
    ((S_80171F24_2 *)arg0)->unk_9A = 0x11;
    ((S_80171F24_2 *)arg0)->unk_9B = 0;
    ((S_80171F24_2 *)arg0)->unk_8C = 0;
    ((S_80171F24_0 *)arg3)->unk_84 = 0x7C;
    ((S_80171F24_0 *)arg3)->unk_85 = 0;
    dead_mask = ((S_80171F24_2 *)arg0)->unk_98 & 0x8000;
    ASM_KEEP(dead_mask);   /* MATCH pin: retail basic-block layout depends on it */
    (*(u8 **)((u8 *)arg2 + 0x2C)) = D_80173FB8;
    func_80047784(arg2,
        D_80173FB8[((D_80083228 + ((S_80171F24_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80171F24_0 *)arg3)->unk_6D = (u8) (((S_80171F24_0 *)arg3)->unk_6D - 1);
    func_8009C93C(arg3, arg2, ((S_80171F24_0 *)arg3)->unk_2A, 1, 0);
    return 1;
}

/* MECHANISM: An unused volatile s64 supplies retail's eight-byte frame object,
   while explicit CFG labels preserve the early-zero and shared late-failure blocks.
   The retained dead flag mask restores three tail words; a fence at the later
   zero-return join prevents jump-threading and closes the final return-slot residue. */
