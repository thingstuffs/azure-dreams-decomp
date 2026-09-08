#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003AF8C_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8003AF8C_0;   /* arg0 in func_8003AF8C */


/* Clears the object's field at offset 0x14. */
void func_8003AF8C(S_8003AF8C_0 *object) {
    object->unk_14 = 0;
}
