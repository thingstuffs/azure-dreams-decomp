#include "common.h"

typedef struct S_80040490_RECT {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} S_80040490_RECT;

extern void *func_80040574(s32 size);
extern void func_8004068C(u8 *src, void *dst);
extern s32 LoadImage(S_80040490_RECT *rect, void *p);

/* Decompresses image data pointed to by a0 into a freshly allocated VRAM-image
 * buffer sized from the RECT (a1)'s w/h, then hands the RECT + buffer to
 * LoadImage. Returns LoadImage's result. */
s32 func_80040490(u8 *a0, S_80040490_RECT *a1) {
    void *buf;

    buf = func_80040574(a1->w * (a1->h << 1));
    func_8004068C(a0, buf);
    return LoadImage(a1, buf);
}
