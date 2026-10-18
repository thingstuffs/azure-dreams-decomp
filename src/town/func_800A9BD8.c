#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A7338_0 {
    u8 pad_00[0x50];
    s32 (*unk_50)(struct S_800A7338_0 *);
} S_800A7338_0;   /* arg0 in invoke_emote_object_callback */


/* Invoke the object's callback. */
void invoke_emote_object_callback(S_800A7338_0 *object) {
    object->unk_50(object);
}
