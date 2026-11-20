#include "engine/message.h"
#include "slus/data.h"

/* Set the number of text rows for this mode and their total height. */
void update_text_row_scale(ScriptController *controller, u8 unused_scale) {
    MessageWindow *window = &controller->window;

    window->row_count = message_mode_row_scale[controller->mode];
    window->height = message_row_heights[window->spacing] * window->row_count;
}
