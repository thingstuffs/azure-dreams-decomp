/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

extern u8 D_80083160[];

typedef struct S_800BDDD0_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    s16 unk_1A;
} S_800BDDD0_0;   /* temp_t3 in func_800BDDD0 */

/* Writes values 1 through 16 in row order into a wrapped 4x4 grid region. */
void func_800BDDD0(s32 start_x, s16 start_y) {
    s16 cell_value;
    s32 y;
    s32 x;
    s32 end_x;
    s32 wrapped_y;
    s32 origin_x;
    s32 x_limit;
    u8 *state;
    u8 *grid;
    s32 cells_addr;

    x = (s16)start_x;
    state = D_80083160;
    grid = state + 0x1DC;
    cells_addr = *(s32 *)(state + 0x1DC);
    origin_x = start_x;
    end_x = x + 4;
    if (x < end_x) {
        do {
            y = start_y;
            x_limit = end_x;
            while (y < (start_y + 4)) {
                cell_value = (x - origin_x) + 1;
                cell_value += (y - start_y) * 4;
                ASM_KEEP(cell_value);   /* MATCH pin: retail register colouring depends on it */
                wrapped_y = y & ((S_800BDDD0_0 *)grid)->unk_1A;
                y += 1;
                *((s16 *) (((s32) (((((S_800BDDD0_0 *)grid)->unk_18 & x) + (wrapped_y << ((S_800BDDD0_0 *)grid)->unk_14)) << 0x10) >> 0xF) + cells_addr)) = cell_value;
            }
            x += 1;
        } while (x < x_limit);
    }
}
