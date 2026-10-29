/* Set lshop special flag.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00699 - CL:town/func_8032E634, CL:town/func_8032E6A8, CL:town/func_8032E9EC.
 */
#include "town/shop/state/set_lshop_special_flag_g00699.h"
#include "shared/item_ids.h"
#include "town/player/script_flags.h"
#include "town/shop/state.h"
#include "town/shop/object.h"

/* Set flag 0x11F8 when the record bytes are 2 and 0xD. */
void set_lshop_special_flag(S_800191EC_0 *record) {
    if ((record->unk_01 == 0xD) && (record->unk_00 == ITEM_WATER_MEDAL)) {
        set_script_flag_bit(F_sell_mizu_medaru);
    }
}

/* Processes flagged four-byte entries according to the mode, skipping type 0x18. */
void process_lshop_entries(void *entries, s32 entry_mode)
{
    void *entry_list;
    s32 initial_mode;
    u8 *entry;
    s32 entry_index;
    s32 mode;

    entry_list = entries;
    initial_mode = entry_mode;
    entry = entry_list;
    mode = initial_mode;
    entry_index = 0;
    if (entry[1] != 0) {
        entry_list = 0x18;
        do {
            if ((entry[3] & 0x20) && entry[1] != entry_list) {
                if (mode == 0) {
                    append_town_item(entry);
                    entry += 4;
                } else {
                    set_lshop_special_flag(entry);
                    release_lshop_entry(entry_index);
                    entry += 4;
                }
            } else {
                entry += 4;
            }
            entry_index++;
        } while (entry[1] != 0);
    }
    compact_lshop_entry_list();
}
