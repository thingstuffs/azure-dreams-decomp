#include "script_symbols.h"
#include "common.h"
#include "shared/town_event_buffer.h"


void clear_state_history_and_head_indices(void);
void func_8001844C(s32 entry_code);
void func_8001A418(s32 code);

/* Process flagged type 0x18 entries, displaying messages and invoking their handlers. */
void process_flagged_type_0x18_entries(void) {
    u8 *entry;
    u8 *type_ptr;
    u8 entry_code;

    entry = (u8 *)D_8001B218;
    entry_code = entry[1];
    type_ptr = entry + 1;
    if (entry_code == 0) {
        return;
    }

    do {
        if ((entry_code == 0x18) && (type_ptr[2] & 0x20)) {
            entry_code = entry[0];
            if (entry_code == 0x20) {
                clear_state_history_and_head_indices();
            } else {
                if (entry_code == 0x1C) {
                    func_8001A418(F_get_bike);
                } else if (entry_code == 0x1D) {
                    func_8001A418(F_get_bike_b);
                }
                func_8001A418(entry[0] + GOODS_SAVE_FLG_00);
                func_8001A418(F_sb22_goods_first);
                func_8001844C(entry[0]);
            }
        }
        type_ptr += 4;
        entry_code = type_ptr[0];
        entry += 4;
    } while (entry_code != 0);
}
