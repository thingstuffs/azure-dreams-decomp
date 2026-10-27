#include "common.h"
#include "m2c_compat.h"
#include "town/shop/state.h"

void set_linked_flag(s32 bit_index);                         /* extern */
void clear_linked_flag(s32 bit_index);                         /* extern */
extern u8 devkit_globals_page[];

typedef struct S_8070207C_0 {
    u8 pad_00[0x1DCC];
    u16 unk_1DCC;
    u16 unk_1DCE;
} S_8070207C_0;

typedef struct S_8070207C_1 {
    u8 pad_00[0x1DCC];
    u16 unk_1DCC;
} S_8070207C_1;   /* (D_80700000 + final_index) in shop_dispatch_entry_value */

/* Dispatches the entry's second value based on its first, then processes the first. */
void propagate_indexed_flag_pair(s32 entry_index) {
    s32 entry_offset;
    s32 saved_index;
    s32 final_offset;

    saved_index = entry_index;
    entry_offset = entry_index * 4;
    if (test_linked_flag(((S_8070207C_0 *)(devkit_globals_page + entry_offset))->unk_1DCC) != 0) {
        set_linked_flag(((S_8070207C_0 *)(devkit_globals_page + entry_offset))->unk_1DCE);
    } else {
        clear_linked_flag(((S_8070207C_0 *)(devkit_globals_page + saved_index * 4))->unk_1DCE);
    }
    final_offset = saved_index * 4;
    set_linked_flag(((S_8070207C_1 *)(devkit_globals_page + final_offset))->unk_1DCC);
}
