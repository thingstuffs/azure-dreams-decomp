#include "town/scene/object.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person/object.h"
#include "town/scene.h"

extern u8 D_800D6B14[];
extern u8 D_800D6B18[];
extern u8 D_800D6AE4[];
extern u8 D_800D6AEC[];

void initialize_scene_slot_forty_sprite(void *object, void *position, SpriteFrameState *sprite) {
    initialize_object_and_register_slot(object, 40, D_800D6B14, D_800D6B18, D_800D6AE4, D_800D6AEC);
    sprite->clut = 2;
    sprite->flags &= ~0x100;
}
