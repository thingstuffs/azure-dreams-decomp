#include "common.h"
#include "m2c_compat.h"

/* extern */
s32 func_800AD9B4();                /* extern */
extern void func_80171138(void *, void *, void *, void *);

typedef struct S_800D45D0_0 {
    u8 pad_00[0x8C];
    void (*unk_8C)(void *, void *, void *, void *);
} S_800D45D0_0;   /* arg0 in func_80173E00 */


s32 func_800AC010(S_800D45D0_0 *, M2C_UNK, M2C_UNK, M2C_UNK);
/* Select the bank actor callback when the resident checks succeed. */
void func_80173E00(S_800D45D0_0 *state, M2C_UNK transform, M2C_UNK entity, M2C_UNK actor) {
    if ((func_800AC010(state, transform, entity, actor) != 0) && ((func_800AD9B4(entity, actor) << 0x10) > 0)) {
        state->unk_8C = func_80171138;
    }
}
