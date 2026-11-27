#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/event/object_setup.h"
#include "town/event.h"
#include "town/data.h"

extern s32 D_800D06F8[];
extern s32 D_800F8BCC[];
extern s32 D_800F8BD8[];

/* Assign the object data table and initialize it with the shared tables. */
void initialize_object_resource_table(TownObjectRecord *object, ObjectPosition *context, SpriteFrameState *state) {
    object->animation_tables.as_pv = D_800D06F8;
    select_object_state_by_mode(object, context, state, D_800F8BCC, D_800F8BD8, &town_object_resource_table);
}
