#include "common.h"
#include "town/player/action_initializers.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/town_handler.h"
#include "town/player/object.h"
#include "town/player.h"

#include "town/player/object/entity_record_fields.h"                      /* extern */

/* Initialize the object and its transform with fixed placement and settings. */
void initialize_object_transform_and_handler(TownObjectRecord *object, ObjectPosition *transform, void *ptr2) {
    call_the_handler_selects_nonzero_entry(D_800D0170, object, ptr2);
    object->unk_04 = &update_actor_and_select_ground_handler;
    clear_entity_record_fields(transform);
    transform->velocity_x = 0xFFFE0000;
    transform->velocity_y = 0x40000;
    transform->velocity_z = 0xFFF90000;
    object->unk_10 = 0xE00;
}
