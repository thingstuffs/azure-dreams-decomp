#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800CA308;

typedef struct S_800CA774_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x14];
    s16 unk_6C;
} S_800CA774_0;   /* arg0 in func_800CA774 */

void func_800CA774(S_800CA774_0 *arg0) {
    arg0->unk_54 = &D_800CA308;
    arg0->unk_6C = 0xA;
}
