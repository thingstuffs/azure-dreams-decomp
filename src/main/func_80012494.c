#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025494_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
    s32 unk_50;
} S_80025494_0;   /* arg0 in func_80025494; pointer addresses record offset 0x10 */


M2C_UNK func_800230CC();                    /* extern */
extern M2C_UNK D_8002546C;

void func_80025494(void *arg0) {
    ((S_80025494_0 *)((u8 *)arg0 - 0x10))->unk_4C = 1;
    func_800230CC(arg0 - 0x20, arg0 + 0x40);
    ((S_80025494_0 *)((u8 *)arg0 - 0x10))->unk_50 = 1;
    ((S_80025494_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_8002546C;
}
