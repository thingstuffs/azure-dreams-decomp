#include "common.h"
#include "shared/widget_views.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"

   /* initial_data in card_boot_animate_command_panel_selection */

/* Animate the selection marker and entry offsets, then advance the frame counter. */
s32 card_boot_animate_command_panel_selection(CardCommandPanelBody *state)
{
    s32 start_index;
    s32 index_delta;
    s32 scaled_frame;
    s32 position_delta;
    register s32 frame;
    s32 end_frame;
    s32 entry_index;
    s32 result;
    s32 result_2;
    u8 *offset_slot;
    s32 old_offset;
    s32 next_offset;
    u8 offset;
    CardMenuDisplayNode *color_node;
    CardMenuDisplayNode *marker_node;
    MenuDisplayBlock *marker_data;

    start_index = state->previous_selection;
    index_delta = state->selected_entry - start_index;
    scaled_frame = state->animation_tick * 0x10;
    position_delta = (index_delta * scaled_frame) / state->animation_frames;
    entry_index = 0;
    marker_node = state->marker;
    marker_data = marker_node->block;
    position_delta += 10;
    marker_data->fields.y = start_index * 0x10 + position_delta;

    do {
        old_offset = state->row_offsets[entry_index];
        /* Keep the byte-walk address used by the retail induction. */
        offset_slot = ((u8 *)state + entry_index) + 0x7C;
        if (entry_index == state->selected_entry) {
            s32 offset_left;
            s32 active_offset;
            register s32 offset_step;

            active_offset = old_offset;
            offset_left = 8;
            result_2 = state->animation_frames;
            frame = state->animation_tick;
            offset_left -= active_offset;
            result_2 -= frame;
            result_2++;
            offset_step = offset_left / result_2;
            next_offset = active_offset + offset_step;
        } else {
            next_offset = old_offset;
            if (next_offset != 0) {
                next_offset--;
            }
        }
        *offset_slot = next_offset;
        offset = state->row_offsets[entry_index];

        state->highlight[entry_index]->block->fields.x =
            offset + 0x24;
        state->labels[entry_index]->block->fields.x =
            offset + 0x8F;
        state->left[entry_index]->block->fields.x =
            offset + 9;
        state->right[entry_index]->block->fields.x =
            offset + 0x42;

        state->highlight[entry_index]->block->color.r =
            state->row_offsets[entry_index] * 3 + 0x68;
        state->highlight[entry_index]->block->color.g =
            state->row_offsets[entry_index] * 3 + 0x68;
        color_node = state->highlight[entry_index];
        color_node->block->color.b =
            state->row_offsets[entry_index] * 4 + 0x60;
        entry_index++;
    } while (entry_index < 3);

    end_frame = state->animation_tick;
    if (end_frame < state->animation_frames) {
        result = end_frame + 1;
        state->animation_tick = result;
    } else {
        result = end_frame + 1;
    }
    return result;
}
