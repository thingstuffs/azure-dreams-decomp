#include "shared/object_node.h"
#include "town/minigame.h"
#include "common.h"
#include "m2c_compat.h"


/* Allocate a type 2 object and initialize its data pointer and value. */
void create_timed_sound(s16 value) {
    TimedSoundNode *object;

    object = allocate_flagged_object_node(2);
    if (object != NULL) {
        object->header.update_callback = tick_timed_sound;
        object->body.timer = value;
    }
}
