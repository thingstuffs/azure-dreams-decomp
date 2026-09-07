#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C3960_0 {
    u8 pad_00[0x54];
    M2C_UNK (*unk_54)();
} S_800C3960_0;   /* arg0 in func_800C3960 */


/* cfail-repair: tf7-phase1-cache-v3 */
void func_800C3960(S_800C3960_0 *arg0) {
    arg0->unk_54();
}
