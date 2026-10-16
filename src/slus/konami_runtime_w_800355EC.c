#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800355EC_0 {
    u8 pad_00[0x68];
    M2C_UNK (*unk_68)();
} S_800355EC_0;   /* arg0 in invokeWindowObjectCallback */


/* Invokes the object's callback. */
void invokeWindowObjectCallback(S_800355EC_0 *object) {
    object->unk_68();
}
