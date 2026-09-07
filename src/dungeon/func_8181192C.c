#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002692C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x18];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
} S_8002692C_0;   /* arg0 in func_8002692C; pointer addresses record offset 0x10 */


M2C_UNK func_80026708();                    /* extern */
M2C_UNK func_8002675C();                      /* extern */
extern M2C_UNK D_800266B0;

void func_8002692C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_a1;

    ((S_8002692C_0 *)((u8 *)arg0 - 0x10))->unk_1C = arg2;
    temp_a1 = arg2 == 0x13;
    ((S_8002692C_0 *)((u8 *)arg0 - 0x10))->unk_20 = temp_a1;
    func_80026708(arg0 + 0x20, temp_a1);
    func_8002675C(arg0 + 0x2C);
    ((S_8002692C_0 *)((u8 *)arg0 - 0x10))->unk_24 = arg3;
    ((S_8002692C_0 *)((u8 *)arg0 - 0x10))->unk_2C = arg1;
    ((S_8002692C_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_800266B0;
}
