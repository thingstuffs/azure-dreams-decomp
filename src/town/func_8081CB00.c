#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026B00_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80026B00_0;   /* arg1 in func_80026B00 */

typedef struct S_80026B00_1 {
    u16 unk_00;
    u8 pad_02[0xE];
    u16 unk_10;
} S_80026B00_1;   /* arg0 in func_80026B00; pointer addresses record offset 0x2 */


extern s32 D_800814A0[3];

void func_80026B00(void *arg0, S_80026B00_0 *arg1) {
    u16 temp_v0;

    arg1->unk_00 = (s32) (arg1->unk_00 + arg1->unk_0C);
    arg1->unk_04 = (s32) (arg1->unk_04 + arg1->unk_10);
    arg1->unk_08 = (s32) (arg1->unk_08 + arg1->unk_14);
    temp_v0 = ((S_80026B00_1 *)((u8 *)arg0 - 0x2))->unk_10 - 1;
    ((S_80026B00_1 *)((u8 *)arg0 - 0x2))->unk_10 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_80026B00_1 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_80026B00_1 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
