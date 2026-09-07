#include "common.h"
#include "m2c_compat.h"

typedef struct S_80016E5C_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80016E5C_0;   /* D_80016000 in func_80016E5C */

typedef struct S_80016E5C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80016E5C_1;   /* temp_v1 in func_80016E5C */

typedef struct S_80016E5C_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80016E5C_2;   /* temp_v1_2 in func_80016E5C */


extern S_80016E5C_0 *D_80016000;

void func_80016E5C(void) {
    S_80016E5C_1 *temp_v1;
    S_80016E5C_2 *temp_v1_2;

    temp_v1 = D_80016000->unk_1C;
    temp_v1->unk_04 = (s32) ((temp_v1->unk_04 << 6) + 0x220);
    temp_v1_2 = D_80016000->unk_1C;
    temp_v1_2->unk_08 = (s32) ((temp_v1_2->unk_08 << 6) + 0x220);
}
