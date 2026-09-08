#include "common.h"

extern s32 D_8009DDD8[][32];

/* Copy 128 bytes from the source's offset 0x200 into an entry and mark it active. */
void func_80401ED4(s32 entry_index, void *source) {
    s32 *entry;

    entry = D_8009DDD8[entry_index];
    memcpy(entry, (u8 *)source + 0x200, 0x80);
    D_8009DDD8[entry_index][0] = 1;
}
