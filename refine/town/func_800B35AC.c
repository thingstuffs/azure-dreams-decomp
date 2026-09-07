#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B0D0C_0 {
    u8 pad_00[0xCC];
    void * unk_CC;
} S_800B0D0C_0;   /* arg0 in func_800B0D0C */

typedef struct S_800B0D0C_1 {
    u8 pad_00[0x74];
    void * unk_74;
    void * unk_78;
} S_800B0D0C_1;   /* ((S_800B0D0C_0 *)arg0)->unk_CC in func_800B0D0C */

typedef struct S_800B0D0C_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B0D0C_2;   /* ((S_800B0D0C_1 *)(((S_800B0D0C_0 *)arg0)->unk_CC))->unk_74 in func_800B0D0C */

typedef struct S_800B0D0C_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B0D0C_3;   /* ((S_800B0D0C_1 *)(((S_800B0D0C_0 *)arg0)->unk_CC))->unk_78 in func_800B0D0C */

typedef struct S_800B0D0C_4 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B0D0C_4;   /* ((S_800B0D0C_2 *)(((S_800B0D0C_1 *)(((S_800B0D0C_0 *)arg0)->unk_CC))->unk_74))->unk_04 in func_800B0D0C */

typedef struct S_800B0D0C_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B0D0C_5;   /* ((S_800B0D0C_3 *)(((S_800B0D0C_1 *)(((S_800B0D0C_0 *)arg0)->unk_CC))->unk_78))->unk_04 in func_800B0D0C */

/* Positions the two child elements at (-95, 48) and (97, 48). */
void func_800B0D0C(S_800B0D0C_0 *parentObject) {
    ((S_800B0D0C_4 *)(((S_800B0D0C_2 *)(((S_800B0D0C_1 *)(parentObject->unk_CC))->unk_74))->unk_04))->unk_08 = -0x5F;
    ((S_800B0D0C_4 *)(((S_800B0D0C_2 *)(((S_800B0D0C_1 *)(parentObject->unk_CC))->unk_74))->unk_04))->unk_0A = 0x30;
    ((S_800B0D0C_5 *)(((S_800B0D0C_3 *)(((S_800B0D0C_1 *)(parentObject->unk_CC))->unk_78))->unk_04))->unk_08 = 0x61;
    ((S_800B0D0C_5 *)(((S_800B0D0C_3 *)(((S_800B0D0C_1 *)(parentObject->unk_CC))->unk_78))->unk_04))->unk_0A = 0x30;
}
