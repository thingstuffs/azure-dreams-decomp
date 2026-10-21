#include "common.h"

#include "common.h"
#include "engine/window.h"

typedef struct S_800355EC_0 {
    u8 pad_00[0x68];
    s32 (*unk_68)();
} S_800355EC_0;   /* arg0 in invoke_window_object_callback */


/* Invokes the object's callback. */
void invoke_window_object_callback(S_800355EC_0 *object) {
    object->unk_68();
}
