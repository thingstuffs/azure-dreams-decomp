#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

extern s32 D_80093638;
extern M2C_UNK D_800D0078;

/* Initialize the record and set its first pointer to D_80093638. */
void func_80093704(M2C_UNK **record, void *ptr, void *ptr2) {
    func_80094984((s32 *) &D_800D0078, (Rec_func_80094268_arg0 *) record, ptr2);
    *record = &D_80093638;
}
