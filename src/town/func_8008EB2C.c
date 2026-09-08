#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008C214();                      /* extern */
extern u8 D_800FC428;

/* Pass the entry index and its 64-byte record to func_8008C214. */
void func_8008C28C(s32 entry_index) {
    func_8008C214(entry_index, (entry_index << 6) + &D_800FC428);
}
