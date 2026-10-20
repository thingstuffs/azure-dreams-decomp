#include "common.h"

extern s32 D_800FE5C0[];

/* Clears slot 3 and copies the supplied value into slot 0. */
void clear_slot_n_3_copies_slot_n_0(s32 *value) {
    D_800FE5C0[3] = 0;
    D_800FE5C0[0] = *value;
}
