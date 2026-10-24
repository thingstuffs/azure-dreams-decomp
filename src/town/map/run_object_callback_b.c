#include "town/map/object_callback.h"

typedef struct S_8008B9D8_0 {
    u8 pad_00[0x68];
    s32 (*unk_68)(struct S_8008B9D8_0 *, void *, void *, void *);
} S_8008B9D8_0;   /* arg0 in func_8008B9D8 */


/* Invoke the object's callback. */
void run_map_object_callback(S_8008B9D8_0 *object, void *transform,
                             void *context, void *extra_ptr) {
    object->unk_68(object, transform, context, extra_ptr);
}
