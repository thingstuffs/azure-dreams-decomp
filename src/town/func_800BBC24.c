#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void *func_8003FC64();                       /* extern */
extern M2C_UNK D_800B9260;

typedef struct S_800B9384_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800B9384_0;   /* temp_v0 in func_800B9384 */

void func_800B9384(void) {
    S_800B9384_0 *temp_v0;

    temp_v0 = func_8003FC64(0);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_800B9260;
    }
}
