#include "common.h"

#include "common.h"

extern s32 dispatch_entry_resource_values[];
extern s32 D_80189394;
extern s32 D_801B8EB8;

extern void play_selected_movie_and_restore_display(void);
extern void load_dispatch_entry_files(u16 entry_index);

/* Store the selected table value and flags with bit 30 set, then invoke the runtime handlers. */
void play_movie_with_fixed_display_flag(s32 table_index, s32 flags)
{
    s32 table_value = dispatch_entry_resource_values[table_index];

    D_80189394 = flags | 0x40000000;
    D_801B8EB8 = table_value;
    play_selected_movie_and_restore_display();
    load_dispatch_entry_files(0);
}
