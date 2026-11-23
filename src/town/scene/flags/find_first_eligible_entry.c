#include "common.h"
#include "town/scene/flags.h"
#include "town/player/state.h"
#include "town/scene.h"

/* Copy, in this TOWN script module, of the module-0 helper find_eligible_entry (src/town/func_8032F794.c). */

extern s32 D_80019550;

/* Return the first entry whose flag is clear and whose callback returns zero, rescanning while D_80019550 is set. */
s32 find_first_eligible_entry(TownObjectSet *set) {
    s32 entry_index;

    /* BYTES: Pass the table as an integer: a pointer argument swaps the operands of one addu. */
    process_town_records((unsigned long)set->flag_dependencies, set->flag_dependency_count);
    do {
        D_80019550 = 0;
        entry_index = 0;
        while (get_script_flag_mask(set->choices[entry_index].script_flag) != 0 ||
               set->choices[entry_index].predicate(set, entry_index) != 0) {
            entry_index++;
        }
    } while (D_80019550 != 0);
    return entry_index;
}
