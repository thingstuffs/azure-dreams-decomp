#include "common.h"

#include "common.h"
#include "engine/movie.h"
#include "engine/resource.h"
#include "slus/data.h"

extern void play_selected_movie_and_restore_display(void);

/* Store the selected table value and flags with bit 30 set, then invoke the runtime handlers. */
void play_movie_with_fixed_display_flag(s32 table_index, s32 flags)
{
    s32 table_value = dispatch_entry_resource_values[table_index];

    movie_frame_control = flags | 0x40000000;
    movie_start_sector = table_value;
    play_selected_movie_and_restore_display();
    load_dispatch_entry_files(0);
}
