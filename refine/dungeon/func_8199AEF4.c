#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Node {
    char pad00[0x10];
    void *field10;
    char pad14[0xC];
    s32 field20;
} Node;

typedef struct Child {
    char pad00[4];
    void *field04;
    void *field08;
    s32 field0C;
    void *field10;
    char pad14[0x24];
    u16 field38;
} Child;

typedef struct Source {
    char pad00[0x88];
    u16 field88;
} Source;

extern void *func_8003FD64(s32, void *);
extern char D_800242D4[];
extern char D_80024A8C[];
extern char D_80083498[];
extern Source *D_800814A8[];

/* Allocate a node and initialize its child with supplied values and shared source data. */
void func_8199AEF4(s32 node_value, s32 child_value)
{
    Node *node;
    Child *child;
    Source *source;
    void *callback;
    u16 source_value;

    node = func_8003FD64(0x10, D_80083498);
    if (node != NULL) {
        child = (Child *)((char *)node + 0x20);
        node->field10 = D_800242D4;
        callback = D_80024A8C;
        source = D_800814A8[0];
        child->field10 = callback;
        node->field20 = node_value;
        child->field04 = D_80083498;
        source_value = source->field88;
        child->field0C = child_value;
        child->field08 = node;
        child->field38 = source_value;
    }
}
