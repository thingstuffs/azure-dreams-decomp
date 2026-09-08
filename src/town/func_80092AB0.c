#include "common.h"
#include "m2c_compat.h"

typedef struct S_80090210_0 {
    s32 unk_00;
    u8 pad_04[0x10];
    M2C_UNK * unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
    u8 pad_1C[0xA];
    s16 unk_26;
} S_80090210_0;   /* base_834B8 in func_80090210; pointer addresses record offset 0x10 */

typedef struct S_80090210_1 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_80090210_1;   /* base_82E80 in func_80090210 */

typedef struct S_80090210_2 {
    u8 pad_00[0x438];
    union { M2C_UNK (*s)(); s32 u; } unk_438;   /* accessed as both */
} S_80090210_2;   /* callback_page in func_80090210 */


M2C_UNK func_80033AA8();                     /* extern */
M2C_UNK func_80033AE8();                     /* extern */
s32 func_80033B2C();                         /* extern */
M2C_UNK func_80048D20();                            /* extern */
s32 func_80048D40();                                /* extern */
M2C_UNK func_800902C0();                            /* extern */
M2C_UNK func_800902F4();                            /* extern */
M2C_UNK func_80094984(); /* extern */
M2C_UNK func_80098868(); /* extern */
M2C_UNK func_80098928(); /* extern */
M2C_UNK func_80099764();                   /* extern */
extern s32 D_80080A80;
extern u8 D_80082E80[];
extern s32 D_800834B8;
extern s32 D_80083780;
extern u8 D_8008FFC0[];
extern M2C_UNK D_80097D54;
extern u8 D_800D0078[];
extern s32 D_800D0438;

void func_80090210(void) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0;
    u8 *base_83780 = (u8 *)&D_80083780;
    u8 *base_82E80 = D_80082E80;
    u8 *base_834B8 = (u8 *)&D_800834B8;
    u8 *callback_page;
    M2C_UNK (*callback)();

    if (((S_80090210_0 *)((u8 *)base_834B8 - 0x10))->unk_00 != D_8008FFC0) {
        if (func_80033B2C(0x1202) == 0) {
            ((S_80090210_0 *)((u8 *)base_834B8 - 0x10))->unk_26 = 0;
            temp_s0 = func_80033B2C(0x1202);
            if (temp_s0 != func_80033B2C(0x9D)) {
                register u32 dead_result_page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                func_80048D20();
                dead_result_page = 0x80080000;
                ASM_PAGEBASE_PIN(dead_result_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                func_800902C0();
                return;
            }
            goto block_7;
        }
        ((S_80090210_0 *)((u8 *)base_834B8 - 0x10))->unk_26 = 1;
        temp_s0_2 = func_80033B2C(0x1202);
        if (temp_s0_2 != func_80033B2C(0x9D)) {
            temp_v0 = func_80048D40();
            D_80080A80 = temp_v0;
            ((S_80090210_1 *)base_82E80)->unk_28 = temp_v0;
        }
block_7:
        if (func_80033B2C(0x1202) != 0) {
            register u32 dead_arg_page ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            func_80033AA8(0x9D);
            dead_arg_page = 0x800D0000;
            ASM_PAGEBASE_PIN(dead_arg_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800902F4();
            return;
        }
        func_80033AE8(0x9D);
        func_80094984(D_800D0078, base_834B8, base_82E80);
        func_80099764(base_834B8);
        func_80098868(base_834B8, base_83780, base_82E80);
        func_80098928(base_834B8, base_83780, base_82E80);
        {
            u8 *handler_page;

            handler_page = (u8 *)0x80090000;
            ASM_KEEP(handler_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            callback_page = (u8 *)0x800D0000;
            callback = ((S_80090210_2 *)callback_page)->unk_438.s;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ((S_80090210_0 *)((u8 *)base_834B8 - 0x10))->unk_14 =
                (M2C_UNK *)(handler_page + 0x7D54);
            ((S_80090210_0 *)((u8 *)base_834B8 - 0x10))->unk_1A = 0x10;
            if (callback != NULL) {
                callback();
                ((S_80090210_2 *)callback_page)->unk_438.u = 0;
            }
        }
    }
}

/* MECHANISM: Early pointer locals force the 0x28 frame and s3/s2/s1 held bases; s0 is reused for the callback page.
   LEAD-27 page pins supply the two dead lui fillers consumed by the LEAD-22 sibling-call jumps.
   A guarded v0 0x80090000 page plus a scheduling seam orders the callback load before the handler low-half/store. */
