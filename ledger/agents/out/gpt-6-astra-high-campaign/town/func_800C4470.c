#include "common.h"

typedef struct { s16 x, y, w, h; } RECT;

extern int LoadImage(RECT *rect, void *p);
extern void DrawSync(s32 a0);

extern RECT D_800D43B0;
extern RECT D_800D43B8;

/* Upload both sb01_over_push images to VRAM, waiting for each transfer. */
void func_800C1BD0(void) {
    LoadImage(&D_800D43B0, (void *)0x80020000);
    DrawSync(0);
    LoadImage(&D_800D43B8, (void *)0x80024000);
    DrawSync(0);
}
