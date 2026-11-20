#include "engine/message.h"
#include "engine/graphics.h"
#include "slus/data.h"

/* Scrolls the rows up and clears the last row when a row-height step completes. */
void scroll_message_rows(MessageWindow *window)
{
    s32 row;

    window->scroll_offset += 4;
    row = 0;
    if (window->scroll_offset < message_row_heights[window->spacing]) {
        return;
    }

    window->scroll_offset = 0;
    if (window->row_count - 1 > 0) {
        s32 *row_heights = message_row_heights;

scroll_row:
        move_vram_rect(
            (s16)(window->texture_rect.x + window->x_offset),
            (s16)(window->texture_rect.y + window->scroll_offset + row_heights[window->spacing] * (row + 1) + 2),
            window->width / 4,
            *(s16 *)&row_heights[window->spacing],
            window->texture_rect.x + window->x_offset,
            window->texture_rect.y + window->scroll_offset + row_heights[window->spacing] * row
                + 2);
        row += 1;
        if (row < window->row_count - 1) {
            goto scroll_row;
        }
    }

    {
        s32 *height_table;
        s32 *row_height;

        height_table = message_row_heights;
        row_height = height_table + window->spacing;

        fill_vram_rect(
            (s16)(window->texture_rect.x + window->x_offset),
            (s16)(window->texture_rect.y + window->scroll_offset + *row_height * (window->row_count - 1) + 2),
            window->width / 4,
            *(s16 *)row_height,
            0, 0, 0);
    }
    window->message_handler = update_message_window;
}
