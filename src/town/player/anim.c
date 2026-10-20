#include "common.h"
#include "m2c_compat.h"

typedef struct S_80097D2C_0 {
    u8 pad_00[0x4];
    s32 (*unk_04)(struct S_80097D2C_0 *);
} S_80097D2C_0;   /* arg0 in func_80097D2C */


/* Invoke the object's callback. */
void func_80097D2C(S_80097D2C_0 *object) {
    object->unk_04(object);
}
