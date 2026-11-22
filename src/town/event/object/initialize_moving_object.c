#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/scene/object.h"
#include "town/event/object.h"

struct Node;                       /* extern */
#include "town/scene/object/unlink_scene_list_node_api.h"                      /* extern */
#include "shared/town_state.h"
#include "town/event/motion.h"
struct Actor;
struct Motion;
struct Subject;




/* Set the object flag, assign the context handler, and run object setup. */
void initialize_moving_object(TownObjectRecord *context, TownObjectRecord *object) {
    object->unk_15 = 1;
    context->unk_50.as_pm = update_actor_with_controlled_motion;
    unlink_scene_list_node(object);
    append_scene_list_node((struct Node *)(object));
}
