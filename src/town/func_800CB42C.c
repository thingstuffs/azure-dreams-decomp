#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C8B8C_0 {
    u8 pad_00[0x50];
    M2C_UNK (*unk_50)();
} S_800C8B8C_0;   /* arg0 in func_800C8B8C */


/* Invokes the owner's callback. */
void func_800C8B8C(S_800C8B8C_0 *owner) {
    owner->unk_50();
}
