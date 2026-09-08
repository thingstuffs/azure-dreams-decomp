#include "common.h"

typedef struct TownLink TownLink;

struct TownLink {
    u8 pad_00[4];
    TownLink *next;
    u8 pad_08[0xC];
    u8 type;
    u8 pad_15[0x7F];
    s8 state;
    u8 pad_95[3];
    void *object;
};

extern s32 D_800CFCB4;
extern s32 func_8009FF50(void);
extern void func_800A0404(void *);

/* Process active type-4 town links that have no associated object. */
void func_800A0560(void)
{
    TownLink *sentinel = (TownLink *)&D_800CFCB4;
    TownLink *link = sentinel->next;

    if (func_8009FF50() != 0) {
        return;
    }

    if (link == sentinel) {
        return;
    }

    do {
        if (link->type == 4 && link->state != -1 && link->object == 0) {
            func_800A0404((u8 *)link + 0x4C);
        }
        link = link->next;
    } while (link != sentinel);
}
