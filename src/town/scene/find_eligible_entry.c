#include "common.h"
#include "town/scene.h"
#include "town/player/script_flags.h"

/* Return the first choice whose flag is clear and whose predicate returns zero. */
s32 find_eligible_entry(void *context, s32 unused_group_bits)
{
    TownObjectSet *set = context;
    s32 *flag_page;
    s32 entry_index;

    process_town_records(set->flag_records_address, set->flag_record_count);
    flag_page = (s32 *)0x80020000;
    do {
        flag_page[-3874] = 0;
        entry_index = 0;
        while (get_script_flag_mask(set->choices[entry_index].script_flag) != 0 ||
               set->choices[entry_index].predicate((SquareSceneEntry *)set, entry_index) != 0) {
            entry_index++;
        }
    } while (flag_page[-3874] != 0);
    return entry_index;
}
