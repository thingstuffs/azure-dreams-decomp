#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033B2C();                         /* extern */
extern s16 D_800D1064[];

/* Passes the selected table entry to func_80033B2C. */
void func_800A98C4(s32 table_index) {
    func_80033B2C(D_800D1064[table_index]);
}
