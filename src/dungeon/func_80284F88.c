#include "common.h"

typedef struct {
    u16 x;
    u16 y;
    s16 width;
    s16 height;
    u8 pad[12];
} DungeonRect;

typedef struct {
    u16 x;
    u16 y;
    u16 flags;
} DungeonCell;

typedef struct {
    DungeonCell *cells;
    u8 pad[16];
    s16 shift;
} DungeonState;

extern DungeonState D_8008333C;
extern DungeonRect D_800E2970[];
extern s16 func_800BCB04(s32, s32, s32);

s32 func_80017F88(s16 rectIndex, s16 *outX, s16 *outY, s16 checkFlags)
{
    s16 best;
    s16 rows;
    s16 columns;
    s16 tileY;
    s16 tileX;
    s16 value;
    s32 signedY;
    u16 flags;
    s32 tileYAddress;
    DungeonCell *cells;
    DungeonState *state;

    best = -0x200;
    rows = D_800E2970[rectIndex].height;
    tileY = D_800E2970[rectIndex].y;
    state = &D_8008333C;
    cells = state->cells;
    if (rows > 0) {
        do {
            columns = D_800E2970[rectIndex].width;
            tileX = D_800E2970[rectIndex].x;
            if (columns > 0) {
                signedY = (s16)tileY;
                tileYAddress = (signedY << 6) + 0x20;
                do {
                    flags = cells[(s16)tileX
                        + (signedY << state->shift)].flags;
                    if (!(flags & 0x8400)
                        && ((checkFlags == 0)
                        || ((flags & 0x300) == 0x200))) {
                        value = func_800BCB04(
                            (((s16)tileX << 6) + 0x20) & 0xFFE0,
                            tileYAddress & 0xFFFF,
                            -0x400);
                        if (value < 0x200) {
                            if (best < value) {
                                *outX = tileX;
                                best = value;
                                *outY = tileY;
                            }
                        }
                    }
                    columns--;
                    tileX++;
                } while ((columns << 16) > 0);
            }
            rows--;
            tileY++;
        } while ((rows << 16) > 0);
    }
    if (best == -0x200) {
        best = 0x200;
    }
    return best;
}

/* MECHANISM: A real 20-byte DungeonRect makes both direct table indexes emit the
   retail multiply-by-20 sequence; a promoted signed row value and direct signed-16
   counters preserve the inner lifetimes while the best value spans the sole call. */
