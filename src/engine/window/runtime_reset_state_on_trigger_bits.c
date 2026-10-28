#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

#include "common.h"
#include "slus/data.h"
#include "engine/window.h"

typedef struct S_8003626C_0 {
    u8 pad_00[0x4C];
    u8 unk_4C;
    u8 pad_4D[0x3];
    s8 unk_50;
    u8 pad_51[0x17];
    void (*unk_68)(struct S_800362A0_0 *);
} S_8003626C_0;   /* arg0 in runtime_reset_state_on_trigger_bits */

/* Resets state fields and selects the next handler when either trigger bit is set. */
void runtime_reset_state_on_trigger_bits(S_8003626C_0 *state) {
    if ((g_game_work.pressed_buttons) & 0x60) {
        state->unk_4C = 0xFF;
        state->unk_50 = 0;
        state->unk_68 = &runtime_mark_state_when_flag_50_set;
    }
}
