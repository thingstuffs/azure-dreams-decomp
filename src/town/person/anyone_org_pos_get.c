#include "engine/message/data.h"
#include "engine/message.h"
#include "shared/object_node.h"
#include "shared/town_object.h"
#include "shared/object_index_slots.h"
#include "town/person.h"

/* anyone_org_pos_get: copy the actor's original position to script variables. */
void anyone_org_pos_get(s32 actor_id) {
    ScriptController *controller = &runtime_script_state;
    ObjectNodeHeader *node;
    TownObjectRecord *body;

    if (actor_id != 0) {
        node = object_index_slots[actor_id].object;
        if (node != 0) {
            body = NODE_BODY(node);
            controller->variables[1] = body->origin_x;
            controller->variables[2] = body->origin_y;
        }
    }
}
