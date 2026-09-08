#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 *D_8001E950[];
typedef struct S_8001C31C_0 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_8001C31C_0;   /* *D_8001E950 in func_8001C31C */

/* Check whether the first entry's state byte is 2. */
s32 func_8001C31C(void) {
    return ((S_8001C31C_0 *)(*D_8001E950))->unk_04 == 2;
}
