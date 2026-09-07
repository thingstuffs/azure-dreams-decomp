#include "common.h"

extern void func_807006FC(u16);
extern u8 D_A0700000[];

void func_808B9488(void) {
    s32 i;

    for (i = 4; i < 0x1C; i += 4) {
        func_807006FC(*(u16 *)(D_A0700000 + i + 0x9DC));
        func_807006FC(*(u16 *)(D_A0700000 + i + 0x9DE));
    }
}
