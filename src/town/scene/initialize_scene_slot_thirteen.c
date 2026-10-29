#include "town/scene/object.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person/object.h"
#include "town/scene.h"

extern u8 D_800D55D0[];
extern u8 D_800D55D4[];
extern u8 D_800D55A0[];
extern u8 D_800D55A8[];

void initialize_scene_slot_thirteen(void *object, void *position, SpriteFrameState *sprite) {
    initialize_object_and_register_slot(object, 13, D_800D55D0, D_800D55D4, D_800D55A0, D_800D55A8);
}
