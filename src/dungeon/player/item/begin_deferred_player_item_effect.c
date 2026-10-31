#include "common.h"
#include "dungeon/player/item.h"
#include "shared/entity.h"


/* Sets object state bytes from the mode and clears its state word. */
void begin_deferred_player_item_effect(void *object_in, unsigned long unused_1, void *unused_2, ActorRecord *actor) {
    ActorRecord *object = object_in;
    object->action_id.s = 0x2B;
    if (actor == 0) {
        object->action_phase.s = 0x10;
    } else {
        object->action_phase.s = 0;
    }
    object->unk_8C.word = 0;
    return;
}
