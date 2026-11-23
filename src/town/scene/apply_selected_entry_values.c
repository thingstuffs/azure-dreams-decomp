#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene.h"




/* Apply the selected entry and record values if the record passes its check. */
s32 apply_selected_entry_values(TownObjectSet *record, s32 entry_index) {
    if (check_record_flag_if_unblocked(record) != 0) {
        set_script_flag_bit(record->choices[entry_index].script_flag);
        clear_script_flag_bit(record->entry_flag);
        return 1;
    }
    return 0;
}
