#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002626C_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8002626C_3;   /* temp_v0 in func_8002626C */

typedef struct S_8002626C_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8002626C_4;   /* ((S_8002626C_3 *)temp_v0)->unk_08 in func_8002626C */




s16 func_8002458C();                         /* extern */
M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_8002615C;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;

typedef struct S_8002626C_0 {
    u8 pad_00[0x28];
    s16 unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    u8 pad_32[0x56];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
} S_8002626C_0;   /* temp_s0 in func_8002626C */

typedef struct S_8002626C_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8002626C_1;   /* temp_v0 in func_8002626C */

typedef struct S_8002626C_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8002626C_2;   /* temp_s1 in func_8002626C */

void func_8002626C(
    s32 unused0, s32 unused1, s32 unused2, s32 unused3,
    s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s16 temp_v1;
    S_8002626C_0 *temp_s0;
    S_8002626C_2 *temp_s1;
    void *temp_v0;
    register s32 held_arg4 ASM_REG("$22") = arg4;   /* MATCH pin: load-bearing for the whole function shape */
    register s32 held_arg5 ASM_REG("$23") = arg5;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s0 = temp_v0 + 0x20;
        temp_s0->unk_28 = 0x14;
        ((S_8002626C_1 *)temp_v0)->unk_10 = &D_8002615C;
        func_8004491C(temp_v0, &D_80045340);
        temp_s1 = ((S_8002626C_1 *)temp_v0)->unk_0C;
        temp_s1->unk_10 = 0x40;
        temp_s1->unk_14 = (u16) (temp_s1->unk_14 | 0xC);
        ((S_8002626C_4 *)(((S_8002626C_3 *)temp_v0)->unk_08))->unk_02 =
            (s16) (s32) &((s8 *) arg7)[held_arg4];
        ((S_8002626C_4 *)(((S_8002626C_3 *)temp_v0)->unk_08))->unk_06 =
            (s16) (s32) &((s8 *) arg8)[held_arg5];
        ((S_8002626C_4 *)(((S_8002626C_3 *)temp_v0)->unk_08))->unk_0A = (s16) (arg9 + arg6);
        temp_s0->unk_88 = (s32) (0 - ((s32) (held_arg4 << 0x10) >> 7));
        temp_s0->unk_8C = (s32) (0 - ((s32) (held_arg5 << 0x10) >> 7));
        temp_s0->unk_2C = (s16) arg7;
        temp_s0->unk_2E = (s16) arg8;
        temp_s0->unk_30 = (s16) arg9;
        temp_s0->unk_90 = (s32) (0 - ((s32) (arg6 << 0x10) >> 7));
        temp_s1 = ((S_8002626C_1 *)temp_v0)->unk_0C;
        temp_s1->unk_1E = 0x3000;
        temp_s1->unk_1C = 0x3000;
        temp_v1 = func_8002458C(3);
        temp_s1->unk_0E = 0;
        temp_s1->unk_0D = 0;
        temp_s1->unk_0C = 0;
        if (temp_v1 == 0) {
            temp_s1->unk_0C = 0x10;
        }
        if (temp_v1 == 1) {
            temp_s1->unk_0D = 0x10;
        }
        if (temp_v1 == 2) {
            temp_s1->unk_0E = 0x10;
        }
        temp_s1->unk_12 = 0x7DCF;
        temp_s1->unk_14 = (u16) (temp_s1->unk_14 | 0x100);
        func_8003DB94(temp_s1, &D_800DE870, 0);
        ASM_KEEP(held_arg4);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        ASM_KEEP(held_arg5);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    }
}
/* MECHANISM: The ten-argument ABI and reused pointer local produce the retail
   0x38 frame, full hold set, and reload seam. Tail-kept s6/s7 pins preserve
   scheduling; byte-pointer BASE[index] sums select retail addu operand order. */
