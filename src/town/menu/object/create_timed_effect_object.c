#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

void register_node_if_unregistered(void *block_data, void *registration_id);
struct IntVector3; void * create_town_effect_object(s32, struct IntVector3 *, s32, s32);       /* extern */
extern void D_800A7C0C();

typedef struct S_800A7B98_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800A7B98_2;   /* arg2 in create_timed_effect_object */

typedef struct S_800A7B98_3 {
    u8 pad_00[0x6C];
    s16 unk_6C;
} S_800A7B98_3;

/* Creates an object, copies its source data fields, and initializes its state. */
void create_timed_effect_object(s32 ownerDataAddress, s32 creationParam, S_800A7B98_2 *sourceData) {
    S_800A7B98_3 *objectState;
    ObjectNodeHeader *createdObject;
    SpriteFrameState *objectData;

    createdObject = create_town_effect_object(ownerDataAddress - 0x20, (struct IntVector3 *)(creationParam), (s32)(&D_800A7C0C), 0);
    objectState = ((void *)createdObject) + 0x20;
    if (createdObject != NULL) {
        objectData = createdObject->sprite;
        objectData->source = sourceData->unk_08;
        objectData->flags = (u16) sourceData->unk_14;
        register_node_if_unregistered(objectState, project_sprite_chain);
        objectState->unk_6C = 5;
    }
}
