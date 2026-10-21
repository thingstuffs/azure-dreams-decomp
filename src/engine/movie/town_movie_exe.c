#include "common.h"
#include "engine/movie.h"
#include "engine/resource.h"
#include "slus/data.h"

extern void play_selected_movie_and_restore_display(void);

/* Run town_movie_exe with the supplied value and selected table entry, then process record zero. */
void town_movie_exe(s32 table_index, s32 value) {
    s32 table_value = dispatch_entry_resource_values[table_index];

    movie_frame_control = value;
    movie_start_sector = table_value;
    play_selected_movie_and_restore_display();
    load_dispatch_entry_files(0);
}
