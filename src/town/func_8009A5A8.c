#include "common.h"
#include "m2c_compat.h"

typedef struct S_80097D08_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x78];
    s16 unk_7C;
    u8 pad_7E[0x28];
    s8 unk_A6;
} S_80097D08_0;   /* arg0 in func_80097D08; pointer addresses record offset 0x10 */

typedef struct S_80097D08_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80097D08_1;   /* arg1 in func_80097D08 */


extern M2C_UNK D_80097C50;

void func_80097D08(void *arg0, S_80097D08_1 *arg1) {
    ((S_80097D08_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_80097C50;
    arg1->unk_08 = (s32) (((S_80097D08_0 *)((u8 *)arg0 - 0x10))->unk_A6 << 0x10);
    ((S_80097D08_0 *)((u8 *)arg0 - 0x10))->unk_7C = 5;
}
