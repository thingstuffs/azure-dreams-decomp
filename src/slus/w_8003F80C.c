#include "common.h"

#include "common.h"

typedef struct { s16 x, y, w, h; } RECT;

extern int LoadImage(RECT *rect, void *p);
extern s32 D_80082EC0[128];

/* Registers a VRAM "tile cache" slot: cellIdx is derived from a1's vram-offset
 * encoding ((a1-0x7000)>>6, a 64-cell grid). Unless a3&1 suppresses it, issues a
 * LoadImage of a 1-row strip into VRAM at a position computed from cellIdx/a1's
 * low bits, width scaled from a2 (palette/tile-set id). Unless a3&2 suppresses
 * it, stores a packed (a0 & 0xFFFFFF) | (a2<<24) entry into D_80082EC0[cellIdx]
 * (source-address/tile-set id). If cellIdx is one of the first 64 slots and
 * a2>=0x11, clears the paired "loaded" flag at D_80082EC0[cellIdx+0x40]. */
void func_8003F80C(s32 a0, s32 a1, s32 a2, s32 a3)
{
    s32 cellIdx;
    s32 flags;
    s32 pal;
    s32 *base;

    flags = a3;
    pal = a2;
    cellIdx = (a1 - 0x7000) >> 6;
    if (!(flags & 1)) {
        RECT rect;
        rect.x = ((cellIdx & 0x40) << 1) + ((a1 & 0x3F) << 4);
        rect.y = (cellIdx & 0x3F) + 0x1C0;
        rect.w = pal << 4;
        rect.h = 1;
        LoadImage(&rect, (void *)a0);
    }
    if (!(flags & 2)) {
        D_80082EC0[cellIdx] = (a0 & 0xFFFFFF) | (pal << 24);
    }
    if (cellIdx < 0x40 && pal >= 0x11) {
        base = D_80082EC0;
        base[cellIdx + 0x40] = 0;
    }
}
