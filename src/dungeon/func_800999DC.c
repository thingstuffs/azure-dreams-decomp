#include "common.h"
#include "shared/game_work.h"

/* D_80083160: shared state table. offset 0x1DC holds a pointer to the
 * dungeon map cell array (6-byte cells, first s16 field is the cell
 * "type"); offset 0x1F0 (0x1DC+0x14) holds a s16 shift value used to
 * compute the row stride (row index << shift). Local (own-view)
 * declaration per merge-safety contract -- only a raw byte-offset
 * view is needed here (matches the field access shape in the asm,
 * base symbol used with explicit sub-offsets, not folded). */
extern void submit_activation_command(void);
extern void create_transformed_render_object(s16 x, s16 y, s32 color, s32 size, s32 count);

typedef struct {
    u16 type;
    s8 unk2[4];
} MapCell;

/* Redraw the minimap: plot one marker for every type-3 cell of the floor grid. */
void redraw_type_three_floor_markers(void) {
    MapCell *mapPtr;
    u8 *shiftBase;
    s32 x;
    s32 y;
    s32 count;

    mapPtr = (MapCell *)((void *)g_game_work.map.cells);
    shiftBase = (u8 *)((void * *)&g_game_work.map.cells);
    submit_activation_command();
    count = 0;
    y = 1;
    do {
        x = 1;
        do {
            if (mapPtr[x + (y << *(s16 *)(shiftBase + 0x14))].type == 3) {
                create_transformed_render_object(x, y, 0x808080, 0x10, count);
                count += 1;
            }
            x += 1;
        } while (x < 0x3F);
        y += 1;
    } while (y < 0x3F);
}
