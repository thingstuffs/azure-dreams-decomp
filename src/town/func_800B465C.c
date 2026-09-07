#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800B1D00;

typedef struct S_800B1DBC_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800B1DBC_0;   /* arg0 in func_800B1DBC */

void func_800B1DBC(S_800B1DBC_0 *arg0) {
    arg0->unk_10 = &D_800B1D00;
}
