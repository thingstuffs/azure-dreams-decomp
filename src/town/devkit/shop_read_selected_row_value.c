#include "common.h"

extern s32 devkit_globals_page[];
extern s32 D_80701DC4[];

extern void dev_report_kind_mode_sno(s32 kind);
extern void set_entry_bit_flag(s32 index, s32 entry_index);

/* Read the selected row value and process entry 3 before returning it. */
s32 read_flag_row_report(void) {
    s32 row_index;
    s32 row_value;

    row_index = D_80701DC4[0];
    row_value = *(s32 *)((u8 *)devkit_globals_page + (row_index << 5) + 0x1E40);
    set_entry_bit_flag(row_index, 3);
    dev_report_kind_mode_sno(3);
    return row_value;
}
