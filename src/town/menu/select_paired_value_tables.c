#include "common.h"

extern s32 menu_paired_values[];
extern s32 selected_menu_value;
extern s32 D_80126AD0;

/* Load the selected table value and its paired value into global state. */
void select_paired_value_tables(void *selection) {
    u8 index = ((u8 *)selection)[0x16];

    selected_menu_value = menu_paired_values[index];
    D_80126AD0 = menu_paired_values[((u8 *)selection)[0x16] ^ 1];
}
