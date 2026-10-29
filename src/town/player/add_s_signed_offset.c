#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/player.h"


/* Add 0x20000 to the record's signed value at offset 0x14. */
void add_hex_20000_s_signed_offset_hex_14(EntityRec *record) {
    record->flags14 = (s32) (record->flags14 + 0x20000);
}
