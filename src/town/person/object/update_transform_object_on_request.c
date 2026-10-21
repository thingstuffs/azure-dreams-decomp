#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    void *value;
    void *pad[2];
} PointerGlobal;

extern s32 service_script_controller(void);
extern void unlink_scene_list_node(void *node);

extern PointerGlobal D_800FE4A0;
extern PointerGlobal scene_object_payload_alias;
extern u8 D_80097D2C[12];

/* Update the current object and set its and the global flags when the request succeeds. */
void update_transform_object_on_request(void *object, s32 request_data, s32 request_param, s32 check_param) {
    void *current_object;

    if (service_script_controller() != 0) {
        current_object = D_800FE4A0.value;
        if (current_object == object && scene_object_payload_alias.value == D_80097D2C) {
            unlink_scene_list_node(current_object);
            ((u16 *) current_object)[-1] |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}
