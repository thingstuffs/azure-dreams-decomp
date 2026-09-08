#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 *D_80175D50[3];
typedef struct S_8016F2A4_0 {
    u8 pad_00[0xCF];
    u8 unk_CF;
} S_8016F2A4_0;   /* *D_80175D50 in func_8016F2A4 */

/* Return whether the first entry's unk_CF field is zero. */
s32 func_8016F2A4(void) {
    return ((S_8016F2A4_0 *)(*D_80175D50))->unk_CF == 0;
}
