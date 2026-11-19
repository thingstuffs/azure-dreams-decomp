#include "common.h"
#include "engine/node/registration.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "records/Rec_D_80082D58.h"
#include "shared/object_links.h"
#include "shared/town_object.h"
#include "town/scene/object.h"
#include "town/event/object.h"
#include "town/menu.h"
#include "town/player/state.h"


s32 update_object_and_clear_status_fields();

   /* the 0x2 bytes before arg0 in dispatch_object_event_or_retire, addressed as arg0[-1] */


/* Dispatches an object event or cleans up the object when the event check succeeds. */
void dispatch_object_event_or_retire(void *object_arg, ObjectPosition *position, struct SpriteFrameState *sprite)
{
    TownObjectRecord *object = object_arg;
    ObjectPosition *saved_position = position;
    struct SpriteFrameState *saved_sprite = sprite;
    void (*update)(TownObjectRecord *, TownObjectRecord *, ObjectPosition *, struct SpriteFrameState *);
    s8 *status_ptr;

    if (classify_object_against_bounds(object_arg, position) != 0) {
        unlink_scene_list_node(object);
        status_ptr = object->unk_98;
        if (status_ptr != 0) {
            *status_ptr = 0;
        }
        unlink_node_if_registered(object);
        NODE_HEADER(object)->flags =
            (u16)(NODE_HEADER(object)->flags | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        return;
    }
    update = object->unk_50.as_pm;
    update(object, object, saved_position, saved_sprite);
    if (!(NODE_HEADER(object)->flags & 0x8000)) {
        set_state_bytes_from_flags(update_object_and_clear_status_fields(saved_position), object_arg);
    }
}
