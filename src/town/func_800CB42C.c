#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C8B8C_0 {
    u8 pad_00[0x50];
    s32 (*unk_50)(struct S_800C8B8C_0 *);
} S_800C8B8C_0;   /* arg0 in func_800C8B8C */


/* Invokes the owner's callback. */
void func_800C8B8C(S_800C8B8C_0 *owner) {
    owner->unk_50(owner);
}
