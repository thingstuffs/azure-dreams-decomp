#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();
M2C_UNK func_8004491C();
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BBBE0;
extern M2C_UNK D_800BC054;

typedef struct S_800BC0A8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800BC0A8_0;   /* temp_v0 in func_800BC0A8 */

typedef struct S_800BC0A8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BC0A8_1;   /* temp_v0_2 in func_800BC0A8 */

typedef struct S_800BC0A8_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    u8 pad_0A[0x3E];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    u8 pad_52[0x6];
    s16 unk_58;
} S_800BC0A8_2;   /* temp_a1 in func_800BC0A8 */

typedef struct S_800BC0A8_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
} S_800BC0A8_3;   /* temp_a0 in func_800BC0A8 */

void *func_800BC0A8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    register s32 hold4 ASM_REG("$21") = arg4;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 hold5 ASM_REG("$23") = arg5;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 hold7 ASM_REG("$22") = arg7;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    S_800BC0A8_3 *temp_a0;
    S_800BC0A8_2 *temp_a1;
    void *temp_v0;
    S_800BC0A8_1 *temp_v0_2;

    temp_v0 = func_8003FD64(0x202, &D_80083498);
    if (temp_v0 != NULL) {
        ((S_800BC0A8_0 *)temp_v0)->unk_10 = &D_800BBBE0;
        func_8004491C(temp_v0, &D_800BC054);
        temp_v0_2 = ((S_800BC0A8_0 *)temp_v0)->unk_08;
        temp_a1 = temp_v0 + 0x20;
        temp_v0_2->unk_02 = arg0;
        temp_a1->unk_04 = arg0;
        temp_v0_2->unk_06 = arg1;
        temp_a1->unk_06 = arg1;
        temp_v0_2->unk_0A = arg2;
        temp_a1->unk_08 = arg2;
        temp_a0 = ((S_800BC0A8_0 *)temp_v0)->unk_0C;
        temp_a0->unk_1A = (s16) (arg3 + 0x400);
        temp_a0->unk_14 = (u16) (temp_a0->unk_14 | 0xC);
        temp_a1->unk_4E = arg3;
        temp_a1->unk_4C = 4;
        temp_a1->unk_50 = (s16) hold4;
        ((S_800BC0A8_0 *)temp_v0)->unk_20 = arg6;
        temp_a1->unk_58 = (s16) hold5;
        temp_a1->unk_48 = (s16) hold7;
    }
    return temp_v0;
}
