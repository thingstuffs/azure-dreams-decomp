#include "shared/menu_display.h"
#include "common.h"

#include "engine/menu.h"
#include "slus/data.h"

/* Interpolate table values into each target's fields with scales of 30 and 12 and fixed offsets. */
void interpolate_selection_menu_entry_coordinates(AnimatedSelectionMenuBody *state)
{
    AnimatedSelectionMenuBody *settings;
    s32 entry_index;
    u8 *value_row;
    AnimatedSelectionEntry **entry_slot;
    s32 start_value;
    s32 value_delta;
    s32 scaled_weight;
    s32 offset;
    s32 offset2;
    s32 offset3;
    s32 target_value;
    AnimatedSelectionEntry *entry;
    MenuDisplayBlock *target;
    MenuDisplayNode *obj;

    settings = state;

    for (entry_index = 0; entry_index < settings->count; entry_index++) {
        entry_slot = (AnimatedSelectionEntry **)settings + entry_index;
        value_row = selection_menu_animation_keys + entry_index * 3;
        start_value = value_row[settings->previous_index];
        value_delta = value_row[settings->selected_index] - start_value;

        scaled_weight = settings->transition_tick * 30;
        offset = (value_delta * scaled_weight) / settings->transition_frames;
        entry = entry_slot[1];
        obj = entry->display;
        target_value = start_value * 30;
        offset2 = offset + 0x200;
        target_value = target_value + offset2;
        obj->block->fields.depth = (s16)target_value;

        scaled_weight = settings->transition_tick * 12;
        offset2 = (value_delta * scaled_weight) / settings->transition_frames;

        target = obj->block;
        target_value = start_value * 12;
        offset3 = offset2 - 0x40;
        target_value = target_value + offset3;
        target->fields.y = (s16)target_value;

    }
}
