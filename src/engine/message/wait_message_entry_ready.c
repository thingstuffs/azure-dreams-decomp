#include "engine/message.h"
#include "shared/object_index_slots.h"

/* Sets the object's callback to update_message_window when its entry's field_1 is zero. */
void wait_message_entry_ready(MessageWindow *window)
{
    if (object_index_slots[window->entry_index].active == 0) {
        window->message_handler = update_message_window;
    }
}
