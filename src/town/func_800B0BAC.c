#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800AE2A4;

typedef struct S_800AE30C_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800AE30C_0;   /* arg0 in func_800AE30C */

/* Set the object's data pointer if the object is non-null. */
void func_800AE30C(S_800AE30C_0 *object) {
    if (object != NULL) {
        object->unk_10 = &D_800AE2A4;
    }
}
