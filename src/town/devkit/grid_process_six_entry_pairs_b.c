#include "common.h"

extern void func_807006FC(u16);
extern u8 devkit_overlay_page[];

/* Pass six consecutive pairs of 16-bit table values to func_807006FC. */
void grid_process_six_entry_pairs_b(void) {
    s32 pair_offset;

    for (pair_offset = 4; pair_offset < 0x1C; pair_offset += 4) {
        func_807006FC(*(u16 *)(devkit_overlay_page + pair_offset + 0x9DC));
        func_807006FC(*(u16 *)(devkit_overlay_page + pair_offset + 0x9DE));
    }
}
