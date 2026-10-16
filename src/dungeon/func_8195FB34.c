#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "m2c_compat.h"


   /* temp_v0_3 in func_80025334 */

   /* temp_v0_4 in func_80025334 */

   /* temp_a0 in func_80025334 */

   /* temp_v1 in func_80025334 */

/* Clears the 8-by-8 grid and initializes an object at the given position. */
void func_80025334(s16 x, s16 y, s16 z) {
    s16 row_index;
    s16 column_index;
    s16 next_row;
    s16 next_column;
    s32 column_shifted;
    s8 *grid;
    s8 *row;
    void *init_object;
    void *callback;
    S_8195FB34_2 *render_state;
    void *object;
    S_8195FB34_1 *position;
    S_8195FB34_3 *object_data;

    row_index = 0;
    grid = ((s8 *)D_8002745C);
    do {
        column_index = 0;
        row = (s8 *)(((s32) (row_index << 0x10) >> 0xC) + (u32)grid);
        do {
            column_shifted = column_index << 0x10;
            *(s16 *)((column_shifted >> 0xF) + (u32)row) = 0;
            next_column = column_index + 1;
            column_index = next_column;
        } while (next_column < 8);
        next_row = row_index + 1;
        row_index = next_row;
    } while (next_row < 8);
    object = func_8003FC64(0x202);
    if (object != NULL) {
        init_object = object;

        callback = dungeonAnimateTileHeightsAndTransition;

        ((S_8195FB34_0 *)object)->unk_10 = callback;
        func_8004491C(init_object, dungeonDispatchSevenBySevenTileGrid);
        position = ((S_8195FB34_0 *)object)->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = z;
        render_state = ((S_8195FB34_0 *)object)->unk_0C;
        render_state->unk_1E = 0x2000;
        render_state->unk_1C = 0x2000;
        render_state->unk_0C = 0x808080;
        object_data = object + 0x20;
        render_state->unk_10 = 0x20;
        ((S_8195FB34_0 *)object)->unk_20 = 0xF8F82CC0;
        object_data->unk_04 = 0x13D;
        render_state->unk_08 = object_data;
        object_data->unk_4C = 0x10;
    }
}
