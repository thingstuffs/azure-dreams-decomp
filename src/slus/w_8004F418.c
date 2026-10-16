#include "common.h"

typedef struct S_8004EEBC_Obj S_8004EEBC_Obj;

typedef struct S_8004F418_Node {
    struct S_8004F418_Node *next;
    u8 pad4[8];
    void *unkC;
    void (*unk10)(S_8004EEBC_Obj *);
    u8 pad14[10];
    u16 flags;
    u8 body[0x31C];
} S_8004F418_Node;

extern S_8004F418_Node D_80084138;
extern u8 D_801C9E40[0x10900];
extern u8 D_80027DD0[16];

extern void *findActiveListNode(void *);
extern void slusSetObjectCleanupFlag(void *);
extern void *initializeSceneObjectInBuffer(s32, void *, s32);
extern void func_8004491C(void *, void *);
extern void initializeMenuBackdropDisplayNodes(void *, s32);
extern void bzero(void *, s32);
extern void *linkMenuBackdropDisplayNodes(void *);
extern void initializeMenuBackdropLayout(void *, s32);
extern void updateMenuBackdropVariant(S_8004EEBC_Obj *);

/* Initialize or reset the shared node, link its owner and state, and select its active sub-object. */
void *createOrResetSevenEntryMenuBackdrop(s32 owner, s32 state)
{
    S_8004F418_Node *node = &D_80084138;
    u8 *body = node->body;
    u8 *template_node;

    if (findActiveListNode(node) == 0) {
        node = initializeSceneObjectInBuffer(0, node, 0xCF);
        func_8004491C(node, D_80027DD0);
    } else {
        slusSetObjectCleanupFlag(node);
        node->flags &= 0x7FFF;
        bzero(body, 0x31C);
    }

    D_801C9E40[0x19] = 0;
    D_801C9E40[0x1A] = 0;
    D_801C9E40[0x1B] = 0;
    D_801C9E40[0x108ED] = 0;
    D_801C9E40[0x108EE] = 0;
    D_801C9E40[0x108EF] = 0;
    initializeMenuBackdropDisplayNodes(body, 7);

    template_node = body + 0x210;
    node->unkC = template_node;
    *(void **)(body + 0x21C) = linkMenuBackdropDisplayNodes(body + 0x220);
    *(s32 *)(body + 4) = state;
    initializeMenuBackdropLayout(body, owner);
    node->unk10 = updateMenuBackdropVariant;
    updateMenuBackdropVariant((S_8004EEBC_Obj *)body);
    return node;
}
