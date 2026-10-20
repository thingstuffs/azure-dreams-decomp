#include "common.h"

extern s32 set_indexed_flag_bit_unless();
extern s32 D_807009E4[];

/* Call set_indexed_flag_bit_unless with 0x152 when the selected grid entry has bit zero set. */
void grid_run_bit_set_operation_a(s32 row, s32 column) {
    if (D_807009E4[((row * 7) + column) * 2] & 1) {
        set_indexed_flag_bit_unless(0x152);
    }
}
