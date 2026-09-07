#include "common.h"

#include "common.h"

extern s32 D_800814A0;
extern volatile s32 D_800814A0_store asm("D_800814A0");

typedef struct Group {
    u8 pad00[6];
    u16 counter;
    u8 pad08[0x14];
    s32 field_1C;
} Group;

typedef struct Child {
    u8 pad00[0x1E];
    volatile u16 flags;
} Child;

typedef struct Main {
    u8 pad00[0x1E];
    u16 flags;
    Group *group;
    u8 pad24[0xC];
    Child *children[16];
} Main;

void func_800530C4(Main *arg0)
{
    Group **p;
    s32 i;
    Child *child;
    Child **children;

    arg0->group->field_1C = 0;
    i = 0;
    arg0->group->counter++;
    p = &arg0->group;
    children = (Child **)p;
    do {
        child = children[4];
        D_800814A0 |= 0x8000;
        child->flags |= 0x8000;
        children++;
        i++;
    } while (i < 16);

    ((volatile u16 *)p)[-1] |= 0x8000;
    D_800814A0_store = D_800814A0;
}
