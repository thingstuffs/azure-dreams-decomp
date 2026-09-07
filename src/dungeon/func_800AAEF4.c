#include "common.h"
#include "m2c_compat.h"

s32 func_80065420();        /* extern */

typedef struct S_800B0654_0 {
    u8 pad_00[0x28];
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u8 pad_2E[0x92];
    s32 unk_C0;
} S_800B0654_0;   /* arg2 in func_800B0654 */

typedef struct S_800B0654_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B0654_1;   /* arg0 in func_800B0654 */

typedef struct S_800B0654_2 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_800B0654_2;   /* arg1 in func_800B0654 */

void func_800B0654(S_800B0654_1 *arg0, S_800B0654_2 *arg1, void *arg2) {
    ((S_800B0654_0 *)arg2)->unk_28 = (u16) arg0->unk_02;
    ((S_800B0654_0 *)arg2)->unk_2A = (u16) arg0->unk_06;
    ((S_800B0654_0 *)arg2)->unk_2C = (u16) arg0->unk_0A;
    ((S_800B0654_0 *)arg2)->unk_C0 = (s32) (func_80065420(arg2 + 0x28, arg2 + 0xB8, arg2 + 0x90, arg2 + 0x94) + arg1->unk_04);
}
