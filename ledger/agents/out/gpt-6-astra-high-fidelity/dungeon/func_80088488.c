#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_8008ACDC_arg0.h"

extern void func_80048A44(void *, u8, s32, s32);
extern void func_8008D94C(void *, void *, void *, void *);
extern s32 func_80094F74(void *, void *, void *, void *);
extern void func_800A2B04(void *, u8, u8);

extern u16 D_80013714;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008ACDC;
extern u8 D_800DD050[];



typedef struct S_8008DBE8_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    s16 unk_04;
} S_8008DBE8_0;   /* status in func_8008DBE8 */





typedef struct S_8008DBE8_5 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_8008DBE8_5;   /* late_status in func_8008DBE8 */

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
            ((((((Rec_D_80082E80 *)arg2)->unk_24 << 6) + 0x20) << 16) -
             ((Rec_D_800E3D7C *)arg1)->unk_00.at00_s32.v) /
            timer;
        coordinate = ((Rec_D_800E3D7C *)arg1)->unk_04.at00_s32.v;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = quotient;
        divisor2 = ((S_8008DBE8_0 *)status)->unk_04;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v =
            ((((((Rec_D_80082E80 *)arg2)->unk_25 << 6) + 0x20) << 16) -
             coordinate) /
            divisor2;
    }

    if (((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 & 0x100) {
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        mode = ((S_8008DBE8_0 *)status)->unk_04;
        if (D_80013714 & 8) {
            if (mode != 3) {
                ASM_SCHED_BARRIER(); /* MATCH: Keep the mode checks separate and jump to the shared update. */
                goto continue_update;
            }
        } else if (mode != 6) {
            goto continue_update;
        }

        func_8008D94C(arg0, arg1, arg2, arg3);
        return;
    }

continue_update:
    flags = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2;
    if (!(flags & 0x10)) {
        if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 != D_800DD050) {
            ((Rec_func_8008ACDC_arg0 *)arg0)->unk_A2 = flags | 1;
            (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_800DD050;
            func_80048A44(
                arg2,
                D_800DD050[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0,
                1);
        }
    }

    page = 0x80080000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    late_status = (void *)(page + 0x3460);
    timer = ((S_8008DBE8_5 *)late_status)->unk_04 - 1;
    ((S_8008DBE8_5 *)late_status)->unk_04 = timer;
    if (timer > 0) {
        return;
    }

    ((S_8008DBE8_5 *)late_status)->unk_04 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);

    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x4000;
    if ((s16)func_80094F74(arg0, arg1, arg2, arg3) > 0) {
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_s32 = (s32)&D_8008ACDC;
    }
}

/* MECHANISM: Separate s32 quotient/coordinate/divisor pseudos plus ASM_MEM_BARRIER reuse
   $a0 for the coordinate preload and force the signed timer reload into $v1.
   Widened mode + ASM_SCHED_BARRIER preserve the branch nop; zero-arg DCEC and
   the post-merge pinned page reproduce the tail ABI and late $v0 coloring. */
