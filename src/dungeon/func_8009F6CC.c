#include "common.h"

typedef struct DungeonArea {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 unk8;
    s16 enabled;
    u8 pad[8];
} DungeonArea;

extern s32 func_8009A350(s16 x, s16 y, s32 arg2, u16 *tile);
extern s32 func_800A6D30(void);
extern s16 D_80081468[3];
extern s8 D_800E2970[];

s32 func_800A4E2C(u8 *arg0, u8 *arg1)
{
    u16 tile;
    s16 areaIndex;
    s16 x;
    s16 y;
    s32 attempts;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    DungeonArea *area;
    s16 *limits;
    DungeonArea *areas;

    attempts = 0x100;
    limits = D_80081468;
    areas = (DungeonArea *)D_800E2970;

    do {
        areaIndex = (u16)func_800A6D30() % limits[3];
        area = (DungeonArea *)((areaIndex * (s32)sizeof(*area)) + (u32)areas);
        if (area->enabled != 0) {
            x = (u32)(func_800A6D30() & 0xFFFF) % area->width;
            y = (u32)(func_800A6D30() & 0xFFFF) % area->height;
            x += area->x;
            y += area->y;
            if ((s16)func_8009A350((s16)(x - 1), y, 0, &tile) != 0) {
                if ((tile & 0xF720) == 0) {
                    result = areaIndex;
                    goto found;
                }
            }
        }
        attempts--;
    } while (attempts > 0);

    for (y = 1; y < 0x3F; y++) {
        for (x = 1; x < 0x3F; x++) {
            if ((s16)func_8009A350((s16)(x - 1), y, 0, &tile) != 0) {
                if ((tile & 0xF720) == 0) {
                    result = 0;
                    goto found;
                }
            }
        }
    }

    if ((u32)(*arg0 - 1) >= 0x3E) {
        goto fallback;
    }
    if ((u32)(*arg1 - 1) >= 0x3E) {
        goto fallback;
    }
    result = 0;
    goto done;

found:
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    *arg0 = x;
    *arg1 = y;
    goto done;

fallback:
    *arg0 = 1;
    *arg1 = 1;
    result = 0;
done:
    return result;
}

/* MECHANISM: The retail 0x40 frame comes from the tile local plus s0-s7/fp holds.
   A guarded $v0 result carrier establishes each dispatcher return on its CFG edge,
   leaving both func_800A5018 sibcalls eligible for SHAPE-B tail conversion. */
