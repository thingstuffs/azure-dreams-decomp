#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A6DA0_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x5C];
    s32 unk_60;
} S_800A6DA0_0;   /* arg0 in func_800A6DA0; pointer addresses record offset 0x10 */

typedef struct S_800A6DA0_1 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800A6DA0_1;   /* arg2 in func_800A6DA0 */


M2C_UNK func_8008F104();  /* extern */
M2C_UNK func_8009CD18();             /* extern */
extern M2C_UNK D_800A6CF0;
extern M2C_UNK D_800D0DA8;

void func_800A6DA0(void *arg0, M2C_UNK arg1, S_800A6DA0_1 *arg2) {
    ((S_800A6DA0_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_800A6CF0;
    ((S_800A6DA0_0 *)((u8 *)arg0 - 0x10))->unk_60 = 0;
    func_8009CD18(arg0, arg2, 0x48);
    func_8008F104(arg0, arg1, &D_800D0DA8);
    arg2->unk_20 = 0xC00;
    arg2->unk_1E = 0xC00;
    arg2->unk_1C = 0xC00;
}
