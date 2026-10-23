#include "common.h"

#include "common.h"
#include "engine/window.h"

typedef struct S_800355EC_0 {
    u8 pad_00[0x68];
    s32 (*unk_68)(struct S_800355EC_0 *, void *, void *);
} S_800355EC_0;   /* arg0 in invoke_window_object_callback */


/* Invokes the object's callback. */
void invoke_window_object_callback(S_800355EC_0 *object, void *context, void *output) {
    object->unk_68(object, context, output);
}
