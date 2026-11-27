#include "engine/message/data.h"
#include "engine/message.h"
#include "shared/object_node.h"
#include "shared/town_object.h"
#include "shared/object_index_slots.h"
#include "town/person.h"

/* anyone_org_ang_get: store the actor's converted original angle in the script variables. */
void anyone_org_ang_get(s32 actor_id, void *script_context) {
    ScriptController *controller = &runtime_script_state;
    ObjectNodeHeader *node;

    if (actor_id != 0) {
        node = object_index_slots[actor_id].object;
        if (node != 0) {
            TownObjectRecord *body = NODE_BODY(node);
            controller->variables[0] = map_angle_to_cardinal_direction(body->origin_heading);
        }
    }
}
