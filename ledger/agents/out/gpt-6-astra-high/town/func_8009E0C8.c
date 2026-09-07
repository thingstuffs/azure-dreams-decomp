#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008F294();             /* extern */
M2C_UNK func_8008F664();             /* extern */
M2C_UNK func_8009539C();                 /* extern */
M2C_UNK func_8009C148(); /* extern */
extern s32 D_80083788;
extern s32 D_800D0428;

typedef struct S_8009B828_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8009B828_0;   /* arg2 in func_8009B828 */

typedef struct S_8009B828_1 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_8009B828_1;   /* arg0 in func_8009B828 */

/* Update motion toward the shared target and advance state when the countdown expires. */
void func_8009B828(S_8009B828_1 *state, M2C_UNK context, S_8009B828_0 *motion, M2C_UNK transition_arg) {
    s32 position;
    u16 ticks_left;

    position = motion->unk_08;
    motion->unk_14 = (s32) ((s32) ((D_80083788 + D_800D0428) - position) / 2);
    func_8009539C(motion, position);
    func_8008F294(context, motion);
    func_8008F664(context, motion);
    ticks_left = state->unk_6C - 1;
    state->unk_6C = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        func_8009C148(state, context, motion, transition_arg);
    }
}
