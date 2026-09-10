#include "common.h"
#include "m2c_compat.h"

typedef struct S_80098544_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x2A];
    s16 unk_36;
    s16 unk_38;
} S_80098544_0;   /* arg0 in func_80098544 */

typedef struct S_80098544_1 {
    s32 unk_00;
    s32 unk_04;
} S_80098544_1;   /* out in func_80098544 */


M2C_UNK func_80099754();
extern M2C_UNK D_800984AC;

/* Advance the fixed-point coordinates toward their targets and finish when the countdown expires. */
void func_80098544(S_80098544_0 *state, void *position_data) {
    S_80098544_1 *position;
    s16 remaining;
    register s32 current_coord ASM_REG("$3");
    u16 steps_left;
    s32 target_y;

    do {
        position = position_data;
    } while (0);
    steps_left = state->unk_0A.s - 1;
    state->unk_0A.s = steps_left;
    if ((s16) steps_left > 0) {
        current_coord = position->unk_00;
        position->unk_00 = (s32) (current_coord + ((s32) ((state->unk_36 << 0x10) - current_coord) / (s16) steps_left));
        target_y = state->unk_38;
        current_coord = position->unk_04;
        remaining = state->unk_0A.u;
        position->unk_04 = (s32) (current_coord + ((s32) ((target_y << 0x10) - current_coord) / remaining));
        return;
    }
    position->unk_00 = (s32) (state->unk_36 << 0x10);
    position->unk_04 = (s32) (state->unk_38 << 0x10);
    func_80099754(position);
    state->unk_04 = &D_800984AC;
}
