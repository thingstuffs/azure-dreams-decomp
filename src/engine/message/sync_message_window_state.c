#include "engine/message.h"
#include "engine/message/data.h"

extern s32 return_zero_variadic(const char *format, ...);

/* Processes global state, updates the inner context, and saves then clears its status byte. */
void sync_message_window_state(MessageWindowLinks *links)
{
    ScriptController *controller = &runtime_script_state;

    return_zero_variadic(message_window_primary_sync_data, controller);
    return_zero_variadic(message_window_tail_sync_data, &controller->window.cursor);
    return_zero_variadic(message_window_detail_sync_data, &controller->window.message_handler);
    sync_message_window_data(links->window);
    links->window->field86 = links->window->active;
    links->window->active = 0;
}
