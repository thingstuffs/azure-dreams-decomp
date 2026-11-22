#include "common.h"
#include "town/person/state.h"

extern TownIndexedHandler D_800D6FBC[];

/* Invoke the callback selected by the object state. */
void invoke_flag_state_callback(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    D_800D6FBC[(s16)object->unk_68](object, position, sprite);
}
