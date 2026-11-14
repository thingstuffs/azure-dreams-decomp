/* Relinked copy of town/func_80881478 (func_80881478.c); retail differs only at relocation sites. */
#include "common.h"
#include "town/scene.h"
#include "town/devkit/flag_test_imports.h"


extern s32 devkit_scene_list_length[];
extern u8 D_807000C4[];

/* Read the selected table value between mode-one setup and completion calls. */
s32 read_selected_devkit_entry_value(void) {
    s32 entry_value;
    s32 entry_index;

    func_80700894(1);
    entry_index = devkit_scene_list_length[0];
    entry_value = *(s32 *)(D_807000C4 + (entry_index * 0x10) + 0x674);
    post_slot_ready_code(entry_index, 1);
    func_80700804(1);
    return entry_value;
}
