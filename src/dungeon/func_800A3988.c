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

void func_800A90E8(DungeonArg *arg0)
{
    func_8004A8D8(arg0->group, arg0->index);
    D_80073414[arg0->group].entries[arg0->index].flags &= 0xFBFF;
}
