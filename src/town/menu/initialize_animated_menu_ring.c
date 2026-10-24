#include "common.h"
#include "town/menu/motion.h"

typedef struct S_800A32F0_0 {
    s32 * unk_00;
    u8 pad_04[0x4];
    s16 unk_08;
    u8 pad_0A[0x6];
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
} S_800A32F0_0;   /* arg0 in initialize_animated_menu_ring */

/* Initialize state values and install the next handler. */
void initialize_animated_menu_ring(S_800A32F0_0 *state) {
    state->unk_14 = 0xC0;
    state->unk_1C = 0x60;
    state->unk_08 = 0x14;
    state->unk_10 = 0;
    state->unk_18 = 0;
    state->unk_00 = &tick_menu_motion_fade;
}
