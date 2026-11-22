#include "town/scene/object.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person/object.h"
#include "town/scene.h"

extern s32 D_800D55D0[];
extern TownIndexedHandler D_800D55D4[];
extern s32 D_800D55A0[];
extern PersonDescriptor D_800D55A8;

void initialize_scene_slot_thirteen(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    register_object_slot_with_tables(object, 13, D_800D55D0, D_800D55D4, D_800D55A0, &D_800D55A8);
}
