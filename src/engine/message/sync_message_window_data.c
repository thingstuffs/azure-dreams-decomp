#include "common.h"
#include "engine/message/data.h"

#include "engine/message.h"
#include "slus.h"

extern u8 D_800809C4[];

extern s32 return_zero_variadic(void *, ...);

/* Synchronize changed data, consume the pending value, and run the state callback. */
void sync_message_window_data(MessageWindow *window)
{
    return_zero_variadic(D_800809C4);
    return_zero_variadic(message_window_audio_sync_data, read_sound_mode_blocking_status(4));
    return_zero_variadic(D_800809C4);

    {
        ScriptController *controller = window->controller;
        s8 current_value = controller->text_speed;
        s8 previous_value = controller->previous_text_speed;
        u8 value_byte = controller->text_speed;

        if (current_value != previous_value) {
            controller->previous_text_speed = value_byte;
            window->text_speed = value_byte;
        }
    }

    if (window->controller->pending_script != 0) {
        if (window->message_handler == scroll_message_rows) {
            do {
                scroll_message_rows(window);
            } while (window->message_handler != update_message_window);
        }

        {
            u8 *pending_script;
            pending_script = window->controller->pending_script;
            window->text_advance_mode = 0;
            window->message_handler = update_message_window;
            window->returns.next = window->returns.addresses;
            window->cursor = pending_script;
            window->controller->pending_script = 0;
        }
    }

    if (window->message_handler == 0) {
        window->message_handler = update_message_window;
    }
    window->message_handler(window);
}
