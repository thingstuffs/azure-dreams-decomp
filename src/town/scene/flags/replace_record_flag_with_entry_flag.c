#include "common.h"
#include "town/player.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"
#include "town/scene.h"


/* Update flags using the record and indexed entry, then return success. */
s32 replace_record_flag_with_entry_flag(TownObjectSet *record, s32 entry_index) {
    clear_script_flag_bit(record->entry_flag);
    set_script_flag_bit(record->choices[entry_index].script_flag);
    return 1;
}
