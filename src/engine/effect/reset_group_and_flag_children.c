#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

#include "common.h"
#include "engine/effect.h"

extern s32 D_800814A0;

typedef struct Group {
    u8 pad00[6];
    u16 counter;
    u8 pad08[0x14];
    s32 field_1C;
} Group;

typedef struct Main {
    u8 pad00[0x1E];
    u16 flags;
    Group *group;
    u8 pad24[0xC];
    ObjectNodeHeader *children[16];
} Main;

/* Reset group state, increment its counter, and set bit 0x8000 in the main, child, and global flags. */
void reset_group_and_flag_children(Main *main)
{
    Group **group_slot;
    s32 child_index;
    ObjectNodeHeader *child;
    ObjectNodeHeader **child_cursor;

    main->group->field_1C = 0;
    child_index = 0;
    main->group->counter++;
    group_slot = &main->group;
    child_cursor = (ObjectNodeHeader **)group_slot;
    do {
        child = child_cursor[4];
        D_800814A0 |= OBJECT_REMOVE_PENDING;
        child->flags |= 0x8000;
        child_cursor++;
        child_index++;
    } while (child_index < 16);

    (*(u16 *)((u8 *)group_slot - 2)) |= NODE_REMOVE;
    D_800814A0 |= OBJECT_REMOVE_PENDING;
}
