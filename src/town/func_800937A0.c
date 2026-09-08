#include "common.h"
#include "m2c_compat.h"

/* extern */
M2C_UNK func_80093D48();    /* extern */

typedef struct S_80090F00_0 {
    s32 unk_00;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80090F00_0;   /* arg0 in func_80090F00 */


M2C_UNK func_80090A74(S_80090F00_0 *, M2C_UNK, M2C_UNK);
/* Updates the object and decrements its countdown if its state is unchanged. */
void func_80090F00(S_80090F00_0 *object, M2C_UNK context, M2C_UNK data) {
    s32 previous_state;
    u16 countdown;

    previous_state = object->unk_00;
    func_80090A74(object, context, data);
    if (previous_state == object->unk_00) {
        countdown = object->unk_0A - 1;
        object->unk_0A = countdown;
        if ((countdown << 0x10) <= 0) {
            func_80093D48(object, context, data);
        }
    }
}
