#include "shared/object_node.h"
#include "common.h"
void no_op_entry_callback(void);

typedef struct S_800B93FC_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800B93FC_0;

/* Allocate an object and set its data pointer. */
void allocate_third_object_variant(void) {
    S_800B93FC_0 *object;

    object = func_8003FC64(0);
    if (object != 0) {
        object->unk_10 = &no_op_entry_callback;
    }
}
