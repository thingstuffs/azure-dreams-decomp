#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_8008BA00;
extern M2C_UNK D_8008BC58;
extern u8 D_800FC418;

typedef struct S_8008BED8_0 {
    u8 pad_00[0x68];
    M2C_UNK * unk_68;
} S_8008BED8_0;   /* arg0 in func_8008BED8 */

/* Selects a state handler when the global status is 0xFF or zero. */
void func_8008BED8(S_8008BED8_0 *state) {
    M2C_UNK *handler;
    u32 status = D_800FC418;

    if (status == 0xFF) {
        handler = &D_8008BA00;
    } else if (status == 0) {
        handler = &D_8008BC58;
    } else {
        return;
    }
    state->unk_68 = handler;
}
