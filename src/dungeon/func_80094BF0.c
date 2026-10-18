#include "shared/game_work.h"
#include "shared/dir_step.h"



typedef struct {
    s16 value;
    s16 unk2;
    u16 flags;
} Entry;


/* Returns the grid entry value at the selected offset and writes its flags. */
s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags)
{
    s32 grid_x;
    s32 grid_y;
    s32 entry_index;
    GameWork *state;
    Entry *entry;

    grid_x = x + dir_step_x[offset_index];
    state = &g_game_work;
    grid_y = y + dir_step_y[offset_index];
    entry_index = grid_x + (grid_y << state->map.shiftX);
    entry = (Entry *)((entry_index * sizeof(Entry)) +
                      (unsigned long)((Entry *)state->map.cells));
    *flags = entry->flags;
    return entry->value;
}
