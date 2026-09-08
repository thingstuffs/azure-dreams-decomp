#include "common.h"

typedef struct {
    s32 unk0;
    void *object;
} ObjectEntry;

typedef struct {
    u8 pad0[0x10];
    void *current;
    u8 pad14[4];
    s32 object_index;
} TownState;

extern ObjectEntry D_80082660[];
extern s16 D_80083780[];
extern TownState D_800CFCB4;
extern s16 D_800D5078[];

extern s16 func_800C2B88(s16 x, s16 z, s32 arg2);

/* Return the current object's cached value or look it up at the town coordinates. */
s16 func_800C2BE8(void *object, s32 lookup_mode)
{
    TownState *state = &D_800CFCB4;

    if (object == state->current &&
        object == (u8 *)D_80082660[*(s32 *)((u8 *)object + 0x60)].object +
                    0x20) {
        return D_800D5078[state->object_index];
    }

    return func_800C2B88(D_80083780[1], D_80083780[3], lookup_mode);
}
