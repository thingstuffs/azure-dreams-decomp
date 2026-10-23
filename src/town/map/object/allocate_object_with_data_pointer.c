#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"

extern void D_800B90B4();

typedef struct S_800B90BC_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800B90BC_0;

/* Allocate an object and set its data pointer. */
void allocate_object_with_data_pointer(void) {
    S_800B90BC_0 *object;

    object = allocate_flagged_object_node(0);
    if (object != NULL) {
        object->unk_10 = &D_800B90B4;
    }
}
