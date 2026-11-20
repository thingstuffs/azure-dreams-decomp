#include "engine/message/data.h"
#include "engine/message.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/object_index_slots.h"
#include "town/person.h"

/* anyone_now_pos_get: store the actor's current position in the script variables. */
void anyone_now_pos_get(s32 actor_id) {
    ScriptController *controller = &runtime_script_state;
    ObjectNodeHeader *actor;
    ObjectPosition *position;

    if (actor_id != 0) {
        actor = object_index_slots[actor_id].object;
        if (actor != 0) {
            position = actor->position;
            controller->variables[1] = position->x.w.i;
            controller->variables[2] = position->y.w.i;
            controller->variables[3] = position->z.w.i;
        }
    }
}
