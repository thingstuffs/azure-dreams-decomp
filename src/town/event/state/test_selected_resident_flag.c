#include "common.h"
#include "m2c_compat.h"

s32 test_resident_bitmap_bit();                         /* extern */
extern s16 D_800D1064[];

/* Passes the selected table entry to test_resident_bitmap_bit. */
void test_selected_resident_flag(s32 table_index) {
    test_resident_bitmap_bit(D_800D1064[table_index]);
}
