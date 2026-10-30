#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "town/event/state.h"
#include "engine/node.h"
#include "town/menu/object.h"

struct IntVector3;        /* extern */
extern void D_800A7C0C(void *object, s32 check_value);

typedef struct S_800A7B98_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800A7B98_2;   /* arg2 in create_timed_effect_object */

/* Creates an object, copies its source data fields, and initializes its state. */
void create_timed_effect_object(s32 ownerDataAddress, s32 creationParam, S_800A7B98_2 *sourceData) {
    BoundsExpiryObject *objectState;
    ObjectNodeHeader *createdObject;
    SpriteFrameState *objectData;

    createdObject = create_town_effect_object(ownerDataAddress - 0x20, (struct IntVector3 *)(creationParam), (s32)(&D_800A7C0C), 0);
    objectState = ((void *)createdObject) + 0x20;
    if (createdObject != NULL) {
        objectData = createdObject->sprite;
        objectData->source = sourceData->unk_08;
        objectData->flags = (u16) sourceData->unk_14;
        register_node_if_unregistered(objectState, project_sprite_chain);
        objectState->timer = 5;
    }
}
