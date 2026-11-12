#include "script_symbols.h"
#include "common.h"
#include "town/scene/mode_data.h"
#include "town/scene/entry_requests.h"
#include "shared/record_ptrs.h"
#include "town/scene/resource.h"
#include "shared/town_root.h"
#include "town/player/state.h"
#include "town/scene/event.h"

typedef struct TownRecord {
    s8 pad0[8];
    s32 index;
    s8 padC[0x34];
    u8 *entries;
} TownRecord;


/* Loads the current entry's value, conditionally clears it, and handles the follow-up check. */
s32 load_entry_value_and_handle_followup(void *object, s32 entry_index) {
    TownRecord *record;

    record = (TownRecord *)town_scene_root;
    scene_cell_dispatch_code = record->entries[(record->index * 8) + 4];
    if (process_checked_entry(object, entry_index) != 0) {
        TownRecord *clear_record;

        clear_record = (TownRecord *)town_scene_root;
        clear_record->entries[(clear_record->index * 8) + 4] = 0;
        scene_cell_dispatch_code = 0;
    }
    if (get_script_flag_mask(F_sbs14_pad20) == 0) {
        invoke_callback_event_11();
    }
    return 0;
}
