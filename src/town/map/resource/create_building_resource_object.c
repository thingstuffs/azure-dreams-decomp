#include "shared/object_node.h"
#include "common.h"

extern s32 D_800B7B8C;

typedef struct S_800B8170_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
    s16 unk_22;
} S_800B8170_0;

/* Allocate an object, set its data pointer, and clear its two halfword fields. */
void create_building_resource_object(void) {
    S_800B8170_0 *object;

    object = allocate_flagged_object_node(0);
    if (object != 0) {
        object->unk_10 = &D_800B7B8C;
        object->unk_20 = 0;
        object->unk_22 = 0;
    }
}
