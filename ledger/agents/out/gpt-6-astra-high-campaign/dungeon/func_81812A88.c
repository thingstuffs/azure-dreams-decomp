#include "common.h"
#include "m2c_compat.h"

typedef struct S_80027A88_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
    s32 unk_10;
} S_80027A88_0;   /* arg0 in func_80027A88; pointer addresses record offset 0x10 */


M2C_UNK func_80027A20();                      /* extern */
s32 func_8004CB2C();                             /* extern */
extern M2C_UNK D_80027A68;

/* Reset the handler and state when the record check succeeds, then dispatch its callback. */
void func_80027A88(void *record) {
    if (func_8004CB2C(record + 0x2C) != 0) {
        ((S_80027A88_0 *)((u8 *)record - 0x10))->unk_00 = &D_80027A68;
        ((S_80027A88_0 *)((u8 *)record - 0x10))->unk_10 = 0;
    }
    func_80027A20(record);
}
