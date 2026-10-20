#include "common.h"

extern void runtime_set_record_value_and_buffer(void *controller, s32 reset_value);
extern s32 is_list_nonempty(void *controller);
extern void remove_all_controller_nodes(void *controller);
extern void init_message_window(void *controller, s32 selector);

/* Updates the runtime selector, clearing active objects when needed, and resets its state. */
void func_80035164(void *controller, s32 reset_value, s32 requested_selector)
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
