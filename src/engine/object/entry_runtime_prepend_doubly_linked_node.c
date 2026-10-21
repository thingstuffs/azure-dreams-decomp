#include "common.h"
#include "engine/object.h"

typedef struct {
    unsigned char pad_00[0x54];
    void *unk_54;
} Struct800350B0;

/* Store a self-reference and pass its address to runtime_prepend_doubly_linked_node. */
void prepend_embedded_object_node(void *context, Struct800350B0 *object) {
    object->unk_54 = object;
    runtime_prepend_doubly_linked_node(context, &object->unk_54);
}
