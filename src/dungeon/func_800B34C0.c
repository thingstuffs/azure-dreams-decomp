#include "common.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

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

typedef struct Object_800B34C0 {
    u8 pad0[0xC];
    Child *child;
    void *state;
    u8 pad14[0xC];
    Tail tail;
} Object_800B34C0;

struct S_800B8830_1;
extern void update_arcing_effect(void *motion, S_800B8830_3 *coords, struct S_800B8830_1 *render);
extern u8 D_800DF2F8[];
extern u8 D_800DF334[];

extern void * func_8003FD64();

/* Create an object with default child and tail data when none are supplied. */
void create_timed_model_effect(void *owner, s32 value, void *child_data, void *tail_data)
{
    Object_800B34C0 *object;
    Child *child;
    void *descriptor;
    EntityRec *header;

    {
        u8 *call_page;
        s32 kind;

        call_page = (u8 *)0x80080000;
        kind = 0x12;
        object = func_8003FD64(kind, (u8 *)((u8 *)(&D_80083498)));
    }
    if (object != 0) {
        child = object->child;
        object->state = update_arcing_effect;

        if (child_data != 0) {
            child->value8 = child_data;
        } else {
            child->value8 = D_800DF2F8;
        }

        child->value10 = 0x60;
        object = (Object_800B34C0 *)&object->tail;

        if (tail_data != 0) {
            ((Tail *)object)->valueC = tail_data;
        } else {
            u8 *fallback;

            fallback = D_800DF334 - 0x3C;
            ((Tail *)object)->valueC = fallback;
        }
        descriptor = (void *)&D_80083498;
        header = D_800814A8;
        ((Tail *)object)->owner = owner;
        ((Tail *)object)->descriptor = descriptor;
        ((Tail *)object)->value32 = ((u16)header->unk_88);
        ((Tail *)object)->value8 = value;
    }
}
