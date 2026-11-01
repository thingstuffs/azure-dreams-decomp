#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person/object.h"
#include "town/person/state.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s8 D_800826B8;
extern s32 D_800D6540[];


/* Initialize the object, clear the shared flag, and set its callback. */
void initialize_reaction_object_and_clear_flag(TownObjectRecord *object, s32 unused, void *context) {
    initialize_object_entries((Struct800C5724 *)(object), context, D_800D6540);
    D_800826B8 = 0;
    object->handler = &forward_reaction_object;
}
