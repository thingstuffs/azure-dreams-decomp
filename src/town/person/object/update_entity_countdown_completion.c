#include "common.h"
#include "shared/town_object.h"

#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
void assign_object_data_pointers(TownObjectRecord *object);

/* Decrement the entity countdown and run its completion handlers when it expires. */
void update_entity_countdown_completion(TownObjectRecord *entity, void *update_context, void *setup_context) {
    u16 countdown;

    countdown = entity->timer - 1;
    entity->timer = countdown;
    if ((countdown << 0x10) <= 0) {
        assign_object_data_pointers(entity);
        create_and_invoke_render_object((s32)(entity), entity->variant);
        apply_object_setup_and_update(entity, update_context, setup_context);
    }
}
