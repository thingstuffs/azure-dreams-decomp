/* Relinked copy of town/func_80881478 (func_80881478.c); retail differs only at relocation sites. */
#include "common.h"


extern s32 D_8070070C[];
extern u8 D_807000C4[];
extern void func_80700804(s32);
extern void func_80700894(s32);
extern void post_code_0x107_when_slot_ready(s32, s32);

/* Read the selected table value between mode-one setup and completion calls. */
s32 read_table_between_one_setup(void) {
    s32 entry_value;
    s32 entry_index;

    func_80700894(1);
    entry_index = D_8070070C[0];
    entry_value = *(s32 *)(D_807000C4 + (entry_index * 0x10) + 0x674);
    post_code_0x107_when_slot_ready(entry_index, 1);
    func_80700804(1);
    return entry_value;
}
