#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80051FBC();                         /* extern */

typedef struct S_80020D0C_0 {
    u8 pad_00[0xFC];
    s32 * unk_FC;
} S_80020D0C_0;   /* arg0 in func_80020D0C */

/* Pass the object's referenced value to func_80051FBC. */
void func_80020D0C(S_80020D0C_0 *object) {
    func_80051FBC(*object->unk_FC);
}
