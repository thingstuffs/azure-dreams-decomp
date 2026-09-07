#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_8008BA00;
extern M2C_UNK D_8008BC58;
extern u8 D_800FC418;
extern void func_8008BF00(void) __attribute__((noreturn));

typedef struct S_8008BED8_0 {
    u8 pad_00[0x68];
    M2C_UNK * unk_68;
} S_8008BED8_0;   /* arg0 in func_8008BED8 */

void func_8008BED8(S_8008BED8_0 *arg0) {
    M2C_UNK *var_v0;
    u32 temp_v1 = D_800FC418;
    ASM_KEEP(temp_v1);   /* MATCH pin: load-bearing for the whole function shape */

    if (temp_v1 == 0xFF) {
        var_v0 = &D_8008BA00;
        ASM_TAILSLOT_PIN(var_v0);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8008BF00();
    }
    if (temp_v1 == 0) {
        var_v0 = &D_8008BC58;
        arg0->unk_68 = var_v0;
    }
}
