#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "town/person.h"

extern s32 D_800C53F8;


/* Clear the actor table flag, install its handler, and set its counter to 10. */
void install_actor_handler_with_counter_10(TownObjectRecord *actor) {
    object_index_slots[actor->slot].unk_00 = 0;
    actor->handler = &D_800C53F8;
    actor->timer = 0xA;
}
