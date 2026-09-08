#include "common.h"


extern void func_80025370() __attribute__((noreturn));
extern s32 func_8003DB94();
extern void *func_8003FC64();
extern void func_8004491C();
extern s32 func_80069EF8();

extern u8 D_80025098[9];
extern u8 D_80025AF0[9];
extern u8 D_80045C34[9];


typedef struct S_818C3A3C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818C3A3C_0;   /* temp_v0 in func_818C3A3C */

typedef struct S_818C3A3C_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
} S_818C3A3C_1;   /* temp_s2 in func_818C3A3C */

typedef struct S_818C3A3C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818C3A3C_2;   /* arg0 in func_818C3A3C */

typedef struct S_818C3A3C_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818C3A3C_3;   /* temp_s0 in func_818C3A3C */

typedef struct S_818C3A3C_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C3A3C_4;   /* arg1 in func_818C3A3C */

typedef struct S_818C3A3C_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C3A3C_5;   /* temp_v1_ptr in func_818C3A3C */

s32 func_818C3A3C(S_818C3A3C_2 *arg0, S_818C3A3C_4 *arg1) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 color;
    s32 call_zero;
    s32 alpha;
    void *handler;
    s32 temp_lo;
    s32 temp_v1;
    s32 var_v0;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    S_818C3A3C_3 *temp_s0;
    void *temp_s2;
    void *temp_v0;
    S_818C3A3C_5 *temp_v1_ptr;
    void *effect_name;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_s2 = (u8 *)temp_v0 + 0x20;
        effect_name = D_80025AF0;
        handler = D_80025098;
        ASM_KEEP_NV(handler);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_CLOBBER("$3");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        color = 0x7DCF;
        ((S_818C3A3C_0 *)temp_v0)->unk_10 = handler;
        ((S_818C3A3C_0 *)temp_v0)->unk_20 = arg0;
        ((S_818C3A3C_1 *)temp_s2)->unk_10 = 0;
        alpha = arg0->unk_14;
        call_zero = 0;
        *(volatile u16 *)((u8 *)temp_s2 + 0x14) = alpha;

        temp_s0 = ((S_818C3A3C_0 *)temp_v0)->unk_0C;
        alpha = 0x80;
        temp_s0->unk_0E = alpha;
        temp_s0->unk_0D = alpha;
        temp_s0->unk_0C = alpha;
        alpha = temp_s0->unk_14;
        temp_s0->unk_12 = color;
        alpha |= 0xC;
        temp_s0->unk_14 = alpha;
        alpha = temp_s0->unk_10;
        color = temp_s0->unk_14;
        alpha |= 0x20;
        color |= 0x100;
        temp_s0->unk_10 = alpha;
        temp_s0->unk_14 = color;
        func_8003DB94(temp_s0, effect_name, call_zero);

        var_v0 = func_80069EF8();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        temp_s0->unk_1A = temp_v1 - ((var_v0 >> 12) << 12);

        temp_lo = 0x1400 / ((S_818C3A3C_1 *)temp_s2)->unk_14;
        temp_s0->unk_1E = temp_lo;
        temp_s0->unk_1C = temp_lo;
        func_8004491C(temp_v0, D_80045C34);

        temp_v1_ptr = ((S_818C3A3C_0 *)temp_v0)->unk_08;
        ASM_KEEP(temp_v1_ptr);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        result = (u32)temp_v0;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        temp_a0 = arg1->unk_00;
        temp_a1 = arg1->unk_04;
        temp_a2 = arg1->unk_08;
        temp_a3 = arg1->unk_0C;
        temp_v1_ptr->unk_00 = temp_a0;
        temp_v1_ptr->unk_04 = temp_a1;
        temp_v1_ptr->unk_08 = temp_a2;
        temp_v1_ptr->unk_0C = temp_a3;
        temp_a0 = arg1->unk_10;
        temp_a1 = arg1->unk_14;
        temp_v1_ptr->unk_10 = temp_a0;
        temp_v1_ptr->unk_14 = temp_a1;
        func_80025370(temp_a0, temp_a1, temp_a2, temp_a3);
    }
    return 0;
}
