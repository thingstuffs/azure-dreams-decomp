#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/script/vm.h"
#include "slus.h"

typedef struct S_80039A88_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_80039A88_0;   /* arg0 in script_wait_sound_idle */

/* Opcode 0x56: Wait while the sound status is nonzero. */
void script_wait_sound_idle(S_80039A88_0 *state) {
    if (read_sound_mode_blocking_status(4) != 0) {
        state->unk_10 = 0;
        state->unk_1C = (s32) (state->unk_1C - 1);
    }
}
