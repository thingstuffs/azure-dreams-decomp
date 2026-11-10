#include "common.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "town/player/state.h"


typedef struct S_80098CC0_0 {
    u8 pad_00[0x4];
    void (*unk_04)();
    u8 pad_08[0x8];
    s16 unk_10;
} S_80098CC0_0;   /* arg0 in set_handler_and_countdown_800 */

/* Initialize the state's data pointer and value to forward_state_value_to_handler_a and 0x800. */
void set_handler_and_countdown_800(S_80098CC0_0 *state) {
    state->unk_04 = &forward_state_value_to_handler_a;
    state->unk_10 = 0x800;
}
