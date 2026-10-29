#include "common.h"
#include "dungeon/effect/object.h"
#include "shared/object_node.h"
#include "dungeon/effect.h"

#include "engine/node/allocation.h"                  /* extern */

typedef struct S_800B341C_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0xC];
    ObjectNodeHeader *unk_20;
} S_800B341C_0;

typedef struct S_800B341C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x86];
    s16 unk_8E;
} S_800B341C_1;

/* Allocates and initializes an object when the payload value is nonzero. */
void allocate_payload_object(ObjectNodeHeader *owner, s32 payloadValue, s16 payloadShortValue) {
    ObjectNodeHeader *allocatedObject;
    S_800B341C_1 *objectData;

    if (payloadValue != 0) {
        allocatedObject = allocate_list_node(0x210, &owner->next);
        if (allocatedObject != 0) {
            allocatedObject->update_callback = &update_oriented_offset_effect_position;
            objectData = ((void *)allocatedObject) + 0x20;
            ((S_800B341C_0 *)allocatedObject)->unk_20 = owner;
            objectData->unk_04 = payloadValue;
            objectData->unk_8E = payloadShortValue;
        }
    }
}
