#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "town/menu/object.h"
#include "town/menu/state.h"
#include "engine/node.h"

/* Creates a display object with callbacks and the supplied payload values. */
ObjectNodeHeader *create_shaded_primitive_object(struct DoorTransitionEffect *parent, s32 index, struct ObjectPosition *unused_origin)
{
    ObjectNodeHeader *object;
    SpriteFrameState *display;
    DoorProjectionChild *payload;

    object = allocate_list_node(0x136, &scene_object_list_anchor.next);
    if (object == 0) {
        return 0;
    }

    object->update_callback = render_shaded_object_primitive;
    display = object->sprite;
    payload = NODE_BODY(object);
    payload->update = initialize_indexed_render_state;
    payload->parent = parent;
    payload->index = index;

    display->scale_y = 0xAAA;
    display->scale_x = 0xAAA;
    display->depth_bias = 9;
    return object;
}
