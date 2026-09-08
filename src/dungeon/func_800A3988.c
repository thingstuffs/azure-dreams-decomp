#include "common.h"

typedef struct {
    u8 index;
    u8 group;
} DungeonArg;

typedef struct {
    u16 flags;
    u8 pad2[18];
} DungeonItem;

typedef struct {
    u8 pad[12];
    DungeonItem *entries;
    u8 pad10[4];
} DungeonGroup;

extern void func_8004A8D8(u8, u8);
extern DungeonGroup D_80073414[];

/* Updates the selected item through func_8004A8D8 and clears its flag 0x400 in the item category table. */
void func_800A90E8(DungeonArg *selection)
{
    func_8004A8D8(selection->group, selection->index);
    D_80073414[selection->group].entries[selection->index].flags &= 0xFBFF;
}
