#include "common.h"
#include "m2c_compat.h"

s32 testResidentBitmapBit();                         /* extern */
extern s16 D_800D1064[];

/* Passes the selected table entry to testResidentBitmapBit. */
void func_800A98C4(s32 table_index) {
    testResidentBitmapBit(D_800D1064[table_index]);
}
