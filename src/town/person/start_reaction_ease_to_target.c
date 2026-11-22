#include "common.h"
#include "m2c_compat.h"
#include "town/person.h"
#include "town/person/position.h"

/* Initializes the object's data pointer and sets its initial value to 10. */
void start_reaction_ease_to_target(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *unused_sprite, struct GameWork *unused_game) {
    object->handler = &ease_reaction_position_to_target;
    object->timer = 0xA;
}
