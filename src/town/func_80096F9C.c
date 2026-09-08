#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800930E4;

typedef struct S_800946FC_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
} S_800946FC_0;   /* arg0 in func_800946FC */

/* Initializes the object's data pointer and sets its initial value to 0x13. */
void func_800946FC(S_800946FC_0 *object) {
    object->unk_00 = &D_800930E4;
    object->unk_0A = 0x13;
}
