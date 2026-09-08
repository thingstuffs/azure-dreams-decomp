#include "common.h"

typedef struct TownLink TownLink;

struct TownLink {
    u8 pad_00[4];
    TownLink *next;
    u8 pad_08[0xC];
    u8 type;
    u8 pad_15[0x7F];
    s8 state;
};

extern s32 D_800CFCB4;

/* Count type 4 links whose state is not -1. */
s32 func_800A0608(void)
{
    TownLink *link = ((TownLink *)&D_800CFCB4)->next;
    s32 count = 0;

    if (link != (TownLink *)&D_800CFCB4) {
        s32 type = 4;
        s32 state = -1;
        TownLink *sentinel = (TownLink *)&D_800CFCB4;

        do {
            if (link->type == type && link->state != state) {
                count++;
            }
            link = link->next;
        } while (link != sentinel);
    }

    return count;
}
