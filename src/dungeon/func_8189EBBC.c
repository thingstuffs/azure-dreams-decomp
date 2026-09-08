#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800244D4() __attribute__((noreturn));
s32 func_8003DB94();
void *func_8003FC64();
s32 func_8004491C();
s32 rand();
extern s32 D_80024264;
extern s32 D_800D36D0;
extern s32 D_800DEF08;

typedef struct S_800243BC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_800243BC_0;   /* temp_v0 in func_800243BC */

typedef struct S_800243BC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    s32 unk_08;
} S_800243BC_1;   /* temp_v1 in func_800243BC */

typedef struct S_800243BC_2 {
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
} S_800243BC_2;   /* temp_s0 in func_800243BC */

typedef struct S_800243BC_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800243BC_3;   /* arg1 in func_800243BC */

typedef struct S_800243BC_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800243BC_4;   /* temp_v1_3 in func_800243BC */

s32 func_800243BC(s32 arg0, S_800243BC_3 *arg1)
{
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v0_2;
    s32 var_a2;
    register s32 return_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    S_800243BC_2 *temp_s0;
    void *temp_v0;
    S_800243BC_1 *temp_v1;
    S_800243BC_4 *temp_v1_3;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_v1 = temp_v0 + 0x20;
        ((S_800243BC_0 *)temp_v0)->unk_10 = &D_80024264;
        temp_v1->unk_08 = arg0;
        ((S_800243BC_0 *)temp_v0)->unk_20 = 0;
        temp_v1->unk_02 = 0;
        temp_v1->unk_04 = 0x10;
        temp_s0 = ((S_800243BC_0 *)temp_v0)->unk_0C;
        temp_s0->unk_12 = 0x7E02;
        temp_s0->unk_0E = 0;
        temp_s0->unk_0D = 0;
        temp_s0->unk_0C = 0;
        temp_s0->unk_1E = 0;
        temp_s0->unk_1C = 0;
        temp_s0->unk_14 =
            (s16)(temp_s0->unk_14 | 0xC);
        temp_s0->unk_10 =
            (u16)(temp_s0->unk_10 | 0x20);
        temp_s0->unk_14 =
            (u16)(temp_s0->unk_14 | 0x100);
        temp_v0_2 = rand();
        var_a2 = temp_v0_2;
        if (temp_v0_2 < 0) {
            var_a2 = temp_v0_2 + 0xF;
        }
        func_8003DB94(temp_s0, &D_800DEF08,
                      (s16)(temp_v0_2 - ((var_a2 >> 4) * 0x10)));
        func_8004491C(temp_v0, &D_800D36D0);
        temp_v1_3 = ((S_800243BC_0 *)temp_v0)->unk_08;
        ASM_KEEP(temp_v1_3);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        return_value = (s32)temp_v0;
        ASM_KEEP(return_value);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        temp_a0 = arg1->unk_00;
        temp_a1 = arg1->unk_04;
        temp_a2 = arg1->unk_08;
        temp_a3 = arg1->unk_0C;
        temp_v1_3->unk_00 = temp_a0;
        temp_v1_3->unk_04 = temp_a1;
        temp_v1_3->unk_08 = temp_a2;
        temp_v1_3->unk_0C = temp_a3;
        temp_a0 = arg1->unk_10;
        temp_a1 = arg1->unk_14;
        temp_v1_3->unk_10 = temp_a0;
        temp_v1_3->unk_14 = temp_a1;
        return func_800244D4(temp_a0, temp_a1, temp_a2, temp_a3);
    }
    return 0;
}
