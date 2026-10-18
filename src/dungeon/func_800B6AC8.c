#include "shared/object_node.h"
#include "common.h"
extern void update_wrapped_texture_scroll(void *scrollState);

typedef struct S_800BC228_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x18];
    s16 unk_2C;
} S_800BC228_0;

/* Create an object with update_wrapped_texture_scroll as its data pointer and store the supplied value. */
void create_wrapped_texture_scroll(s16 value) {
    S_800BC228_0 *object;

    object = func_8003FC64(0);
    if (object != 0) {
        object->unk_10 = update_wrapped_texture_scroll;
        object->unk_2C = value;
    }
}
