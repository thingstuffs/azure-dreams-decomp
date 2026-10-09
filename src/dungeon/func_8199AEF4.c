#include "modules/dungeon_ovl_19ba800.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Node {
    char pad00[0x10];
    void *field10;
    char pad14[0xC];
    void *field20;
} Node;

typedef struct Child {
    char pad00[4];
    void *field04;
    void *field08;
    void *field0C;
    void *field10;
    char pad14[0x24];
    u16 field38;
} Child;


#define D_800242D4 ((char *)func_800242D4)
extern char D_80024A8C[];

/* Allocate a node and initialize its child with supplied values and shared source data. */
void func_800246F4(ObjectNodeHeader *node_value, void *child_value)
{
    Node *node;
    Child *child;
    EntityRec *source;
    void *callback;
    u16 source_value;

    node = func_8003FD64(0x10, &D_80083498.next);
    if (node != NULL) {
        child = (Child *)((char *)node + 0x20);
        node->field10 = D_800242D4;
        callback = D_80024A8C;
        source = D_800814A8;
        child->field10 = callback;
        node->field20 = node_value;
        child->field04 = &D_80083498.next;
        source_value = ((u16)source->unk_88);
        child->field0C = child_value;
        child->field08 = node;
        child->field38 = source_value;
    }
}
