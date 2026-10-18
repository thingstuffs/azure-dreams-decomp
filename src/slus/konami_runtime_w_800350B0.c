#include "common.h"

typedef struct {
    unsigned char pad_00[0x54];
    void *unk_54;
} Struct800350B0;

extern void runtime_prepend_doubly_linked_node(void *owner, void *node);

/* Store a self-reference and pass its address to runtime_prepend_doubly_linked_node. */
void func_800350B0(void *context, Struct800350B0 *object) {
    object->unk_54 = object;
    runtime_prepend_doubly_linked_node(context, &object->unk_54);
}
