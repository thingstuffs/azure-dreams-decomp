#include "common.h"

typedef struct S_800CBAAC_0 {
    u8 pad_00[0x50];
    void (*unk_50)(void *, void *, s32, s32);
} S_800CBAAC_0;   /* arg0 in invoke_object_handler */


/* Invoke the object handler with the object and forwarded arguments. */
void invoke_object_handler(S_800CBAAC_0 *object, s32 callback_arg1, s32 callback_arg2) {
    object->unk_50(object, object, callback_arg1, callback_arg2);
}
