#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8();                             /* extern */

typedef struct S_800A6B70_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800A6B70_0;   /* arg0 in func_800A6B70 */

typedef struct S_800A6B70_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800A6B70_1;   /* arg2 in func_800A6B70 */

/* Advances the phase and sets all three color channels to the same intensity. */
void func_800A6B70(S_800A6B70_0 *phase_state, M2C_UNK unused, S_800A6B70_1 *color) {
    s32 phase;
    s8 intensity;

    phase = phase_state->unk_0C + 1;
    phase_state->unk_0C = phase;
    intensity = (func_800644B8(phase << 6) >> 7) + 0x60;
    color->unk_0E = intensity;
    color->unk_0D = intensity;
    color->unk_0C = intensity;
}
