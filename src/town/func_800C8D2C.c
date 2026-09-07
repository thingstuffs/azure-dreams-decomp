#include "common.h"

typedef s32 unk32;

typedef struct S_800C648C_0 {
    u8 pad_00[0x7C];
    s32 ** unk_7C;
    void ** unk_80;
} S_800C648C_0;   /* arg0 in func_800C648C */

typedef struct S_800C648C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C648C_1;   /* ((S_800C648C_0 *)arg0)->unk_80 in func_800C648C */



extern unk32 D_800D58B8;

s32 func_800C648C(S_800C648C_0 *arg0) {
    s32 value;

    value = *arg0->unk_7C;
    if ((value == (s32)&D_800D58B8) &&
        (((S_800C648C_1 *)(arg0->unk_80))->unk_04 == value)) {
        return 1;
    }
    return 0;
}
