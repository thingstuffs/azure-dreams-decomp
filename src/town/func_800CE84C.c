#include "common.h"

typedef void (*TownCallback)(void);

extern TownCallback D_800D6B28[3];

void func_800CBFAC(void *arg0) {
    volatile TownCallback *table = D_800D6B28;
    s32 index = *(s16 *)((s8 *)arg0 + 0x68);
    table[index]();
}
