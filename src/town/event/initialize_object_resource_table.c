#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/event/object_setup.h"


extern s32 town_object_resource_table[];
extern s32 D_800D06F8[];
extern s32 D_800F8BCC[];
extern s32 D_800F8BD8[];

/* Assign the object data table and initialize it with the shared tables. */
void initialize_object_resource_table(void *object, void *context, SpriteFrameState *state) {
    *(void **)((u8 *)object + 0x7C) = D_800D06F8;
    select_object_state_by_mode(object, context, state, D_800F8BCC, D_800F8BD8, town_object_resource_table);
}
