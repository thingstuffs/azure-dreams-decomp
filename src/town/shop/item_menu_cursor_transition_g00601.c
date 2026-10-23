/* Item menu cursor transition (G00601). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B0FD4, CL:town/func_800B10F4. */
#include "town/shop/item_menu_cursor_transition_g00601.h"

/* Sets fixed values and color bytes on each item's linked records. */
void style_item_menu_entry_records(ItemMenuTransition *collection) {
    s32 entry_index;

    entry_index = 0;
    if (collection->entry_count > 0) {
        do {
            collection->rows->text[entry_index]->data->x = 0x20;
            collection->rows->text[entry_index]->data->red = 0x68;
            collection->rows->text[entry_index]->data->green = 0x68;
            collection->rows->text[entry_index]->data->blue = 0x60;
            collection->rows->left[entry_index]->data->x = 9;
            collection->rows->middle[entry_index]->data->x = 0x39;
            collection->rows->right[entry_index]->data->x = 0x8F;
            entry_index += 1;
        } while (entry_index < collection->entry_count);
    }
}

/* Animate the cursor position, row offsets, and colors during a row transition. */
void animate_item_menu_cursor_transition(ItemMenuTransition *state) {
    s32 start_row;
    s32 start_r_duration;
    s32 start_g_duration;
    s32 end_r_duration;
    s32 end_g_duration;
    s32 slide_offset;
    s32 cursor_offset;
    s32 start_b_duration;
    s32 row_delta;
    s32 scaled_progress;
    s32 end_b_duration;
    ItemMenuRowPrimitive *cursor_prim;

    style_item_menu_entry_records(state);
    start_row = state->start_row;
    row_delta = state->end_row - start_row;
    scaled_progress = state->progress * 0x10;
    cursor_offset = row_delta * scaled_progress / state->duration + 0xA;
    cursor_prim = state->rows->cursor->data;
    cursor_prim->y = (s16)(start_row * 0x10 + cursor_offset);
    slide_offset = (state->progress * 8) / state->duration;
    state->rows->text[state->start_row]->data->x =
        (s16)(0x28 - slide_offset);
    state->rows->text[state->end_row]->data->x =
        (s16)(slide_offset + 0x20);
    state->rows->right[state->start_row]->data->x =
        (s16)(0x97 - slide_offset);
    state->rows->right[state->end_row]->data->x =
        (s16)(slide_offset + 0x8F);
    state->rows->left[state->start_row]->data->x =
        (s16)(0x11 - slide_offset);
    state->rows->left[state->end_row]->data->x = (s16)(slide_offset + 9);
    state->rows->middle[state->start_row]->data->x =
        (s16)(0x41 - slide_offset);
    state->rows->middle[state->end_row]->data->x =
        (s16)(slide_offset + 0x39);
    start_r_duration = state->duration;
    state->rows->text[state->start_row]->data->red =
        (s8)(((start_r_duration - state->progress) * 0x18) / start_r_duration + 0x68);
    start_g_duration = state->duration;
    state->rows->text[state->start_row]->data->green =
        (s8)(((start_g_duration - state->progress) * 0x18) / start_g_duration + 0x68);
    start_b_duration = state->duration;
    state->rows->text[state->start_row]->data->blue =
        (s8)(((start_b_duration - state->progress) << 5) / start_b_duration + 0x60);
    end_r_duration = state->duration;
    state->rows->text[state->end_row]->data->red =
        (s8)(-0x80 - ((end_r_duration - state->progress) * 0x18) / end_r_duration);
    end_g_duration = state->duration;
    state->rows->text[state->end_row]->data->green =
        (s8)(-0x80 - ((end_g_duration - state->progress) * 0x18) / end_g_duration);
    end_b_duration = state->duration;
    state->rows->text[state->end_row]->data->blue =
        (s8)(-0x80 - ((end_b_duration - state->progress) << 5) / end_b_duration);
}
