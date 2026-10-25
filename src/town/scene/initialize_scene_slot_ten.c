#include "town/scene/object.h"
#include "common.h"
#include "shared/sprite_frame_state.h"

extern void initialize_object_and_register_slot(void *, s32, void *, void *, void *, void *);
extern u8 D_800D6360[];
extern u8 D_800D6364[];
extern u8 D_800D6330[];
extern u8 D_800D6338[];

void initialize_scene_slot_ten(void *object, void *position, SpriteFrameState *sprite) {
    initialize_object_and_register_slot(object, 10, D_800D6360, D_800D6364, D_800D6330, D_800D6338);
}
