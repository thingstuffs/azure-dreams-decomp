#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801735B8_0 {
    u8 pad_00[0x96];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801735B8_0;   /* arg0 in func_801735B8 */

typedef struct S_801735B8_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_801735B8_1;   /* &D_80083460 in func_801735B8 */


typedef struct S_801735B8_3 {
    u8 pad_00[0xC];
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801735B8_3;   /* held_arg2 in func_801735B8 */

typedef struct S_801735B8_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_801735B8_4;   /* global_ptr in func_801735B8 */


void func_8009A028(void *);
void func_8009A3D0(s32, s32, s32);
void func_800A2FE0(void *);
void func_800A32A4(void *);
void func_800A56E0(s32);
void func_800ACF88(void *);
extern s32 D_800814A0;
extern s32 D_80083460;

void func_801735B8(void *arg0, void *arg1, void *arg2, void *arg3) {
    register void *held_arg2 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    M2C_UNK *global_ptr;
    s32 state;
    s32 flags;
    s32 global_value;
    s32 call_arg0;
    s32 call_arg1;
    s32 call_arg2;
    u16 countdown;

    held_arg2 = arg2;
    state = ((S_801735B8_0 *)arg0)->unk_9B;
    switch (state) {
    case 0:
        if (((S_801735B8_1 *)(&D_80083460))->unk_0A != 0) {
            return;
        }
        ((S_801735B8_0 *)arg0)->unk_9B = 1;
        /* fallthrough */
    case 1:
        flags = ((Rec_D_80082E80 *)arg3)->unk_14.at00_s32.v;
        if (flags & 0x4000) {
            if (!(flags & 0x20000000)) {
                func_800ACF88(arg3);
            }
        }
        ((S_801735B8_0 *)arg0)->unk_96.u = 6;
        ((S_801735B8_0 *)arg0)->unk_9B =
            (u8)(((S_801735B8_0 *)arg0)->unk_9B + 1);
        ((S_801735B8_3 *)held_arg2)->unk_12 = 0xFF80;
        /* fallthrough */
    case 2:
        ((Rec_D_80082E80 *)arg3)->unk_1C.at00_s32.v |= 0x10000000;
        countdown = ((S_801735B8_0 *)arg0)->unk_96.u - 1;
        ((S_801735B8_0 *)arg0)->unk_96.u = countdown;
        if ((countdown << 16) <= 0) {
            if (((S_801735B8_3 *)held_arg2)->unk_0C.u8 >= 0x10U) {
                ((S_801735B8_3 *)held_arg2)->unk_0C.s32 += (s32)0xFFEFEFF0;
            }
            ((S_801735B8_3 *)held_arg2)->unk_10 = 0x20;
            ((S_801735B8_3 *)held_arg2)->unk_14 |= 0xC;
        } else {
            ((S_801735B8_3 *)held_arg2)->unk_0C.s32 = 0x00808080;
        }

        if (((S_801735B8_0 *)arg0)->unk_96.s == 0) {
            func_800A56E0(0x805);
        }
        if (!(((S_801735B8_3 *)held_arg2)->unk_14 & 0x8000)) {
            if (((S_801735B8_3 *)held_arg2)->unk_0C.u8 >= 0x10U) {
                return;
            }
        }

        global_ptr = &D_80083460;
        global_value = ((S_801735B8_4 *)global_ptr)->unk_10;
        if (global_value == (s32)((u8 *)arg3 - 0x20)) {
            ((S_801735B8_4 *)global_ptr)->unk_10 =
                global_value & 0x7FFFFFFF;
        }
        func_800A2FE0(arg3);
        func_800A32A4(arg3);

        call_arg0 = ((S_801735B8_3 *)held_arg2)->unk_24;
        call_arg1 = ((S_801735B8_3 *)held_arg2)->unk_25;
        call_arg2 = 0x3000;
        if (((Rec_D_80082E80 *)arg3)->unk_1C.at00_s32.v & 0x2000) {
            call_arg2 = 0x300;
        }
        func_8009A3D0(call_arg0, call_arg1, call_arg2);
        func_8009A028(arg3);
        (*(u16 *)((u8 *)arg3 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    default:
        return;
    }
    ASM_KEEP(held_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}

/* MECHANISM: A natural three-case switch preserves the retail dispatch and fallthrough block order.
   A guarded s1 arg2 hold fixes the s0/s1/s2 frame roles; true-space targets remain local joins.
   Direct D_80083460+0xA access schedules the page base, and u16 0xFF80 selects the ori encoding. */
