#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025524_0 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_80025524_0;   /* arg0 in func_80025524 */

/* Returns the object's value at offset 0x40. */
s32 func_80025524(S_80025524_0 *object) {
    return object->unk_40;
}
