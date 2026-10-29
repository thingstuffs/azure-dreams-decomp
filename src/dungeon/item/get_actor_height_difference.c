#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "dungeon/item.h"

/* Returns the signed difference between the records' 16-bit values at offset 0x88. */
s16 get_actor_height_difference(ActorRecord *left_record, ActorRecord *right_record) {
    return (s16) (((u16)left_record->ground_height) - ((u16)right_record->ground_height));
}
