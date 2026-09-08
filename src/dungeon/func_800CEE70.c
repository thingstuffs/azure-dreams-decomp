#include "common.h"
#include "m2c_compat.h"

/* extern */
s32 func_800AD9B4();                /* extern */
extern M2C_UNK D_800D4494;

typedef struct S_800D45D0_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_800D45D0_0;   /* arg0 in func_800D45D0 */


s32 func_800AB378(S_800D45D0_0 *, M2C_UNK, M2C_UNK, M2C_UNK);
/* Select D_800D4494 after the countdown completes and the actor check succeeds. */
void func_800D45D0(S_800D45D0_0 *state, M2C_UNK transform, M2C_UNK entity, M2C_UNK actor) {
    if ((func_800AB378(state, transform, entity, actor) != 0) && ((func_800AD9B4(entity, actor) << 0x10) > 0)) {
        state->unk_8C = &D_800D4494;
    }
}
