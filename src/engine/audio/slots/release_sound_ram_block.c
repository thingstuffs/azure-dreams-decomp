#include "common.h"

typedef struct {
    /* 0x00 */ u32 addr;
    /* 0x04 */ s32 size;
} S_800869C0;

extern S_800869C0 D_800869C0[16];
extern void sort_entries_by_key(void);

/* Removes the first matching entry from D_800869C0, shifts later entries down, and calls sort_entries_by_key. */
void release_sound_ram_block(u32 addr)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        if (D_800869C0[i].addr == addr) {
            for (; i < 16; i++) {
                D_800869C0[i].size = D_800869C0[i + 1].size;
                D_800869C0[i].addr = D_800869C0[i + 1].addr;
                if (D_800869C0[i].addr == 0) {
                    break;
                }
            }
            sort_entries_by_key();
            return;
        }
    }
}
