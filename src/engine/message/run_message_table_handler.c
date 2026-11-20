#include "engine/message.h"

typedef s32 (*Func8003875CHandler)(u32);

extern u8 D_80110E98[];

/* Calls the selected handler and schedules the follow-up callback on a nonzero result. */
void run_message_table_handler(MessageWindow *window) {
    Func8003875CHandler *group;
    s32 result;

    group = *(Func8003875CHandler **)((u8 *)&D_80110E98 + (window->service_index * 4));
    result = group[window->service_entry](window->service_value);
    if (result != 0) {
        window->service_value = result;
        window->message_handler = update_message_window;
    }
}
