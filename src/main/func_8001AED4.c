#include "common.h"

extern s32 D_8009DDD8[][32];

void func_80401ED4(s32 arg0, void *arg1) {
    s32 *entry;

    entry = D_8009DDD8[arg0];
    memcpy(entry, (u8 *)arg1 + 0x200, 0x80);
    D_8009DDD8[arg0][0] = 1;
}
