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

// Advances an animation object and renders its trailing frames when a frame completes.
void func_800387D0(AnimObject *anim_object)
{
    s32 trail_index;

    anim_object->frame_a += 4;
    trail_index = 0;
    if ((s16)anim_object->frame_a < D_8006A8B4[anim_object->frame_2a]) {
        return;
    }

    anim_object->frame_a = 0;
    if (anim_object->count_25 - 1 > 0) {
        s32 *frame_table = D_8006A8B4;

loop:
            func_8003AE28(
                (s16)(anim_object->x0 + anim_object->x8),
                (s16)(anim_object->y2 + anim_object->frame_a + frame_table[anim_object->frame_2a] * (trail_index + 1) + 2),
                anim_object->size_c / 4,
                *(s16 *)&frame_table[anim_object->frame_2a],
                (s16)anim_object->x0 + (s16)anim_object->x8,
                ((SignedAnimPrefix *)anim_object)->y2 + ((SignedAnimPrefix *)anim_object)->frame_a + frame_table[anim_object->frame_2a] * trail_index + 2);
            trail_index += 1;
            if (trail_index < anim_object->count_25 - 1) {
                goto loop;
            }
    }

    {
        s32 *base;
        s32 *frame_entry;

        base = D_8006A8B4;
        frame_entry = base + anim_object->frame_2a;

        func_8003AE60(
            (s16)(anim_object->x0 + anim_object->x8),
            (s16)(*(s16 *)&anim_object->y2 + *(s16 *)&anim_object->frame_a + *frame_entry * (anim_object->count_25 - 1) + 2),
            anim_object->size_c / 4,
            *(s16 *)frame_entry,
            0, 0, 0);
    }
    anim_object->callback = func_80038A10;
}
