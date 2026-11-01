#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person/object.h"
#include "town/person.h"

extern void *D_800C25C0;
extern s32 D_800D4FA0[];

/* Initialize the object's handler and values from its configuration bytes. */
void initialize_transform_object(TownObjectRecord *object, void *unused_position, struct SpriteFrameState *unused_sprite) {
    *(void **)((u8 *)object - 0x10) = &D_800C25C0;
    object->slot = object->variant.as_u8;
    object->unk_50.as_s32 = D_800D4FA0[*((u8 *)object + 0x94)];
}
