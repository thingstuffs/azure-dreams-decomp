#include "common.h"
#include "town/devkit.h"
#include "town/data.h"
#include "town/devkit/flag_test_imports.h"

extern u8 devkit_globals_page[];

/* Read the selected table value between mode-one setup and completion calls. */
s32 read_selected_table_value(void) {
    s32 entry_value;
    s32 entry_index;

    func_80700868(1);
    entry_index = devkit_cursor_state[0];
    entry_value = *(s32 *)(devkit_globals_page + (entry_index * 0x10) + 0x674);
    func_8070096C(entry_index, 1);
    func_807007D8(1);
    return entry_value;
}
