#ifndef SLUS_JTBL_80041344_H
#define SLUS_JTBL_80041344_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"

typedef struct {
    u16 cmd;
    u16 size;
    s32 offset;
    union {
        struct { u16 x, y, w; } t;
        struct { s32 a, b; } m;
    } u;
} S_80041344;

extern u32 D_80080A8C;
extern void func_8004068C(u8 *src, u8 *dst);
extern void func_8003F80C(void *src, s32 x, s32 y, s32 flags);
extern void LoadImage(void *rect, void *data);
extern void DrawSync(s32 mode);
extern void *memcpy(void *dst, void *src, s32 size);

/* Process resource commands to upload images, copy data, and relocate pointers. */

void func_80041344(s32 data_base, void *scratch);

#endif
