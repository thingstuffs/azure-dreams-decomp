/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef void (*Func_800B0E0C_Callback)(M2C_UNK);
extern Func_800B0E0C_Callback D_800D157C[];

typedef struct S_800AE56C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x18];
    s32 unk_38;
} S_800AE56C_0;   /* arg0 in func_800AE56C */

/* Dispatch the callback selected by the byte at the current state offset. */
void func_800AE56C(S_800AE56C_0 *state, M2C_UNK callback_arg) {
    D_800D157C[*(u8 *)(state->unk_38 +
                       state->unk_1C)](callback_arg);
}
