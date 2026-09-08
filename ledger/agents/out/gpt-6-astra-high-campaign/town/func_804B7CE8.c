#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017D9C();             /* extern */
M2C_UNK func_80018854();                         /* extern */
M2C_UNK func_800188CC();                     /* extern */

typedef struct S_800164E8_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800164E8_0;   /* arg0 in func_800164E8 */

/* Process the object identifier and 0x50C before forwarding the object and value. */
void func_800164E8(S_800164E8_0 *object, M2C_UNK value) {
    func_80018854(object->unk_18);
    func_800188CC(0x50C);
    func_80017D9C(object, value);
}
