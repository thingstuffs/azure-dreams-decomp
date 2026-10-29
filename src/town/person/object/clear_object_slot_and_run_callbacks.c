#include "common.h"
#include "shared/object_index_slots.h"
#include "records/Rec_D_80082D58.h"
#include "engine/node.h"
#include "town/person/object.h"
#include "town/scene/object.h"

#include "town/scene/object/unlink_scene_list_node_api.h"                      /* extern */
#include "town/person/object_setup.h"


/* Clear the indexed table flag and run the object callbacks in sequence. */
void clear_object_slot_and_run_callbacks(Rec_D_80082D58 *object, void *callback_arg_1, void *callback_arg_2) {
    object_index_slots[object->unk_60].unk_00 = 0;
    apply_object_setup_and_update(object, callback_arg_1, callback_arg_2);
    unlink_scene_list_node((struct Rec_func_80094268_arg0 *)(object));
    unlink_node_if_registered(object);
    clear_object_slot_and_mark_removed(object);
}
