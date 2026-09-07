#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80019B54();             /* extern */
M2C_UNK func_8001ACE8();                         /* extern */
s32 func_8001ADE0();                         /* extern */

typedef struct S_8001762C_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_8001762C_0;   /* arg0 in func_8001762C */

/* Applies the object's stored value when either condition is active, then forwards the call. */
void func_8001762C(S_8001762C_0 *object, M2C_UNK context) {
    if ((func_8001ADE0(0x1388) != 0) || (func_8001ADE0(0x138A) != 0)) {
        func_8001ACE8(object->unk_18);
    }
    func_80019B54(object, context);
}
