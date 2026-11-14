#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/vector.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "slus.h"
struct Dst;
struct Elem;
#include "town/person.h"
#include "shared/sprite_source.h"
extern SpriteSourceEntry D_800EE344[];

   /* arg0 in create_bouncing_effect_object */


/* Allocate and initialize an object at an offset from the supplied position. */
void * create_bouncing_effect_object(ObjectPosition *source_pos) {
    ObjectPosition *position;
    OwnerCallbackObject *object_state;
    SpriteFrameState *render_state;
    ObjectNodeHeader *object;
    s32 offset_z;

    object = allocate_list_node(0x136, &scene_object_list_anchor.next);
    if (object == NULL) {
        return 0;
    }
    position = object->position;
    render_state = object->sprite;
    object_state = NODE_BODY(object);
    position->x.v = source_pos->x.v;
    position->y.v = source_pos->y.v;
    offset_z = source_pos->z.v + 0xFFDC0000;
    position->velocity_x = 0x100000;
    position->velocity_y = 0;
    position->z.v = offset_z;
    object->update_callback = &call_owner_callback;
    object_state->contacts_left.as_s16 = 2;
    set_bounce_velocity(object_state, position, render_state);
    render_state->scale_y = 0x1000;
    render_state->scale_x = 0x1000;
    render_state->color.word = 0x808080;
    select_record_entry_and_value(render_state, &D_800EE344, 0);
    register_node_if_unregistered(object_state, project_sprite_chain);
    return object;
}
