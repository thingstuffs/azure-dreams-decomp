#include "common.h"

extern void call_indexed_handler_and_clear(s32 *record);

typedef struct S_80025598_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x18];
    s32 unk_2C;
} S_80025598_0;   /* arg0 in reset_object_to_default_data */

/* Clear the object's state and set its default data pointer. */
void reset_object_to_default_data(S_80025598_0 *object) {
    object->unk_2C = 0;
    object->unk_10 = &call_indexed_handler_and_clear;
}
