#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009C46C_0 {
    u8 pad_00[0x50];
    M2C_UNK (*unk_50)();
} S_8009C46C_0;   /* arg0 in func_8009C46C */


/* cfail-repair: tf7-phase1-cache-v3 */
void func_8009C46C(S_8009C46C_0 *arg0) {
    arg0->unk_50();
}
