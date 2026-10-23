#include "common.h"

extern s32 service_script_controller(void);
extern void unlink_scene_list_node(void *node);
extern struct { s32 v; s32 pad[2]; } object_flag_block;

/* On a zero result, process the object and set its flag and the global flag. */
void process_transform_object_on_zero(void *object, s32 value, s32 options, s32 mode) {
    if (service_script_controller() == 0) {
        unlink_scene_list_node(object);
        *((u16 *)object - 1) |= 0x8000;
        object_flag_block.v |= 0x8000;
    }
}
