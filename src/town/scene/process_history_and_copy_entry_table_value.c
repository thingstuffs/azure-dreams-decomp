#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern s32 D_800189BC[];
extern s32 D_80019548[];
void process_history_entries_by_mode(void);

/* Call close_dialogue_if_open_hand, then copy the table entry selected by the current index. */
void process_history_and_copy_entry_table_value(s32 first_input, s32 second_input)
{
    process_history_entries_by_mode();
    D_80019548[0] = D_800189BC[town_scene_root->entry_index];
}
