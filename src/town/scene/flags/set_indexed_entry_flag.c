#include "common.h"
#include "town/player.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene/flags.h"
#include "town/scene.h"

/* Set the indexed entry flag using its identifier and entry pointer. */
void set_indexed_entry_flag(Rec_func_800165F4_arg0 *record, s32 entry_index) {
    TownObjectSet *set = (TownObjectSet *)record;

    set_script_flag_bit(set->choices[entry_index].script_flag);
}
