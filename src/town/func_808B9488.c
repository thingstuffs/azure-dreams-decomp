#include "common.h"

extern void func_807006FC(u16);
extern u8 D_A0700000[];

/* Pass six consecutive pairs of 16-bit table values to func_807006FC. */
void func_808B9488(void) {
    s32 pair_offset;

    for (pair_offset = 4; pair_offset < 0x1C; pair_offset += 4) {
        func_807006FC(*(u16 *)(D_A0700000 + pair_offset + 0x9DC));
        func_807006FC(*(u16 *)(D_A0700000 + pair_offset + 0x9DE));
    }
}
