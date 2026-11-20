#include "engine/message.h"
#include "engine/graphics.h"
#include "engine/script.h"

/* Render text glyphs and advance the cursor according to the display rate. */
void render_message_glyphs(MessageWindow *window)
{
    s32 neg_glyph_count;
    s32 glyph_delay;
    s32 column_or_rate;
    u8 *batch_glyph;
    u8 *next_glyph;
    u8 *glyph;
    u8 *fast_cursor;
    u8 *batch_cursor;

    if (window->text_advance_mode != 0) {
        fast_cursor = window->cursor;
        if ((s8)*fast_cursor <= 0) {
            do {
                if ((*fast_cursor == 0) ||
                    (window->column < (s32)window->column_count)) {
                    process_message_control_bytes(window);
                    if ((s8)*window->cursor <= 0) {
                        move_glyph_to_grid_position(
                            window->cursor,
                            window->column,
                            window->row,
                            window->spacing,
                            (s32)window->texture_rect.x,
                            (s32)(s16)(window->texture_rect.y + 2),
                            1);
                        glyph = window->cursor;
                        window->column =
                            (s16)((u16)window->column + 1);
                        next_glyph = glyph + 2;
                        window->cursor = next_glyph;
                        fast_cursor = next_glyph;
                        if ((s8)glyph[2] <= 0) {
                            continue;
                        }
                    }
                } else {
                    script_new_line(window);
                    return;
                }
                break;
            } while (1);
        }
    } else if (window->text_speed < 0) {
        batch_cursor = window->cursor;
        if ((s8)*batch_cursor <= 0) {
            neg_glyph_count = 0;
            do {
                if ((*batch_cursor != 0) &&
                    (window->column >= (s32)window->column_count)) {
                    script_new_line(window);
                    return;
                }
                process_message_control_bytes(window);
                if ((s8)*window->cursor > 0) {
                    return;
                }
                neg_glyph_count -= 1;
                move_glyph_to_grid_position(
                    window->cursor,
                    window->column,
                    window->row,
                    window->spacing,
                    (s32)window->texture_rect.x,
                    (s32)(s16)(window->texture_rect.y + 2),
                    1);
                column_or_rate = ((u16)window->column);
                batch_glyph = window->cursor;
                column_or_rate += 1;
                window->column = (s16)column_or_rate;
                column_or_rate = window->text_speed;
                batch_cursor = batch_glyph + 2;
                window->cursor = batch_cursor;
                if (neg_glyph_count < column_or_rate) {
                    break;
                }
            } while ((s8)batch_glyph[2] <= 0);
        }
        window->text_speed = window->controller->text_speed;
    } else {
        process_message_control_bytes(window);
        if ((s8)*window->cursor <= 0) {
            move_glyph_to_grid_position(
                window->cursor,
                window->column,
                window->row,
                window->spacing,
                (s32)window->texture_rect.x,
                (s32)(s16)(window->texture_rect.y + 2),
                1);
            window->column =
                (s16)((u16)window->column + 1);
            glyph_delay = window->text_speed;
            window->cursor = window->cursor + 2;
            if (glyph_delay != 0) {
                window->countdown = glyph_delay;
                window->message_handler = wait_message_countdown;
            }
        }
    }
}
