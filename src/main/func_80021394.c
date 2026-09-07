#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_80021394_0 {
    s32 unk_00;
    u8 pad_04[0x10];
    s32 unk_14;
} S_80021394_0;   /* arg0 in func_80021394 */

void func_80021394(S_80021394_0 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_14 = arg1;
    arg0->unk_00 = arg2;
}
