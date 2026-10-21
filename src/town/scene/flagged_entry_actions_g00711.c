/* Process flagged entries and clear scene history (G00711). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80471198. */
#include "town/scene/flagged_entry_actions_g00711.h"

/* Pass the two context regions to func_80018824 with their sizes. */
void clear_state_history_and_head_indices(void) {
    TownStateRecord *context_base;

    context_base = D_80016000->unk_38;
    func_80018824((s8 *)context_base->history, 0xC0);
    func_80018824((s8 *)context_base->headIndices, 0x10);
}

/* Process flagged type 0x18 entries, displaying messages and invoking their handlers. */
void process_flagged_type_0x18_entries(void) {
    u8 *entry;
    u8 *type_ptr;
    u8 entry_code;

    entry = (u8 *)town_event_records;
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
