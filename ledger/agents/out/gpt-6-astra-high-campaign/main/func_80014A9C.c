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

/* Initializes record values and installs its callback pointer. */
void func_80027A9C(void *record) {
    s32 record_base;

    record_base = record - 0x20;
    ((S_80027A9C_0 *)((u8 *)record - 0x10))->unk_30 = func_8004F418(record_base, record + 0xC);
    ((S_80027A9C_0 *)((u8 *)record - 0x10))->unk_34 = func_80026ED0(record_base, ((S_80027A9C_0 *)((u8 *)record - 0x10))->unk_1C);
    func_800209C4();
    ((S_80027A9C_0 *)((u8 *)record - 0x10))->unk_00 = &D_8002789C;
}
