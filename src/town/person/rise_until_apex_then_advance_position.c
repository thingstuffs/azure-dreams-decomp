#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/town_object.h"
#include "town/person.h"
#include "town/player.h"

#include "town/person/object/initialize_object_entries_api.h"  /* extern */
#include "town/person/object_setup.h"
extern s32 D_800D6290[];


/*
 * Rises by the vertical velocity at +0x14 and adds 0x20000 to it each step; at the apex (velocity no
 * longer negative) selects the D_800D6290 entries and installs advance_object_position.
 */
void rise_until_apex_then_advance_position(TownObjectRecord *object, EntityRec *motion, void *context) {
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    add_vertical_gravity(motion);
    if (motion->flags14 >= 0) {
        initialize_object_entries((object), context, D_800D6290);
        object->handler = &advance_object_position;
    }
}
