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

void func_800387D0(AnimObject *arg0)
{
    s32 i;

    arg0->frame_a += 4;
    i = 0;
    if ((s16)arg0->frame_a < D_8006A8B4[arg0->frame_2a]) {
        return;
    }

    arg0->frame_a = 0;
    if (arg0->count_25 - 1 > 0) {
        s32 *table = D_8006A8B4;

loop:
            func_8003AE28(
                (s16)(arg0->x0 + arg0->x8),
                (s16)(arg0->y2 + arg0->frame_a + table[arg0->frame_2a] * (i + 1) + 2),
                arg0->size_c / 4,
                *(s16 *)&table[arg0->frame_2a],
                (s16)arg0->x0 + (s16)arg0->x8,
                ((SignedAnimPrefix *)arg0)->y2 + ((SignedAnimPrefix *)arg0)->frame_a + table[arg0->frame_2a] * i + 2);
            i += 1;
            if (i < arg0->count_25 - 1) {
                goto loop;
            }
    }

    {
        s32 *base;
        s32 *entry;

        base = D_8006A8B4;
        entry = base + arg0->frame_2a;

        func_8003AE60(
            (s16)(arg0->x0 + arg0->x8),
            (s16)(*(s16 *)&arg0->y2 + *(s16 *)&arg0->frame_a + *entry * (arg0->count_25 - 1) + 2),
            arg0->size_c / 4,
            *(s16 *)entry,
            0, 0, 0);
    }
    arg0->callback = func_80038A10;
}
