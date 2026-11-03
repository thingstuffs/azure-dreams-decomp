#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "town/person/motion.h"
#include "town/player.h"

   /* ((TownObjectRecord *)arg0)->unk_80 in advance_motion_and_switch_handler */

#include "town/person/object/initialize_object_entries_api.h"        /* extern */
#include "town/person/object.h"

/* Advances motion and changes the object handler when the motion step is nonnegative. */
void advance_motion_and_switch_handler(TownObjectRecord *object, EntityRec *motion, SpriteFrameState *context) {
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    add_hex_20000_s_signed_offset_hex_14(motion);
    if (motion->flags14 >= 0) {
        initialize_object_entries((object), context, object->descriptor->entries[8]);
        object->handler = &advance_and_clamp_entity_value;
    }
}
