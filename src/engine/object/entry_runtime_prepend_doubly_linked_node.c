#include "common.h"
#include "engine/object.h"

typedef struct {
    unsigned char pad_00[0x54];
    void *unk_54;
} Struct800350B0;

/* Store a self-reference and pass its address to prepend_owner_list_node. */
void prepend_embedded_object_node(void *context, void *object_data) {
    Struct800350B0 *object = object_data;
    object->unk_54 = object;
    prepend_owner_list_node(context, &object->unk_54);
}
