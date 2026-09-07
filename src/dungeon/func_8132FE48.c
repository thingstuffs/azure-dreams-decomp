#include "common.h"

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} __attribute__((packed)) Rect;

typedef struct {
    s16 x;
    s16 y;
} Point;

extern Rect D_80164824;
extern s32 D_800814A0;
extern void func_800B8FC8(void *, Rect *, Point *, s32, s32);

void func_80166E48(void *arg0, s32 arg1, void *arg2)
{
    Rect rect;
    Point center;
    u16 timer;
    u16 angle;
    u16 next;
    s32 test;

    rect = D_80164824;
    center.x = rect.x + ((s16)rect.w >> 1);
    center.y = rect.y + ((s16)rect.h >> 1);

    angle = *(u16 *)((u8 *)arg2 + 0x1A);
    next = angle - 0x28;
    test = next << 16;
    angle = next;
    if (test <= 0) {
        angle += 0x1000;
    }
    *(u16 *)((u8 *)arg2 + 0x1A) = angle;

    func_800B8FC8(arg0, &rect, &center, 1, 1);

    timer = *(u16 *)((u8 *)arg0 + 0x18) - 1;
    *(u16 *)((u8 *)arg0 + 0x18) = timer;
    if ((s16)timer <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
