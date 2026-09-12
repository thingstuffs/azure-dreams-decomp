#include "common.h"

extern s32 func_800BCB04(u16, u16, s16, void *);
extern void *D_800814A8[3];
extern u8 D_8008333C[32];
extern u8 D_800EA000[];

/* Rounds the sampled or fallback height up to a 64-unit boundary relative to the cell height. */
s16 func_800D175C(s32 grid_x, s32 grid_y)
{
    u8 *grid_info;
    u8 *state;
    u8 *cell_table;
    u16 cell_height;
    s32 height;
    s32 biased_height;

    grid_info = D_8008333C;
    state = grid_info - 0x1C4;
    cell_table = D_800EA000;
    grid_y = (s16)grid_y;
    grid_x = (s16)grid_x;
    ASM_KEEP(grid_info);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    cell_height = *(u16 *)(cell_table +
        ((grid_y << *(s16 *)(grid_info + 0x14)) + grid_x) * 6 + 2);
    height = func_800BCB04(*(u16 *)(state + 0xA4),
                           *(u16 *)(state + 0xA6),
                           (s16)(*(u16 *)(state + 0xA8) - 0x20),
                           state);
    if ((s16)height < 0x201) {
        biased_height = height + 0x3F;
    } else {
        cell_table = *(u16 *)((u8 *)D_800814A8[0] + 0x88);
        biased_height = cell_table + 0x3F;
    }
    return (s16)(((cell_height + biased_height) & -0x40) - cell_height);
}

