#include "common.h"
#include "m2c_compat.h"

typedef struct S_80027A9C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x18];
    s32 unk_1C;
    u8 pad_20[0x10];
    s32 unk_30;
    s32 unk_34;
} S_80027A9C_0;   /* arg0 in func_80027A9C; pointer addresses record offset 0x10 */


M2C_UNK func_800209C4();                            /* extern */
s32 func_80026ED0();                        /* extern */
s32 func_8004F418();                        /* extern */
extern M2C_UNK D_8002789C;

void func_80027A9C(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 - 0x20;
    ((S_80027A9C_0 *)((u8 *)arg0 - 0x10))->unk_30 = func_8004F418(temp_s1, arg0 + 0xC);
    ((S_80027A9C_0 *)((u8 *)arg0 - 0x10))->unk_34 = func_80026ED0(temp_s1, ((S_80027A9C_0 *)((u8 *)arg0 - 0x10))->unk_1C);
    func_800209C4();
    ((S_80027A9C_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_8002789C;
}
