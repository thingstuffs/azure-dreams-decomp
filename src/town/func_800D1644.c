#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s8 D_80082688;
typedef struct S_800CEDA4_0 {
    u8 pad_00[0x6E];
    s16 unk_6E;
} S_800CEDA4_0;   /* arg0 in func_800CEDA4 */

void func_800CEDA4(S_800CEDA4_0 *arg0) {
    D_80082688 = 0;
    arg0->unk_6E = 0x400;
}
