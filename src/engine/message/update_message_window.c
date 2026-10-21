#include "slus/owned_80038A10.h"

#include "slus/owned_80038A10.h"
#include "engine/message.h"

void update_message_window(Func80038A10State *input_state) {
    Func80038A10State *state = input_state;
    GameWork *global = &g_game_work;
    void *context = input_state->field80;
    void (*handler)(Func80038A10State *);

    current_message_window_state = state;

    if (state->field87 == 0) {
        if ((((u32)global->buttons) & 0x20) != 0) {
            if (state->field2E == 0) {
                state->field2E = 1;
            }
        }
    }

    handler = update_message_window;

    do {
        if (interpret_script_opcodes_until_action_changes((struct RuntimeContext *)state, (u8 *)context) == 0) {
            break;
        }
    } while (state->func10 == handler);
}
Func80038A10State * current_message_window_state = 0;
