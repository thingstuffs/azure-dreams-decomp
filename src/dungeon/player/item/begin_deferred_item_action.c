#include "common.h"
#include "dungeon/player/item.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008D024_arg0.h"
#include "shared/entity.h"


/* Set the record's state to 0x21 and clear its associated fields. */
void begin_deferred_item_action(void *record_data, void *unused_position, void *unused_sprite, void *unused_actor) {
    Rec_func_8008D024_arg0 *record = record_data;

    record->unk_9A = 0x21;
    record->unk_9B.as_s8 = 0;
    record->unk_8C = 0;
}
