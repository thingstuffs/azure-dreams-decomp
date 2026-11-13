#include "shared/object_node.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 scene_object_payload_alias;
extern void dispatch_selected_entry_if_nonzero(s32 *a0, void *a1,void *a2);

/* Calls dispatch_selected_entry_if_nonzero with the input value and global context. */
void apply_global_scene_value(void *value) {
    s32 *context = &scene_object_payload_alias;
    dispatch_selected_entry_if_nonzero(value, context, NODE_HEADER(context)->sprite);
}
