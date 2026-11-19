#include "common.h"
#include "shared/menu_display.h"
#include "engine/menu.h"
#include "slus/data.h"

/* Interpolates table values and fills each entry's three-byte buffer with the result. */
void interpolate_selection_menu_entry_shade(AnimatedSelectionMenuBody *state)
{
    s32 entry_index;
    u8 *row;
    s32 start_value;
    s32 end_value;
    s32 value_delta;
    AnimatedSelectionEntry *entry;
    MenuDisplayNode *obj;

    for (entry_index = 0; entry_index < state->count; entry_index++) {
        entry = state->entries[entry_index];
        row = selection_menu_animation_keys + entry_index * 3;
        start_value = selection_menu_shade_keys[row[state->previous_index] * 4];
        end_value = selection_menu_shade_keys[row[state->selected_index] * 4];
        value_delta = (end_value - start_value) * state->transition_tick / state->transition_frames;

        obj = entry->display;
        obj->block->color.r = start_value + value_delta;
        obj->block->color.g = obj->block->color.r;
        obj->block->color.b = obj->block->color.r;
    }
}
