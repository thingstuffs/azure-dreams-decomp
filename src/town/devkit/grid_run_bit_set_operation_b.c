#include "common.h"

extern s32 func_807006AC();
extern s32 devkit_overlay_page[];


/* Call func_807006AC when the selected grid entry has bit 0 set. */
void grid_run_bit_set_operation_b(s32 row, s32 column) {
    if (*(s32 *)((s8 *)devkit_overlay_page + ((((row * 7) + column) * 8)) + 0xA08) & 1) {
        func_807006AC(0x152);
    }
}
