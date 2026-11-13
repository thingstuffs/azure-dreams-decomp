#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"

typedef struct S_8008F534_0 {
    u8 pad_00[0x39];
    s8 unk_39;
} S_8008F534_0;   /* arg0 in stop_at_max_y */

typedef struct S_8008F534_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_8008F534_1;   /* arg1 in stop_at_max_y */

/* Set the object flag, store the state value, and clear the state's secondary field. */
void stop_at_max_y(S_8008F534_0 *object, S_8008F534_1 *state, s32 value) {
    object->unk_39 = 1;
    state->unk_04 = value;
    state->unk_10 = 0;
}
