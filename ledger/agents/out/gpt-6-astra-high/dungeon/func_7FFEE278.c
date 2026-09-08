#include "common.h"
#include "m2c_compat.h"


typedef struct S_8008B9D8_0 {
    u8 pad_00[0x68];
    M2C_UNK (*unk_68)();
} S_8008B9D8_0;   /* arg0 in func_8008B9D8 */

/* Invokes the object's callback. */
void func_8008B9D8(S_8008B9D8_0 *object) {
    object->unk_68();
}
