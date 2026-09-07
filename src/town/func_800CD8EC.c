#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CB04C_0 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800CB04C_0;   /* arg0 in func_800CB04C */

typedef struct S_800CB04C_1 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800CB04C_1;   /* ((S_800CB04C_0 *)arg0)->unk_80 in func_800CB04C */




/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D6924;


void func_800CB04C(S_800CB04C_0 *arg0) {
    ((S_800CB04C_1 *)(arg0->unk_80))->unk_04 = &D_800D6924;
}
