#include "dungeon/monster/golem.h"


/* Requires and clears the object flag at 0xAE, then clears record bit 30. */
s32 consume_pending_flag(GolemActionWork *object, ActorRecord *flag_record) {
    if (object->mode) {
        object->mode = 0;
        {
            u32 flags = flag_record->flags14;

            flag_record->flags14 = flags & 0xBFFFFFFF;
        }
        return 1;
    }
    return 0;
}
