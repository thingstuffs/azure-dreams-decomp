#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_8008F548_0 {
    u8 pad_00[0x38];
    s8 unk_38;
} S_8008F548_0;   /* arg0 in set_the_flag_initialize_associated_state */

typedef struct S_8008F548_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_8008F548_1;   /* arg1 in set_the_flag_initialize_associated_state */

/*
 * Sets the object flag at offset 0x38, stores the supplied initial state at offset 4, and clears
 * its motion word at offset 0x10.
 */
void set_the_flag_initialize_associated_state(S_8008F548_0 *object, S_8008F548_1 *state, s32 initial_value) {
    object->unk_38 = 1;
    state->unk_04 = initial_value;
    state->unk_10 = 0;
}
