#include "common.h"

/* D_80083160: shared state table. offset 0x1DC holds a pointer to the
 * dungeon map cell array (6-byte cells, first s16 field is the cell
 * "type"); offset 0x1F0 (0x1DC+0x14) holds a s16 shift value used to
 * compute the row stride (row index << shift). Local (own-view)
 * declaration per merge-safety contract -- only a raw byte-offset
 * view is needed here (matches the field access shape in the asm,
 * base symbol used with explicit sub-offsets, not folded). */
typedef struct {
    u8 pad0[0x1DC];
    void *mapPtrField;  /* offset 0x1DC */
} S_800999DC_D80083160;

extern S_800999DC_D80083160 D_80083160;

extern void func_8009EEAC(void);
extern void func_8009F3D4(s16 x, s16 y, s32 color, s32 size, s32 count);

typedef struct {
    u16 type;
    s8 unk2[4];
} MapCell;

/* Redraw the minimap: plot one marker for every type-3 cell of the floor grid. */
void func_8009F13C(void) {
    MapCell *mapPtr;
    u8 *shiftBase;
    s32 x;
    s32 y;
    s32 count;

    mapPtr = (MapCell *)D_80083160.mapPtrField;
    shiftBase = (u8 *)&D_80083160.mapPtrField;
    func_8009EEAC();
    count = 0;
    y = 1;
    do {
        x = 1;
        do {
            if (mapPtr[x + (y << *(s16 *)(shiftBase + 0x14))].type == 3) {
                func_8009F3D4(x, y, 0x808080, 0x10, count);
                count += 1;
            }
            x += 1;
        } while (x < 0x3F);
        y += 1;
    } while (y < 0x3F);
}
