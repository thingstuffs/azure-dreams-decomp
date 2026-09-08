#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002644C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x40];
    M2C_UNK * unk_44;
} S_8002644C_0;   /* arg0 in func_8002644C; pointer addresses record offset 0x10 */


M2C_UNK func_80022F3C();                    /* extern */
extern M2C_UNK D_800261F0;
extern M2C_UNK D_80026410;

/* Set record pointers around an update of its embedded data. */
void func_8002644C(void *record_part) {
    ((S_8002644C_0 *)((u8 *)record_part - 0x10))->unk_44 = &D_80026410;
    func_80022F3C(record_part - 0x20, record_part + 0x38);
    ((S_8002644C_0 *)((u8 *)record_part - 0x10))->unk_00 = &D_800261F0;
}
