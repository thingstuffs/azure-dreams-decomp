#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_800789B8[9];
typedef struct S_80025C58_0 {
    u8 pad_00[0x4];
    u8 ** unk_04;
} S_80025C58_0;   /* arg0 in func_80025C58 */

/* Sets the destination byte pointer to D_800789B8. */
void func_80025C58(S_80025C58_0 *dest) {
    *dest->unk_04 = D_800789B8;
}
