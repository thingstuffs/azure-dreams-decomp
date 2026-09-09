#include "common.h"
#include "m2c_compat.h"

/* extern */
extern M2C_UNK D_800B2A60;

typedef struct S_800B2C68_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_800B2C68_0;   /* arg0 in func_800B2C68 */


s32 func_800AB378(S_800B2C68_0 *, void *, void *, void *);
/* Set the state pointer to D_800B2A60 when func_800AB378 succeeds. */
void func_800B2C68(S_800B2C68_0 *state, void *context, void *data, void *extra_data) {
    if (func_800AB378(state, context, data, extra_data) != 0) {
        state->unk_8C = &D_800B2A60;
    }
}
