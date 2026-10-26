#include "common.h"
#include "shared/object_node.h"
#include "engine/node/allocation.h"

#ifndef NULL
#define NULL 0
#endif

extern void register_node(void *, void *);
extern s32 text_sprite_builder_address[4];

typedef struct CopyBlock {
    s32 words[12];
} CopyBlock;

/* Creates an object with the supplied value and 48-byte initialization block. */
void create_scene_object_with_48_byte_payload(s32 init_value, void *init_data)
{
    ObjectNodeHeader *obj;

    obj = allocate_list_node(1, &scene_object_list_anchor.next);
    if (obj != NULL) {
        *(CopyBlock *)((s8 *)obj + 0x20) = *(CopyBlock *)init_data;
        obj->update_callback = init_value;
        register_node(obj, &text_sprite_builder_address);
    }
}
