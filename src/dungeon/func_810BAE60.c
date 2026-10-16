/* Relink of matched dungeon/func_800CEE70; every changed retail word is a paired relocation. */
#define D_800D4494 D_80164E54
#include "common.h"
#include "m2c_compat.h"

/* extern */
s32 func_800AD9B4();                /* extern */
extern u8 D_80164E54;

typedef struct S_800D45D0_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_800D45D0_0;   /* arg0 in func_80166660 */


s32 func_800AB378(S_800D45D0_0 *, M2C_UNK, M2C_UNK, M2C_UNK);
/* Select D_80164E54 after the countdown completes and the actor check succeeds. */
void func_80166660(S_800D45D0_0 *state, M2C_UNK transform, M2C_UNK entity, M2C_UNK actor) {
    if ((func_800AB378(state, transform, entity, actor) != 0) && ((func_800AD9B4(entity, actor) << 0x10) > 0)) {
        state->unk_8C = &D_80164E54;
    }
}
