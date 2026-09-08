#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E994();                         /* extern */

typedef struct S_8002742C_0 {
    u8 pad_00[0xFC];
    s32 * unk_FC;
} S_8002742C_0;   /* arg0 in func_8002742C */

/* Pass the object's referenced value to func_8004E994. */
void func_8002742C(S_8002742C_0 *object) {
    func_8004E994(*object->unk_FC);
}
