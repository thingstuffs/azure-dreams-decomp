#include "common.h"
#include "m2c_compat.h"

typedef struct S_80166204_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80166204_3;   /* temp_v0 in func_80166204 */

typedef struct S_80166204_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80166204_4;   /* arg0 in func_80166204 */

typedef struct S_80166204_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80166204_5;   /* ((S_80166204_3 *)temp_v0)->unk_08 in func_80166204 */

typedef struct S_80166204_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80166204_6;   /* ((S_80166204_4 *)arg0)->unk_08 in func_80166204 */


typedef struct S_80166204_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80166204_0;   /* temp_v0 in func_80166204 */

typedef struct S_80166204_1 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0xC];
    u16 unk_42;
    u16 unk_44;
    u16 unk_46;
} S_80166204_1;   /* temp_s0 in func_80166204 */

typedef struct S_80166204_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    union { u16 s; volatile u16 u; } unk_14;   /* accessed as both */
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80166204_2;   /* temp_a0 in func_80166204 */


M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_80165A0C;

void func_80166204(S_80166204_4 *arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    register s32 held_arg4 ASM_REG("$19") = arg4;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 held_arg5 = arg5;
    register s32 byte_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u16 temp_v0_2;
    S_80166204_2 *temp_a0;
    S_80166204_1 *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        ((S_80166204_0 *)temp_v0)->unk_10 = &D_80165A0C;
        ((S_80166204_5 *)(((S_80166204_3 *)temp_v0)->unk_08))->unk_02 = (s16) (((S_80166204_6 *)(arg0->unk_08))->unk_02 + arg3);
        ((S_80166204_5 *)(((S_80166204_3 *)temp_v0)->unk_08))->unk_06 = (s16) (((S_80166204_6 *)(arg0->unk_08))->unk_06 + held_arg4);
        ASM_KEEP(held_arg4);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_80166204_5 *)(((S_80166204_3 *)temp_v0)->unk_08))->unk_0A = (s16) (((S_80166204_6 *)(arg0->unk_08))->unk_0A + held_arg5);
        ASM_KEEP(held_arg5);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        temp_s0 = temp_v0 + 0x20;
        temp_s0->unk_42 = (u16) ((S_80166204_6 *)(arg0->unk_08))->unk_02;
        temp_s0->unk_44 = (u16) ((S_80166204_6 *)(arg0->unk_08))->unk_06;
        temp_s0->unk_46 = (u16) ((S_80166204_6 *)(arg0->unk_08))->unk_0A;
        ((S_80166204_5 *)(((S_80166204_3 *)temp_v0)->unk_08))->unk_0C = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((S_80166204_5 *)(((S_80166204_3 *)temp_v0)->unk_08))->unk_10 = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((S_80166204_5 *)(((S_80166204_3 *)temp_v0)->unk_08))->unk_14 = arg6;
        temp_s0->unk_14 = arg1;
        temp_s0->unk_32 = 8;
        temp_s0->unk_34 = 8;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = ((S_80166204_0 *)temp_v0)->unk_0C;
        temp_a0->unk_1E = 0x2AA;
        temp_a0->unk_1C = 0x2AA;
        temp_a0->unk_0C = 0xFF;
        byte_value = 0x20;
        temp_a0->unk_0E = byte_value;
        temp_a0->unk_0D = byte_value;
        temp_a0->unk_12 = 0x7DCF;
        temp_v0_2 = temp_a0->unk_14.s & 0xFFF3;
        temp_v0_2 |= 2;
        ASM_KEEP_NV(temp_v0_2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp_a0->unk_14.u = temp_v0_2;
        temp_v0_2 |= 0x100;
        temp_a0->unk_14.s = temp_v0_2;
        func_8003DB94(temp_a0, &D_800DE870, 0);
    }
}

/* MECHANISM: Seven ABI arguments preserve the unused a2 slot; guarded s3/s4
   locals hold stack inputs arg4/arg5 across the allocator-crossing first call.
   A v1 byte-value pin plus volatile midpoint and tied keep preserve the v0 RMW chain. */
