#include "common.h"
#include "m2c_compat.h"

typedef struct S_80090200_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80090200_0;   /* arg0 in func_80090200 */

typedef struct S_80090200_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_80090200_1;   /* arg3 in func_80090200 */


M2C_UNK func_80048A44(); /* extern */
M2C_UNK func_80094E34();                            /* extern */
extern s16 D_80083228;
extern u8 D_800DD0E8;

void func_80090200(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    ((S_80090200_0 *)arg0)->unk_9A = 0xD;
    ((S_80090200_0 *)arg0)->unk_9B = 0;
    ((S_80090200_0 *)arg0)->unk_8C = 0;
    ((S_80090200_0 *)arg0)->unk_96 = 0;
    func_80094E34();
    ((S_80090200_1 *)arg3)->unk_1C = (s32) (((S_80090200_1 *)arg3)->unk_1C & ~0x20);
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = &D_800DD0E8;
    func_80048A44(arg2, *((((s32) (D_80083228 + ((S_80090200_1 *)arg3)->unk_2A + 0x100) >> 9) & 7) + &D_800DD0E8), 0, 1);
}
