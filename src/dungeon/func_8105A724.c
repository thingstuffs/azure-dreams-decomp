#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"





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

    ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 & 0x7F);
    if (D_80083462 & 0x2000) {
        goto late_failure;
    }

    result = func_800A04F0(arg3, ((Rec_D_80082E80 *)arg2)->unk_24,
        ((Rec_D_80082E80 *)arg2)->unk_25, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16);

    if (!(((Rec_func_800A9E70_arg0 *)arg0)->unk_98 & 0x8000)) {
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
    if (!(((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000)) {
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
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_s8 = 0x11;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_s8 = 0;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
    ((Rec_D_800E3D7C *)arg3)->unk_84.as_s8 = 0x7C;
    ((Rec_D_800E3D7C *)arg3)->unk_85.as_s8 = 0;
    dead_mask = ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 & 0x8000;
    ASM_KEEP(dead_mask);   /* MATCH pin: retail basic-block layout depends on it */
    (*(u8 **)((u8 *)arg2 + 0x2C)) = D_80173FB8;
    func_80047784(arg2,
        D_80173FB8[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 - 1);
    func_8009C93C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1, 0);
    return 1;
}

/* MECHANISM: An unused volatile s64 supplies retail's eight-byte frame object,
   while explicit CFG labels preserve the early-zero and shared late-failure blocks.
   The retained dead flag mask restores three tail words; a fence at the later
   zero-return join prevents jump-threading and closes the final return-slot residue. */
