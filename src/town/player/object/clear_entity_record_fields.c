#include "town/player/object/entity_record_fields.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/player/object.h"


/* Clears the record's three fields at offsets 0x0C through 0x14. */
void clear_entity_record_fields(EntityRec *record) {
    record->unk_0C = 0;
    record->unk_10 = 0;
    record->flags14 = 0;
}
