#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_800CCF48_0 {
    u8 pad_00[0x68];
    u16 unk_68;
    u8 pad_6A[0x8];
    s16 unk_72;
} S_800CCF48_0;   /* arg0 in func_800CCF48 */

void func_800CCF48(S_800CCF48_0 *arg0) {
    arg0->unk_72 = 0x400;
    arg0->unk_68 = (u16) (arg0->unk_68 + 1);
}
