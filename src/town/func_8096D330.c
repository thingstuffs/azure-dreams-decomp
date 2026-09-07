#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_801257C8_0 {
    u8 pad_00[0xA];
    s8 unk_0A;
} S_801257C8_0;   /* arg0 in func_801257C8 */

void func_801257C8(S_801257C8_0 *arg0) {
    func_80124188();
    arg0->unk_0A = 1;
}
