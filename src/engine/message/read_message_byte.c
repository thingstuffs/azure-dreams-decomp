#include "engine/message.h"
#include "slus/data.h"

/* Select the camera target slot and load its default byte. */
void read_message_byte(MessageWindow *window) {
    window->controller->camera_target_slot = *window->cursor++;
    window->controller->field3C = message_mode_default_bytes[window->controller->camera_target_slot];
}
