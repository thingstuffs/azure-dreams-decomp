#include "common.h"
#include "engine/message.h"


struct MessageMotionAcceptState {
    u8 pad_00[0x10];
    void (*state_func)(struct Func80038A10State *);
    u8 pad_14[0x1B];
    u8 state_2f;
    u8 pad_30[0x59];
    u8 state_89;
};


/* ms_mot_accpt_ow: advance the state handler when the state check succeeds or the countdown expires. */
void wait_message_motion_accept(MessageMotionAcceptState *state) {
    if (ms_mot_accpt_ow(state->state_2f) == 0) {
        state->state_89 -= 1;
        if ((signed char)state->state_89 >= 0) {
            return;
        }
    }
    state->state_func = update_message_window;
}
