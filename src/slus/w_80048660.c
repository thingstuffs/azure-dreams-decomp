#include "slus/gp_split_storage.h"

static u16 D_80081530;
u16 D_80080B10 = 0;
u16 D_80080B12 = 0;
u16 D_80080B14 = 0;
void func_80048660(struct S_80048660 *state)
{
    s32 row_step;
    s32 col_step;

    if (gameWork.unk_004 != D_80081530) {
        D_80080B14 = 0;
        D_80080B12 = 0;
        D_80080B10 = 0;
        D_80081530 = gameWork.unk_004;
    }

    row_step = (s32)(state->field_A + 1) >> 1;
    col_step = state->field_B + 1;

    if ((s32)(D_80080B12 + col_step) >= 0x100) {
        D_80080B10 = D_80080B10 + D_80080B14;
        D_80080B12 = 0;
    }

    if ((s32)(D_80080B10 + row_step) >= 0x20) {
        D_80080B10 = 0;
        D_80080B12 = 0;
        D_80080B14 = 0;
    }

    state->field_8 = (s8)(D_80080B10 << 1);
    state->field_9 = (u8)D_80080B12;

    if ((s32)D_80080B14 < row_step) {
        D_80080B14 = (u16)row_step;
    }

    D_80080B12 = D_80080B12 + col_step;
}
