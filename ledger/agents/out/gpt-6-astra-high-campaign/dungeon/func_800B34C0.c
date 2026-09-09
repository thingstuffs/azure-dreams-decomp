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

/* Create an object with default child and tail data when none are supplied. */
void func_800B8C20(void *owner, s32 value, void *child_data, void *tail_data)
{
    Object *object;
    Child *child;
    void *descriptor;
    u8 *descriptor_page;
    EntityHeader *header;

    {
        register u8 *call_page ASM_REG("$5");
        s32 kind;

        call_page = (u8 *)0x80080000;
        kind = 0x12;
        ASM_KEEP(call_page);
        ASM_KEEP(kind);
        object = func_8003FD64(kind, call_page + 0x3498);
    }
    if (object != 0) {
        child = object->child;
        object->state = D_800B8830;

        if (child_data != 0) {
            child->value8 = child_data;
        } else {
            child->value8 = D_800DF2F8;
        }

        child->value10 = 0x60;
        object = (Object *)&object->tail;

        if (tail_data != 0) {
            ((Tail *)object)->valueC = tail_data;
        } else {
            u8 *fallback;

            fallback = D_800DF334 - 0x3C;
            ((Tail *)object)->valueC = fallback;
        }
        descriptor_page = (u8 *)0x80080000;
        ASM_KEEP(descriptor_page);
        header = D_800814A8[0];
        descriptor = descriptor_page + 0x3498;
        ((Tail *)object)->owner = owner;
        ((Tail *)object)->descriptor = descriptor;
        ((Tail *)object)->value32 = header->value88;
        ((Tail *)object)->value8 = value;
    }
}
