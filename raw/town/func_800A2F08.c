#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern s32 func_800A069C();

s32 func_800A0668(void *arg0) {
    if (FIELD(FIELD(arg0, void *, 0x98), u8, 1) & 8) {
        return FIELD(arg0, u8, 0x95) == 0;
    }
    (void)(*(volatile u8 *)((u8 *)arg0 + 0x95) != 0);
    return func_800A069C() != 0;
}
