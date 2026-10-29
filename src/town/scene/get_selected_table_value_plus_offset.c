/* Relinked copy of town/get_table_entry_plus_global (get_table_entry_plus_global.c); retail differs only at relocation sites. */
#include "common.h"
#include "town/scene.h"
#include "town/scene/flags.h"

extern s32 func_80000760(s32);
extern s32 func_800007F0(s32);

extern s32 D_00000D9C[3];
extern s32 D_00000DC8[3];
extern s32 D_00000E50[3];

/* Returns the selected table entry's value plus the global offset after updating state. */
s32 get_selected_table_value_plus_offset(void) {
    s32 selectedIndex;
    s32 entryValue;

    func_800007F0(1);
    selectedIndex = D_00000D9C[0];
    entryValue = D_00000DC8[selectedIndex * 4];
    post_code_107_if_entry_bit_0(selectedIndex, 1);
    func_80000760(1);
    return entryValue + D_00000E50[0];
}
