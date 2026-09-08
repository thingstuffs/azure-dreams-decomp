#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A7338_0 {
    u8 pad_00[0x50];
    M2C_UNK (*unk_50)();
} S_800A7338_0;   /* arg0 in func_800A7338 */


/* Invoke the object's callback. */
void func_800A7338(S_800A7338_0 *object) {
    object->unk_50();
}
