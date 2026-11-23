#include "script_symbols.h"
#include "common.h"
#include "town.h"
#include "town/scene/object.h"
#include "town/player.h"
#include "town/player/state.h"
#include "town/scene.h"

/* Processes the object, conditionally passing its stored value to initialize_state_two_entries_pointer. */
void process_entry_with_listed_flag(TownObjectSet *object, s32 context) {
    clear_script_flag_bit(F_sbs34_pad15);
    if ((record_value_table_contains(5) != 0) || (town_pair_table_has_first(5) != 0)) {
        set_script_flag_bit(object->entry_flag);
    }
    process_checked_entry(object, context);
}
