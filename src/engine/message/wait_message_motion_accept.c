#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x10];
    void (*state_func)(void);
    u8 pad_14[0x1B];
    u8 state_2f;
    u8 pad_30[0x59];
    u8 state_89;
} FuncState;

extern int ms_mot_accpt_ow(u8 state_2f); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void update_message_window(void);

/* ms_mot_accpt_ow: advance the state handler when the state check succeeds or the countdown expires. */
void wait_message_motion_accept(FuncState *state) {
    if (ms_mot_accpt_ow(state->state_2f) == 0) {
        state->state_89 -= 1;
        if ((signed char)state->state_89 >= 0) {
            return;
        }
    }
    state->state_func = update_message_window;
}
