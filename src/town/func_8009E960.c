#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_8009B6B4;

typedef struct S_8009C0C0_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_8009C0C0_0;   /* arg1 in func_8009C0C0 */

typedef struct S_8009C0C0_1 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_8009C0C0_1;   /* arg0 in func_8009C0C0 */

void func_8009C0C0(S_8009C0C0_1 *arg0, S_8009C0C0_0 *arg1) {
    arg1->unk_15 = 1;
    arg0->unk_50 = &D_8009B6B4;
}
