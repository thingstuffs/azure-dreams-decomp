#include "town/map/object_callback.h"
#include "town/map.h"

/* Invoke the object's callback with the node's position and sprite records. */
void run_map_object_callback(TownMapBody *object, ObjectPosition *position, SpriteFrameState *sprite) {
    TownMapUpdate update = object->update;
    update(object, position, sprite);
}
