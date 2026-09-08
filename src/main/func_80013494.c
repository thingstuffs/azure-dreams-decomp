#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026494_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x40];
    M2C_UNK * unk_44;
} S_80026494_0;   /* arg0 in func_80026494; pointer addresses record offset 0x10 */


M2C_UNK func_80022FB4();                         /* extern */
extern M2C_UNK D_800261F0;
extern M2C_UNK D_800265B8;

/* Set record pointers around an update of its base record. */
void func_80026494(void *record_part) {
    ((S_80026494_0 *)((u8 *)record_part - 0x10))->unk_44 = &D_800265B8;
    func_80022FB4(record_part - 0x20);
    ((S_80026494_0 *)((u8 *)record_part - 0x10))->unk_00 = &D_800261F0;
}
