#include "engine/message.h"
#include "engine/message/data.h"
#include "engine/script/vm.h"

/* Initialize the embedded window and reset its script return stack. */
void init_message_window(ScriptController *controller, u8 mode) {
    MessageWindow *window = &controller->window;
    s8 text_speed;

    window->controller = controller;
    copy_window_rect(&window->texture_rect, &message_window_object_template);
    window->spacing = 1;
    window->column_count = 0x20;
    window->width = 0xFC;
    window->x_offset = 0;
    window->scroll_offset = 0;
    window->cursor = message_window_state_data;
    window->row = 0;
    window->column = 0;
    window->text_advance_mode = 0;
    text_speed = controller->text_speed;
    controller->previous_text_speed = text_speed;
    window->text_speed = text_speed;
    window->returns.next = window->returns.addresses;
    window->message_handler = update_message_window;
    controller->mode = mode;
    update_text_row_scale(controller, mode);
}
