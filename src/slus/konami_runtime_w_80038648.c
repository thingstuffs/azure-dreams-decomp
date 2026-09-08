#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80038648_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x70];
    s8 unk_84;
} S_80038648_0;   /* arg0 in func_80038648 */


M2C_UNK func_80053DA8();                     /* extern */
extern M2C_UNK func_80038A10;

/* When the object's flag is set, call func_80053DA8 and set its handler to func_80038A10. */
void func_80038648(S_80038648_0 *object) {
    if (object->unk_84 != 0) {
        func_80053DA8(0xB4);
        object->unk_10 = &func_80038A10;
    }
}
