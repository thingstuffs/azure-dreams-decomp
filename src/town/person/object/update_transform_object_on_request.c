#include "common.h"
#include "shared/object_flags.h"
#include "engine/script.h"
#include "town/person/object.h"
#include "town/person/current_transform_object_data.h"
#include "town/scene/object.h"
#include "town/player.h"

typedef struct {
    void *value;
    void *pad[2];
} PointerGlobal;

extern PointerGlobal scene_object_payload_alias;

/* Update the current object and set its and the global flags when the request succeeds. */
void update_transform_object_on_request(void *object, s32 request_data, s32 request_param, s32 check_param) {
    void *current_object;

    if (service_script_controller() != 0) {
        current_object = current_transform_object;
        if (current_object == object && scene_object_payload_alias.value == invoke_object_state_callback) {
            unlink_scene_list_node(current_object);
            ((u16 *) current_object)[-1] |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
