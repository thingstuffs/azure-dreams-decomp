#include "common.h"
#include "shared/object_flags.h"
#include "engine/script.h"
#include "town/person/object.h"
#include "town/scene/object.h"

/* Process the object and set its header and global flags when both checks pass. */
void process_checked_transform_object(void *object, s32 check_value_1, s32 check_value_2, s32 check_value_3) {
    if ((service_script_controller() != 0) && (check_active_transform_object(object) != 0)) {
        unlink_scene_list_node(object);
        *(u16 *)((u8 *)object - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
