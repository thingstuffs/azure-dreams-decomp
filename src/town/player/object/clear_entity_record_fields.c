#include "town/player/object/entity_record_fields.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/player/object.h"


/* Clears the record's three fields at offsets 0x0C through 0x14. */
void clear_entity_record_fields(ObjectPosition *record) {
    record->velocity_x = 0;
    record->velocity_y = 0;
    record->velocity_z = 0;
}
