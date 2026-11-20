#include "engine/message.h"
#include "engine/object.h"
#include "engine/script.h"

/* Updates the runtime selector, clearing active objects when needed, and resets its state. */
void reset_script_message_window(ScriptController *controller, u8 *script, s32 requested_selector)
{
    s32 selector;

    if (is_list_nonempty(controller) != 0) {
        if (controller->reset_requested != 0) {
            remove_all_controller_nodes(controller);
            init_message_window(controller, (u8)requested_selector);
        } else {
            selector = requested_selector & 0xFF;
            if (controller->mode != selector) {
                remove_all_controller_nodes(controller);
                init_message_window(controller, selector);
            }
        }
    } else {
        init_message_window(controller, (u8)requested_selector);
    }
    set_script_text_pointer(controller, script);
}
