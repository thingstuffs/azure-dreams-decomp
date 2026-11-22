#include "town/person/jump_motion.h"
#include "town/person/state.h"

extern TownIndexedHandler D_800D6B28[];

/* Invoke the town callback selected by the object state. */
void invoke_state_indexed_callback(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    TownIndexedHandler *callbacks = D_800D6B28;
    s32 state_index = (s16)object->unk_68;
    callbacks[state_index](object, position, sprite);
}
