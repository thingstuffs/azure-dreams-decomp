#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_800CCF30_0 {
    u8 pad_00[0x68];
    u16 unk_68;
    u8 pad_6A[0x8];
    s16 unk_72;
} S_800CCF30_0;   /* arg0 in func_800CCF30 */

/* Sets the state's 0x72 field to 0x800 and increments its 0x68 counter. */
void func_800CCF30(S_800CCF30_0 *state) {
    state->unk_72 = 0x800;
    state->unk_68 = (u16) (state->unk_68 + 1);
}
