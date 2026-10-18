#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_80098104_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80098104_0;   /* arg0 in tick_countdown_and_initialize_handler */


void initialize_record_with_handler_and_count(S_80098104_0 *, M2C_UNK, s32);
/* Decrement the countdown and call initialize_record_with_handler_and_count when it reaches zero. */
void tick_countdown_and_initialize_handler(S_80098104_0 *state, M2C_UNK context, s32 mode) {
    u16 remaining_ticks;

    remaining_ticks = state->unk_0A - 1;
    state->unk_0A = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        initialize_record_with_handler_and_count(state, context, mode);
    }
}
