#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "engine/node.h"
#include "town/menu.h"
#include "town/person/object.h"
#include "town/scene/object.h"

typedef void (*Callback)(TownObjectRecord *, ObjectPosition *, struct SpriteFrameState *);

/* Clears and flags the object when the check succeeds, or invokes its callback. */
void finalize_transform_object_or_callback(void *object, ObjectPosition *position, struct SpriteFrameState *sprite) {
    TownObjectRecord *body = object;
    Callback callback;
    s8 *status_byte;

    if (classify_object_against_bounds(object, position) != 0) {
        unlink_scene_list_node(object);
        status_byte = body->unk_98;
        if (status_byte != 0) {
            *status_byte = 0;
        }
        unlink_node_if_registered(object);
        NODE_HEADER(object)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    } else {
        callback = body->unk_50.as_pv;
        callback(body, position, sprite);
    }
}
