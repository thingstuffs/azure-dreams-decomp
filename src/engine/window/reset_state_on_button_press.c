#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

#include "engine/window.h"

typedef struct S_8003626C_0 {
    u8 pad_00[0x4C];
    u8 unk_4C;
    u8 pad_4D[0x3];
    s8 unk_50;
    u8 pad_51[0x17];
    void (*unk_68)(struct S_800362A0_0 *);
} S_8003626C_0;   /* arg0 in reset_state_on_button_press */

/* Resets state fields and selects the next handler when either trigger bit is set. */
void reset_state_on_button_press(S_8003626C_0 *state) {
    if ((g_game_work.pressed_buttons) & 0x60) {
        state->unk_4C = 0xFF;
        state->unk_50 = 0;
        state->unk_68 = &request_message_advance_on_first_flag;
    }
}
