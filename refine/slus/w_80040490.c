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

/* Decompresses image data into an allocated buffer and uploads it to the VRAM rectangle. */
s32 func_80040490(u8 *compressed_image, S_80040490_RECT *rect) {
    void *image_buf;

    image_buf = func_80040574(rect->w * (rect->h << 1));
    func_8004068C(compressed_image, image_buf);
    return LoadImage(rect, image_buf);
}
