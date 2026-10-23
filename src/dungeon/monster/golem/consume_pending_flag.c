#include "dungeon/monster/golem.h"


/* Requires and clears the object flag at 0xAE, then clears record bit 30. */
s32 consume_pending_flag(GolemActionWork *object, u32 *flag_record) {
    if (object->mode) {
        object->mode = 0;
        flag_record[5] &= 0xBFFFFFFF;
        return 1;
    }
    return 0;
}
