#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void D_80098140();

typedef struct S_80098CC0_0 {
    u8 pad_00[0x4];
    void (*unk_04)();
    u8 pad_08[0x8];
    s16 unk_10;
} S_80098CC0_0;   /* arg0 in set_handler_and_countdown_800 */

/* Initialize the state's data pointer and value to D_80098140 and 0x800. */
void set_handler_and_countdown_800(S_80098CC0_0 *state) {
    state->unk_04 = &D_80098140;
    state->unk_10 = 0x800;
}
