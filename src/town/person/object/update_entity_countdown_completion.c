#include "common.h"
#include "shared/town_object.h"

#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
void assign_object_data_pointers(TownObjectRecord *object);

/* Decrement the entity countdown and run its completion handlers when it expires. */
void update_entity_countdown_completion(TownObjectRecord *entity, ObjectPosition *position, SpriteFrameState *sprite) {
    u16 countdown;

    countdown = entity->timer - 1;
    entity->timer = countdown;
    if ((countdown << 0x10) <= 0) {
        assign_object_data_pointers(entity);
        create_and_invoke_render_object(entity, entity->variant);
        apply_object_setup_and_update(entity, position, sprite);
    }
}
