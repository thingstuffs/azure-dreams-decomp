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

extern void *func_8004B4A8(void *);
extern void func_8004F52C(void *);
extern void *func_8003FE78(s32, void *, s32);
extern void func_8004491C(void *, void *);
extern void func_8004F330(void *, s32);
extern void bzero(void *, s32);
extern void *func_8004F308(void *);
extern void func_8004F3D8(void *, s32);
extern void func_8004EEBC(S_8004EEBC_Obj *);

void *func_8004F418(s32 arg0, s32 arg1)
{
    S_8004F418_Node *node = &D_80084138;
    u8 *body = node->body;
    u8 *field210;

    if (func_8004B4A8(node) == 0) {
        node = func_8003FE78(0, node, 0xCF);
        func_8004491C(node, D_80027DD0);
    } else {
        func_8004F52C(node);
        node->flags &= 0x7FFF;
        bzero(body, 0x31C);
    }

    D_801C9E40[0x19] = 0;
    D_801C9E40[0x1A] = 0;
    D_801C9E40[0x1B] = 0;
    D_801C9E40[0x108ED] = 0;
    D_801C9E40[0x108EE] = 0;
    D_801C9E40[0x108EF] = 0;
    func_8004F330(body, 7);

    field210 = body + 0x210;
    node->unkC = field210;
    *(void **)(body + 0x21C) = func_8004F308(body + 0x220);
    *(s32 *)(body + 4) = arg1;
    func_8004F3D8(body, arg0);
    node->unk10 = func_8004EEBC;
    func_8004EEBC((S_8004EEBC_Obj *)body);
    return node;
}
