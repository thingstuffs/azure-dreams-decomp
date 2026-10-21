#include "common.h"
#include "shared/game_work.h"

#include "common.h"
#include "engine/message.h"

typedef struct {
    u8 pad0[0x10];
    void (*func10)(void *);
    u8 pad14[4];
    u16 half18;
    u8 pad1A[0x14];
    u8 field2E;
    u8 pad2F[0x58];
    s8 field87;
} Func80038128State;

/* Advance to the next handler when the countdown expires or the global flag permits. */
void wait_message_countdown(Func80038128State *state) {
    GameWork *global = &g_game_work;

    if (state->field87 == 0) {
        if ((((u32)global->buttons) & 0x20) != 0) {
            if (state->field2E == 0) {
                state->field2E = 1;
            }
            state->half18 = 0;
            state->func10 = update_message_window;
            return;
        }
    }

    state->half18 -= 1;
    if ((s16)state->half18 <= 0) {
        state->func10 = update_message_window;
    }
}
