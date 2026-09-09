#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_80098078_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80098078_0;   /* arg0 in func_80098078 */


M2C_UNK func_80098988(S_80098078_0 *, s32);
void func_80098078(S_80098078_0 *arg0, s32 arg1) {
    u16 temp_v0;

    temp_v0 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_80098988(arg0, arg1);
    }
}
