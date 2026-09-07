#include "common.h"

#include "common.h"

typedef struct AnimObject AnimObject;
typedef struct SignedAnimPrefix SignedAnimPrefix;

struct SignedAnimPrefix {
    s16 x0;
    s16 y2;
    u8 pad4[4];
    s16 x8;
    s16 frame_a;
};

struct AnimObject {
    u16 x0;
    u16 y2;
    u8 pad4[4];
    u16 x8;
    u16 frame_a;
    s16 size_c;
    u8 pad_e[2];
    void (*callback)(AnimObject *);
    u8 pad_14[0x11];
    u8 count_25;
    u8 pad_26[4];
    u8 frame_2a;
};

extern s32 D_8006A8B4[];
extern void func_8003AE28(s16 x, s16 y, s32 w, s16 h, s32 move_x, s32 move_y);
extern void func_8003AE60(s16 x, s16 y, s32 w, s16 h, s32 r, s32 g, s32 b);
extern void func_80038A10(AnimObject *arg0);

// Scrolls the animation rows upward, clears the last row, and advances the callback when ready.
void func_800387D0(AnimObject *anim)
{
    s32 rowIndex;

    anim->frame_a += 4;
    rowIndex = 0;
    if ((s16)anim->frame_a < D_8006A8B4[anim->frame_2a]) {
        return;
    }

    anim->frame_a = 0;
    if (anim->count_25 - 1 > 0) {
        s32 *rowHeights = D_8006A8B4;

moveNextRow:
        func_8003AE28(
            (s16)(anim->x0 + anim->x8),
            (s16)(anim->y2 + anim->frame_a + rowHeights[anim->frame_2a] * (rowIndex + 1) + 2),
            anim->size_c / 4,
            *(s16 *)&rowHeights[anim->frame_2a],
            (s16)anim->x0 + (s16)anim->x8,
            ((SignedAnimPrefix *)anim)->y2 + ((SignedAnimPrefix *)anim)->frame_a + rowHeights[anim->frame_2a] * rowIndex + 2);
        rowIndex += 1;
        if (rowIndex < anim->count_25 - 1) {
            goto moveNextRow;
        }
    }

    {
        s32 *rowHeightTable;
        s32 *rowHeightEntry;

        rowHeightTable = D_8006A8B4;
        rowHeightEntry = rowHeightTable + anim->frame_2a;

        func_8003AE60(
        (s16)(anim->x0 + anim->x8),
        (s16)(*(s16 *)&anim->y2 + *(s16 *)&anim->frame_a + *rowHeightEntry * (anim->count_25 - 1) + 2),
        anim->size_c / 4,
        *(s16 *)rowHeightEntry,
        0, 0, 0);
    }
    anim->callback = func_80038A10;
}
