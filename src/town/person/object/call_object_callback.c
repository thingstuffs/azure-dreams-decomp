#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C3960_0 {
    u8 pad_00[0x54];
    s32 (*unk_54)(struct S_800C3960_0 *, void *, void *);
} S_800C3960_0;   /* arg0 in call_object_callback */


/* Calls the object's callback. */
void call_object_callback(S_800C3960_0 *object, void *context, void *motion) {
    object->unk_54(object, context, motion);
}
