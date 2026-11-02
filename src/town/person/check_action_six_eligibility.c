#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/town_object.h"
#include "town/person.h"
#include "town/player.h"

#include "town/person/object/initialize_object_entries_api.h"  /* extern */
#include "town/person/object_setup.h"
extern s32 D_800D6290[];


/* Advance the motion state and update the object when its step is nonnegative. */
void check_action_six_eligibility(TownObjectRecord *object, EntityRec *motion, void *context) {
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    add_hex_20000_s_signed_offset_hex_14(motion);
    if (motion->flags14 >= 0) {
        initialize_object_entries((object), context, D_800D6290);
        object->handler = &advance_object_position;
    }
}
