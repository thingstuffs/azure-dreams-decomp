#include "common.h"
#include "m2c_compat.h"
#include "town/person.h"

typedef struct S_800C8B8C_0 {
    u8 pad_00[0x50];
    s32 (*unk_50)(struct S_800C8B8C_0 *, void *, s32);
} S_800C8B8C_0;   /* arg0 in call_owner_callback */


/* Invokes the owner's callback. */
void call_owner_callback(S_800C8B8C_0 *owner, void *motion, s32 context) {
    owner->unk_50(owner, motion, context);
}
