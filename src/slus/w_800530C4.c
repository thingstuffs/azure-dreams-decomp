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

/* Reset group state, increment its counter, and set bit 0x8000 in the main, child, and global flags. */
void func_800530C4(Main *main)
{
    Group **group_slot;
    s32 child_index;
    Child *child;
    Child **child_cursor;

    main->group->field_1C = 0;
    child_index = 0;
    main->group->counter++;
    group_slot = &main->group;
    child_cursor = (Child **)group_slot;
    do {
        child = child_cursor[4];
        D_800814A0 |= 0x8000;
        child->flags |= 0x8000;
        child_cursor++;
        child_index++;
    } while (child_index < 16);

    ((volatile u16 *)group_slot)[-1] |= 0x8000;
    D_800814A0_store = D_800814A0;
}
