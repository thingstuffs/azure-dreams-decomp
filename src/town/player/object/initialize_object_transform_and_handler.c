#include "common.h"
#include "town/player/action_initializers.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/town_handler.h"
#include "town/player/object.h"

#include "town/player/object/entity_record_fields.h"                      /* extern */
extern void update_actor_and_select_ground_handler();


/* Initialize the object and its transform with fixed placement and settings. */
void initialize_object_transform_and_handler(TownObjectRecord *object, EntityRec *transform, void *ptr2) {
    call_the_handler_selects_nonzero_entry(D_800D0170, object, ptr2);
    object->unk_04.as_pm = &update_actor_and_select_ground_handler;
    clear_entity_record_fields(transform);
    transform->unk_0C = 0xFFFE0000;
    transform->unk_10 = 0x40000;
    transform->flags14 = 0xFFF90000;
    object->unk_10.as_s16 = 0xE00;
}
