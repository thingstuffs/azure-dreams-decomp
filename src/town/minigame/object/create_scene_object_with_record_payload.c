#include "common.h"
#include "shared/object_node.h"

typedef struct {
    s32 words[10];
} Record;

extern void *allocate_list_node();
extern void register_node();
extern s32 display_registration_tag;

/* Allocate an object, copy its record, set its value, and pass it for initialization. */
void create_scene_object_with_record_payload(s32 object_value, void *record) {
    ObjectNodeHeader *object;

    object = allocate_list_node(1, ((u8 *)(&scene_object_list_anchor)));
    if (object != 0) {
        *(Record *)(((void *)object) + 0x20) = *(Record *)record;
        object->update_callback = object_value;
        register_node(object, &display_registration_tag);
    }
}
