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

extern Rect D_8016481C;
extern s32 D_800814A0;
extern void func_800B8FC8(void *, Rect *, Point *, s32, s32);

void func_80166D68(void *arg0, s32 arg1, void *arg2)
{
    Rect rect;
    Point center;
    u16 timer;

    rect = D_8016481C;
    center.x = rect.x + ((s16)rect.w >> 1);
    center.y = rect.y + ((s16)rect.h >> 1);
    *(u16 *)((u8 *)arg2 + 0x1A) += 0x28;
    func_800B8FC8(arg0, &rect, &center, 1, 1);

    timer = *(u16 *)((u8 *)arg0 + 0x18) - 1;
    *(u16 *)((u8 *)arg0 + 0x18) = timer;
    if ((s16)timer <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
