#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_818D4B94_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_818D4B94_2;   /* temp_v0 in func_818D4B94 */


typedef struct S_818D4B94_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_818D4B94_4;   /* ((S_818D4B94_2 *)temp_v0)->unk_08 in func_818D4B94 */

typedef struct S_818D4B94_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818D4B94_5;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_818D4B94 */




void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();      /* extern */
extern M2C_UNK D_80024044;
extern M2C_UNK D_80024294;

typedef struct S_818D4B94_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_818D4B94_0;   /* temp_v0 in func_818D4B94 */

typedef struct S_818D4B94_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u16 unk_34;
    u16 unk_36;
    u16 unk_38;
    u8 pad_3A[0xE];
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
} S_818D4B94_1;   /* temp_s0 in func_818D4B94 */

void func_818D4B94(Rec_D_800E3D7C *arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s16 held_arg1 = arg1;
    s32 held_arg2 = arg2;
    s32 held_arg3 = arg3;
    register s32 held_arg4 ASM_REG("$18") = arg4;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 held_arg5 ASM_REG("$19") = arg5;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 held_arg6 ASM_REG("$20") = arg6;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 signed_arg3;
    s32 var_v1;
    s32 temp_a1;
    s32 numerator;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 var_v1_2;
    S_818D4B94_1 *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x211, arg0);
    if (temp_v0 != NULL) {
        ((S_818D4B94_0 *)temp_v0)->unk_10 = &D_80024294;
        ((S_818D4B94_4 *)(((S_818D4B94_2 *)temp_v0)->unk_08))->unk_02 = (s16) (((S_818D4B94_5 *)(arg0->unk_08.at00_pv.v))->unk_02 + held_arg4);
        ((S_818D4B94_4 *)(((S_818D4B94_2 *)temp_v0)->unk_08))->unk_06 = (s16) (((S_818D4B94_5 *)(arg0->unk_08.at00_pv.v))->unk_06 + held_arg5);
        ((S_818D4B94_4 *)(((S_818D4B94_2 *)temp_v0)->unk_08))->unk_0A = (s16) (((S_818D4B94_5 *)(arg0->unk_08.at00_pv.v))->unk_0A + held_arg6);
        temp_s0 = temp_v0 + 0x20;
        temp_s0->unk_34 = (u16) ((S_818D4B94_5 *)(arg0->unk_08.at00_pv.v))->unk_02;
        temp_s0->unk_36 = (u16) ((S_818D4B94_5 *)(arg0->unk_08.at00_pv.v))->unk_06;
        temp_s0->unk_38 = (u16) ((S_818D4B94_5 *)(arg0->unk_08.at00_pv.v))->unk_0A;
        signed_arg3 = (s16) held_arg3;
        var_v1 = signed_arg3;
        numerator = 0 - (held_arg4 << 0x10);
        if (signed_arg3 < 0) {
            var_v1 = signed_arg3 + 7;
        }
        temp_a1 = var_v1 >> 3;
        temp_lo = numerator / temp_a1;
        if (temp_lo < 0) {
            temp_lo += 0xF;
        }
        temp_s0->unk_48 = temp_lo >> 4;
        ASM_KEEP(held_arg4);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        temp_lo_2 = (s32) (0 - (held_arg5 << 0x10)) / temp_a1;
        if (temp_lo_2 < 0) {
            temp_lo_2 += 0xF;
        }
        temp_s0->unk_4C = temp_lo_2 >> 4;
        ASM_KEEP(held_arg5);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_arg3);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        var_v1_2 = (s32) (0 - (held_arg6 << 0x10)) / temp_a1;
        if (var_v1_2 < 0) {
            var_v1_2 += 0xF;
        }
        temp_s0->unk_50 = (s32) (var_v1_2 >> 4);
        temp_s0->unk_14 = held_arg1;
        temp_s0->unk_32 = held_arg3;
        func_8004491C(temp_v0, &D_80024044, signed_arg3);
        ASM_KEEP(held_arg6);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp_s0->unk_08 = held_arg2;
    }
}

/* MECHANISM: Exact 0x38 frame with raw arguments pinned to retail's s1-s7 roles.
   A raw s32 arg3 plus signed s16 local, mutable quotient locals, and pre-branch numerator reproduce the CFG.
   Keep seams before division and after the call preserve s4 while allowing the global address delay-slot hoist. */
