#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A553C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
    M2C_UNK * unk_10;
} S_800A553C_0;   /* arg0 in func_800A553C; pointer addresses record offset 0x10 */


M2C_UNK func_80033D08();                      /* extern */
M2C_UNK func_80094A38();           /* extern */
extern M2C_UNK D_800A5638;
extern M2C_UNK D_800A5FDC;
extern s32 D_800D0460;
extern M2C_UNK D_800D0C50;

/* Initialize the record pointers and shared state before handing off the record. */
void func_800A553C(void *record_data) {
    ((S_800A553C_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_800A5638;
    func_80094A38(&D_800D0C50, record_data);
    ((S_800A553C_0 *)((u8 *)record_data - 0x10))->unk_10 = &D_800A5FDC;
    D_800D0460 = 0;
    func_80033D08(record_data);
}
