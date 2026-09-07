#include "common.h"

extern void func_8004E264(void *a0, s32 a1);

/* Process 12-byte entries through the entry whose first byte has bit 0x80 set. */
void func_8004E884(u8 *entries, s32 processArg)
{
    u8 *entry = entries;
    s32 entryProcessArg = processArg;

    if (entry != 0) {
        do {
            func_8004E264(entry, entryProcessArg);
            if (*entry & 0x80) {
                break;
            }
            entry = entry + 0xC;
        } while (1);
    }
}
