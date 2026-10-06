#include "common.h"
#include "m2c_compat.h"

void func_80094984(void *, void *, void *);       /* extern */
extern s32 D_80093638;
extern M2C_UNK D_800D0078;

/* Initialize the record and set its first pointer to D_80093638. */
void func_80093704(M2C_UNK **record, void *ptr, void *ptr2) {
    func_80094984(&D_800D0078, record, ptr2);
    *record = &D_80093638;
}
