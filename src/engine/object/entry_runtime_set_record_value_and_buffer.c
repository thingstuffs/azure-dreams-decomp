#include "common.h"
#include "engine/object.h"
#include "engine/script.h"

extern void init_message_window(void *controller, s32 selector);

/* Updates the runtime selector, clearing active objects when needed, and resets its state. */
void prepare_script_controller_and_set_cursor(void *controller, s32 reset_value, s32 requested_selector)
{
    s32 selector;

    if (is_list_nonempty(controller) != 0) {
        if (*(u8 *)controller != 0) {
            remove_all_controller_nodes(controller);
            init_message_window(controller, (u8)requested_selector);
        } else {
            selector = requested_selector & 0xFF;
            if (*((u8 *)controller + 2) != selector) {
                remove_all_controller_nodes(controller);
                init_message_window(controller, selector);
            }
        }
    } else {
        init_message_window(controller, (u8)requested_selector);
    }
    runtime_set_record_value_and_buffer(controller, reset_value);
}
