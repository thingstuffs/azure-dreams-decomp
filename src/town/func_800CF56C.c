#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CCCCC_0 {
    u8 pad_00[0x68];
    u16 unk_68;
} S_800CCCCC_0;   /* arg0 in func_800CCCCC */

/* Increment the object's 16-bit counter at offset 0x68. */
void func_800CCCCC(S_800CCCCC_0 *object) {
    object->unk_68 = (u16) (object->unk_68 + 1);
}
