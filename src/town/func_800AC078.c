#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A97D8_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x5C];
    M2C_UNK * unk_60;
} S_800A97D8_0;   /* arg0 in func_800A97D8; pointer addresses record offset 0x10 */

typedef struct S_800A97D8_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A97D8_1;   /* arg1 in func_800A97D8 */


extern M2C_UNK D_800A6CF0;
extern M2C_UNK D_800A9778;

void func_800A97D8(void *arg0, S_800A97D8_1 *arg1) {
    ((S_800A97D8_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_800A6CF0;
    ((S_800A97D8_0 *)((u8 *)arg0 - 0x10))->unk_60 = &D_800A9778;
    arg1->unk_08 = 0;
}
