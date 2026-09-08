#include "common.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    u8 *unk4;
    u8 pad8[20];
} S_80086A40;

extern S_80086A40 D_80086A40[];

/* Copies an entry's 32-byte block to dst and returns 0, or returns -1 for an invalid slot. */
s32 func_8005B470(s16 idx, u8 *dst) {
    S_80086A40 *table;
    S_80086A40 *entry;
    u8 *src;
    u32 bytes_copied;

    table = D_80086A40;
    entry = &table[idx];
    if (entry->unk0 == -1) {
        return -1;
    }

    src = entry->unk4;
    bytes_copied = 0;
    do {
        *dst = *src;
        src++;
        bytes_copied++;
        dst++;
    } while (bytes_copied < 0x20);

    return 0;
}
