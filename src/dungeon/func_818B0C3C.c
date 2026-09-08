#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002443C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8002443C_0;   /* work_s3 in func_8002443C */

typedef struct S_8002443C_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
} S_8002443C_1;   /* work_s1 in func_8002443C */

typedef struct S_8002443C_2 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_8002443C_2;   /* work_s2 in func_8002443C */

typedef struct S_8002443C_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8002443C_3;   /* temp_s0 in func_8002443C */


M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_800644B8();
s32 func_80064584();
s32 func_80069EF8();
extern M2C_UNK D_800242E0;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEC70;

s32 func_8002443C(s32 arg0, void *arg1, s16 arg2, s32 arg3) {
    u16 copy_value;
    u16 final_value;
    s32 var_s0;
    M2C_UNK *node_type;
    S_8002443C_3 *temp_s0;
    register s32 return_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    u8 *work_s1 = (u8 *)arg0;
    u8 *work_s2 = (u8 *)arg1;
    register s16 work_s0 ASM_REG("$16") = arg2;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 *work_s3;
    s32 work_s4 = arg3;
    s32 init_value;

    work_s3 = func_8003FC64(0x212);
    ASM_KEEP(work_s1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(work_s0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(work_s4);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (work_s3 != NULL) {
        node_type = &D_800242E0;
        ASM_USE(node_type);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_8002443C_0 *)work_s3)->unk_20 = (s32)work_s1;
        work_s1 = work_s3 + 0x20;
        ((S_8002443C_0 *)work_s3)->unk_10 = node_type;
        ((S_8002443C_1 *)work_s1)->unk_04 = work_s0;
        ((S_8002443C_1 *)work_s1)->unk_06 = (s16) (-6 - (func_80069EF8() % 5));
        ((S_8002443C_1 *)work_s1)->unk_08 = (u16) ((S_8002443C_2 *)work_s2)->unk_02.s;
        ((S_8002443C_1 *)work_s1)->unk_0A = (u16) ((S_8002443C_2 *)work_s2)->unk_06.s;
        copy_value = ((S_8002443C_2 *)work_s2)->unk_0A.s;
        ASM_KEEP(copy_value);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        init_value = 0x7E09;
        ASM_USE(init_value);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ((S_8002443C_1 *)work_s1)->unk_0C = copy_value;
        temp_s0 = ((S_8002443C_0 *)work_s3)->unk_0C;
        temp_s0->unk_0E = 0;
        temp_s0->unk_0D = 0;
        temp_s0->unk_0C = 0;
        temp_s0->unk_12 = (s16)init_value;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
        temp_s0->unk_10 = (u16) (temp_s0->unk_10 | 0x20);
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x100);
        func_8003DB94(temp_s0, &D_800DEC70, (s16)work_s4 % 16, (s16)work_s4);
        ASM_USE(work_s4);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        func_8004491C(work_s3, &D_80045340);
        work_s2 = ((S_8002443C_0 *)work_s3)->unk_08;
        var_s0 = func_80069EF8() % 0x1000;
        ((S_8002443C_2 *)work_s2)->unk_02.u = (s16) (((S_8002443C_1 *)work_s1)->unk_08 + ((s32) (func_800644B8(var_s0) * 2) >> 8));
        ((S_8002443C_2 *)work_s2)->unk_06.u = (s16) (((S_8002443C_1 *)work_s1)->unk_0A + ((s32) (func_80064584(var_s0) * 2) >> 8));
        final_value = ((S_8002443C_1 *)work_s1)->unk_0C;
        ASM_USE(final_value);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        return_v0 = (s32)work_s3;
        ASM_KEEP(return_v0);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        ((S_8002443C_2 *)work_s2)->unk_0A.u = (s16)final_value;
        return;
    }
    return_v0 = 0;
       /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    return return_v0;
}
