#include "common.h"

typedef struct Child {
    u8 pad0[8];
    void *value8;
    u8 padC[4];
    s16 value10;
} Child;

typedef struct Tail {
    void *owner;
    void *descriptor;
    s32 value8;
    void *valueC;
    u8 pad10[0x22];
    u16 value32;
} Tail;

typedef struct Object {
    u8 pad0[0xC];
    Child *child;
    void *state;
    u8 pad14[0xC];
    Tail tail;
} Object;

typedef struct EntityHeader {
    u8 pad0[0x88];
    u16 value88;
} EntityHeader;

extern u8 D_80083498[];
extern u8 D_8008346C[16];
extern u8 D_800B8830[];
extern u8 D_800DF2F8[];
extern u8 D_800DF334[];
extern EntityHeader *D_800814A8[3];

extern void *func_8003FD64(s32, void *);

void func_800B8C20(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    Object *object;
    Child *child;
    void *descriptor;
    u8 *descriptor_page;
    EntityHeader *header;

    {
        register u8 *call_page ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        s32 kind;

        call_page = (u8 *)0x80080000;
        kind = 0x12;
        ASM_KEEP(call_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(kind);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        object = func_8003FD64(kind, call_page + 0x3498);
    }
    if (object != 0) {
        do { child = object->child; } while (0);
        object->state = D_800B8830;

        if (arg2 != 0) {
            child->value8 = arg2;
        } else {
            child->value8 = D_800DF2F8;
        }

        do { child->value10 = 0x60; } while (0);
        object = (Object *)&object->tail;

        if (arg3 != 0) {
            ((Tail *)object)->valueC = arg3;
        } else {
            u8 *fallback;

            fallback = D_800DF334 - 0x3C;
            ((Tail *)object)->valueC = fallback;
        }
        descriptor_page = (u8 *)0x80080000;
        ASM_KEEP(descriptor_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        header = D_800814A8[0];
        descriptor = descriptor_page + 0x3498;
        ((Tail *)object)->owner = arg0;
        ((Tail *)object)->descriptor = descriptor;
        ((Tail *)object)->value32 = header->value88;
        ((Tail *)object)->value8 = arg1;
    }
}

/* MECHANISM: The natural 0x28 frame holds all four incoming args; destructively advancing object
   by 0x20 keeps the tail base in a0 across both tail-call and store paths. Scoped a1/a0 call
   staging orders lui-page, li-kind, ra-save, and the jal-slot low half. Sequential pinned v0
   address roles plus a named v1 header and value32-before-value8 fill the final load delay. */
