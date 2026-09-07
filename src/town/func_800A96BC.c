#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A6E1C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x5C];
    M2C_UNK * unk_60;
} S_800A6E1C_0;   /* arg0 in func_800A6E1C; pointer addresses record offset 0x10 */

typedef struct S_800A6E1C_1 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x4];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800A6E1C_1;   /* arg2 in func_800A6E1C */


M2C_UNK func_8008F104();  /* extern */
M2C_UNK func_8009CD18();             /* extern */
extern M2C_UNK D_800A6CF0;
extern M2C_UNK D_800A6EA4;
extern M2C_UNK D_800D0DC0;

void func_800A6E1C(void *arg0, M2C_UNK arg1, S_800A6E1C_1 *arg2) {
    ((S_800A6E1C_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_800A6CF0;
    ((S_800A6E1C_0 *)((u8 *)arg0 - 0x10))->unk_60 = &D_800A6EA4;
    func_8009CD18(arg0, arg2, 0xA);
    func_8008F104(arg0, arg1, &D_800D0DC0);
    arg2->unk_20 = 0x1000;
    arg2->unk_1E = 0x1000;
    arg2->unk_1C = 0x1000;
    arg2->unk_16 = 0;
}
