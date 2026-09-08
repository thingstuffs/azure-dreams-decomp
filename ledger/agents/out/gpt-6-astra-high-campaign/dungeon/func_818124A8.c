#include "common.h"
#include "m2c_compat.h"

typedef struct S_800274A8_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x3C];
    s32 unk_54;
} S_800274A8_0;   /* arg0 in func_800274A8; pointer addresses record offset 0x10 */


M2C_UNK func_80025598();                         /* extern */
M2C_UNK func_80028620();                      /* extern */
extern M2C_UNK D_80027E10;

/* Reset the record handler, restore its saved state, and run cleanup helpers. */
void func_800274A8(void *record) {
    ((S_800274A8_0 *)((u8 *)record - 0x10))->unk_00 = &D_80027E10;
    ((S_800274A8_0 *)((u8 *)record - 0x10))->unk_10 = (s32) ((S_800274A8_0 *)((u8 *)record - 0x10))->unk_14;
    func_80025598(((S_800274A8_0 *)((u8 *)record - 0x10))->unk_54);
    func_80028620(record - 0x20);
}
