#include "common.h"
#include "m2c_compat.h"

/* extern */
extern void func_80171138(void *, void *, void *, void *);

typedef struct S_800B2C68_0 {
    u8 pad_00[0x8C];
    void (*unk_8C)(void *, void *, void *, void *);
} S_800B2C68_0;   /* arg0 in func_80173E64 */


s32 func_800AC480(S_800B2C68_0 *, void *, void *, void *);
/* Restore the bank actor callback after the resident state check succeeds. */
void func_80173E64(S_800B2C68_0 *state, void *context, void *data, void *extra_data) {
    if (func_800AC480(state, context, data, extra_data) != 0) {
        state->unk_8C = func_80171138;
    }
}
