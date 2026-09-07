#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK()  (0)

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80129728[];
extern s32 D_801331A0;

void func_80123898(void) {
    u8 *base_v1;
    u8 *var_v1;
    s32 *temp_v0;
    s32 *var_a0;
    s32 var_a1;

    var_a1 = 0x10;
    var_a0 = &D_801331A0;
    base_v1 = D_80129728;
    var_v1 = base_v1 + 0x40;
    do {
        var_a1 += 1;
        *var_a0 = **(s32 **)var_v1;
        temp_v0 = *(s32 **)var_v1;
        var_v1 += 4;
        *temp_v0 = 0;
        var_a0 += 1;
    } while (var_a1 < 0x1C);
}
