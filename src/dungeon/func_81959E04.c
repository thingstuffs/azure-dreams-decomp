#include "common.h"
#include "m2c_compat.h"

void func_800256B8(void) __attribute__((noreturn)); /* extern */
void func_800256F0(void) __attribute__((noreturn)); /* extern */
void *func_8003FC64(s32);                         /* extern */
void func_8004491C(void *, void *);                /* extern */
s32 func_800644B8(s32);                           /* extern */
s32 func_80064584(s32);                           /* extern */
extern M2C_UNK D_80025528;
extern u8 D_800C95C0[12];

typedef struct S_81959E04_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_81959E04_0;   /* temp_v0 in func_81959E04 */

typedef struct S_81959E04_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_81959E04_1;   /* temp_s1 in func_81959E04 */

typedef struct S_81959E04_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x28];
    s16 unk_30;
} S_81959E04_2;   /* temp_v1 in func_81959E04 */

void *func_81959E04(s16 arg0, s16 arg1, s16 arg2) {
    s32 var_s0;
    register S_81959E04_1 *temp_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *temp_v0;
    s32 var_s3;
    s32 var_s4;
    register s32 var_s5 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 var_s6 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 var_s7 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s16 var_fp;
    register S_81959E04_2 *temp_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *call_arg1;

    var_s6 = arg0;
    var_s7 = arg1;
    var_fp = arg2;
    var_s3 = 0;
    ASM_KEEP_NV(var_s3);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    var_s5 = -0x800;
    var_s4 = 0x20;
    var_s0 = var_s3;
loop_1:
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        register void *call_arg0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register void *field_ptr ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        call_arg1 = D_800C95C0;
#else
        call_arg1 = (void *)0x800D0000;
        ASM_KEEP_NV(call_arg1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#endif
        call_arg0 = temp_v0;
        field_ptr = &D_80025528;
#ifndef NON_MATCHING
        call_arg1 = (u8 *)call_arg1 - 0x6A40;
#endif
        ((S_81959E04_0 *)temp_v0)->unk_10 = field_ptr;
        func_8004491C(call_arg0, call_arg1);
        temp_s1 = ((S_81959E04_0 *)temp_v0)->unk_08;
        temp_s1->unk_02 = var_s6;
        temp_s1->unk_06 = var_s7;
        temp_s1->unk_0A = var_fp;
        if (func_80064584(var_s0) & 0x800) {
            s32 tail_value;
            tail_value = func_80064584(var_s0) | var_s5;
            ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800256B8();
        }
        temp_s1->unk_0C = (s32) ((func_80064584(var_s0) & 0x7FF) << 0xB);
        if (func_800644B8(var_s0) & 0x800) {
            s32 tail_value;
            tail_value = func_800644B8(var_s0) | var_s5;
            ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800256F0();
        }
        temp_s1->unk_10 = (s32) ((func_800644B8(var_s0) & 0x7FF) << 0xB);
        temp_s1->unk_14 = 0xFFFE0000;
        temp_v1 = temp_v0 + 0x20;
        ASM_KEEP_NV(temp_v1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ((S_81959E04_0 *)temp_v0)->unk_20 = var_s4;
        temp_v1->unk_02 = var_s4;
        temp_v1->unk_04 = 1;
        temp_v1->unk_06 = 0;
        temp_v1->unk_30 = var_s4;
        goto block_9;
    }
block_9:
    var_s3 += 1;
    var_s0 += 0x80;
    if (var_s3 >= 0x20) {
        return temp_v0;
    }
    goto loop_1;
}
/* MECHANISM: The 0x38 frame comes from ten held roles: s6/s7/fp args, s3/s0 loop state,
   s5/s4 constants, and s2/s1 object bases; a kept s3 preserves move s0,s3.
   Tied tail-slot pins sink both dead v0|s5 values into noreturn j delays.
   A kept a1 page/low split plus fixed a0/a3 emits the call setup in retail order. */
