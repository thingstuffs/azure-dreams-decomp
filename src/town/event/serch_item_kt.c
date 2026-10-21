#include "common.h"

extern void unlink_scene_list_node(void *);
extern void unlink_node_if_registered(void *object);
extern struct { s32 v; s32 pad[2]; } D_800814A0;

/* Update the object and set the high bit in its header and the global flags. */
void unlink_and_remove_scene_object(void *object) {
    unlink_scene_list_node(object);
    unlink_node_if_registered(object);
    *((u16 *)object - 1) |= 0x8000;
    {
        s32 global_flags = D_800814A0.v;
        D_800814A0.v = global_flags | 0x8000;
    }
}
