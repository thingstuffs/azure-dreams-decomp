#include "common.h"
#include "shared/object_node.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "town/minigame/object.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 text_sprite_builder_address[4];

typedef struct CopyBlock {
    s32 words[12];
} CopyBlock;

/* Creates a text object from an update callback and a 48-byte initialization block. */
void create_text_sprite_object(void *update_callback, void *init_data)
{
    ObjectNodeHeader *obj;

    obj = allocate_list_node(1, &scene_object_list_anchor.next);
    if (obj != NULL) {
        *((CopyBlock *)NODE_BODY(obj)) = *(CopyBlock *)init_data;
        obj->update_callback = update_callback;
        register_node(obj, &text_sprite_builder_address);
    }
}
