#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024FFC_0 {
    u8 * unk_00;
} S_80024FFC_0;   /* arg0 in func_80024FFC; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_8002593C[];
void func_80024FFC(void *arg0) {
    func_80025030();
    ((S_80024FFC_0 *)((u8 *)arg0 - 0x10))->unk_00 = D_8002593C;
}
