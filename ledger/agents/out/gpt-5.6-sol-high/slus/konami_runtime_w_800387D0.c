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

// Advances the animation, moves its strips, clears the trailing strip, and restores the object's callback.
void func_800387D0(AnimObject *object)
{
    s32 strip_index;

    object->frame_a += 4;
    strip_index = 0;
    if ((s16)object->frame_a < D_8006A8B4[object->frame_2a]) {
        return;
    }

    object->frame_a = 0;
    if (object->count_25 - 1 > 0) {
        s32 *frame_table = D_8006A8B4;

loop:
            func_8003AE28(
                (s16)(object->x0 + object->x8),
                (s16)(object->y2 + object->frame_a + frame_table[object->frame_2a] * (strip_index + 1) + 2),
                object->size_c / 4,
                *(s16 *)&frame_table[object->frame_2a],
                (s16)object->x0 + (s16)object->x8,
                ((SignedAnimPrefix *)object)->y2 + ((SignedAnimPrefix *)object)->frame_a + frame_table[object->frame_2a] * strip_index + 2);
            strip_index += 1;
            if (strip_index < object->count_25 - 1) {
                goto loop;
            }
    }

    {
        s32 *frame_table;
        s32 *frame_entry;

        frame_table = D_8006A8B4;
        frame_entry = frame_table + object->frame_2a;

        func_8003AE60(
            (s16)(object->x0 + object->x8),
            (s16)(*(s16 *)&object->y2 + *(s16 *)&object->frame_a + *frame_entry * (object->count_25 - 1) + 2),
            object->size_c / 4,
            *(s16 *)frame_entry,
            0, 0, 0);
    }
    object->callback = func_80038A10;
}
