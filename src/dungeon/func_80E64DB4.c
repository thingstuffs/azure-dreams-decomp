#include "common.h"

typedef struct {
    u8 index;
    u8 group;
    u8 param;
    u8 flags;
} DungeonArg;

typedef struct {
    u16 flags;
    u8 pad2[18];
} DungeonItem;

typedef struct {
    u8 pad0[2];
    u8 count;
    u8 pad3[9];
    DungeonItem *entries;
    u8 pad10[4];
} DungeonGroup;

extern s32 func_800A6DA4(s32, s32);
extern DungeonGroup D_80073414[];

s32 func_801745B4(DungeonArg *arg0, u8 *arg1)
{
    DungeonGroup *groups;
    DungeonGroup *group_ptr;
    s32 tries;
    s32 accepted;
    s32 group;
    s32 item;
    s32 original_class;
    s32 candidate_class;
    s32 param;

    accepted = 0;
    tries = 15;
    original_class = D_80073414[arg0->group].entries[arg0->index].flags & 0x3000;
    groups = D_80073414;

    do {
        group = func_800A6DA4(1, 19);
        group_ptr = (DungeonGroup *)((u32)((u8)group * sizeof(DungeonGroup)) + (u32)groups);

        if (group_ptr->count == 1 || (u8)group == 18 || (u8)group == 14) {
            goto next_try;
        }

        item = func_800A6DA4(1, (u16)(group_ptr->count - 1));
        if (group_ptr->entries[(u8)item].flags & 0x10) {
            goto next_try;
        }

        if (tries >= 12) {
            candidate_class = groups[arg0->group].entries[arg0->index].flags & 0x3000;
            if (original_class == candidate_class) {
                accepted = 1;
            }
            candidate_class = accepted;
        } else {
            candidate_class = groups[arg0->group].entries[arg0->index].flags & 0x3000;
            if (original_class >= candidate_class) {
                accepted = 1;
            }
            candidate_class = accepted;
        }

        if (candidate_class != 0) {
            arg0->group = group;
            arg0->index = item;
            arg0->param = 0;
            arg0->flags = 0;
            if ((u8)group == 4) {
                arg0->flags = 0x80;
                if ((u8)item == 17) {
                    param = 1;
                } else {
                    param = (arg1[0x25] + 15) / 16;
                }
                arg0->param = param;
            }
            return 1;
        }

next_try:
        tries--;
    } while (tries >= 0);

    return 0;
}
