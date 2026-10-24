#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_801237A4_arg0.h"
#include "dungeon/menu.h"

extern s32 menu_paired_values[];
extern s32 selected_menu_value;
extern s32 menu_alternate_value_table;


/* Select the indexed value and its paired value from the lookup table. */
void select_paired_value_tables(Rec_func_801237A4_arg0 *record) {
    selected_menu_value = menu_paired_values[record->unk_16];
    menu_alternate_value_table = menu_paired_values[record->unk_16 ^ 1];
}
