#include "common.h"

typedef struct {
    u8 pad[0x13];
    u8 f13;
} S_D_8006DE24;

extern S_D_8006DE24 D_8006DE24[];

u8 func_800A35A4(s32 arg0, s32 arg1) {
    S_D_8006DE24 *base = D_8006DE24;

    arg0 = arg0 + arg1 * 3;
    return base[*(u8 *)(arg0 + 8)].f13;
}
