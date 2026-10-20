#include "common.h"

extern s32 dispatch_entry_resource_values[];
extern s32 D_80189394;
extern s32 D_801B8EB8;
extern void play_selected_movie_and_restore_display(void);
extern void load_dispatch_entry_files(u16);

/* Run town_movie_exe with the supplied value and selected table entry, then process record zero. */
void town_movie_exe(s32 table_index, s32 value) {
    s32 table_value = dispatch_entry_resource_values[table_index];

    D_80189394 = value;
    D_801B8EB8 = table_value;
    play_selected_movie_and_restore_display();
    load_dispatch_entry_files(0);
}
