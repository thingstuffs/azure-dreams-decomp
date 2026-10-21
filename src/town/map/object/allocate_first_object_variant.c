#include "shared/object_node.h"
#include "common.h"
void update_wrapping_indices_and_input(void);

typedef struct S_800B9384_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800B9384_0;

/* Allocate an object and set its data pointer. */
void allocate_first_object_variant(void) {
    S_800B9384_0 *object;

    object = allocate_flagged_object_node(0);
    if (object != 0) {
        object->unk_10 = &update_wrapping_indices_and_input;
    }
}
