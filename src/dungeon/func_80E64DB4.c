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

/* Select a random eligible dungeon item and initialize its parameters. */
s32 func_801745B4(DungeonArg *selection, u8 *context)
{
    DungeonGroup *groups;
    DungeonGroup *candidate_group;
    s32 retries_left;
    s32 accepted;
    s32 group;
    s32 item_index;
    s32 original_class;
    s32 class_check;
    s32 param;

    accepted = 0;
    retries_left = 15;
    original_class = D_80073414[selection->group].entries[selection->index].flags & 0x3000;
    groups = D_80073414;

    do {
        group = func_800A6DA4(1, 19);
        candidate_group = (DungeonGroup *)((u32)((u8)group * sizeof(DungeonGroup)) + (u32)groups);

        if (candidate_group->count == 1 || (u8)group == 18 || (u8)group == 14) {
            goto next_try;
        }

        item_index = func_800A6DA4(1, (u16)(candidate_group->count - 1));
        if (candidate_group->entries[(u8)item_index].flags & 0x10) {
            goto next_try;
        }

        if (retries_left >= 12) {
            class_check = groups[selection->group].entries[selection->index].flags & 0x3000;
            if (original_class == class_check) {
                accepted = 1;
            }
            class_check = accepted;
        } else {
            class_check = groups[selection->group].entries[selection->index].flags & 0x3000;
            if (original_class >= class_check) {
                accepted = 1;
            }
            class_check = accepted;
        }

        if (class_check != 0) {
            selection->group = group;
            selection->index = item_index;
            selection->param = 0;
            selection->flags = 0;
            if ((u8)group == 4) {
                selection->flags = 0x80;
                if ((u8)item_index == 17) {
                    param = 1;
                } else {
                    param = (context[0x25] + 15) / 16;
                }
                selection->param = param;
            }
            return 1;
        }

next_try:
        retries_left--;
    } while (retries_left >= 0);

    return 0;
}
