#include "common.h"
#include "engine/audio/slots.h"
#include "engine/util.h"

typedef struct {
    /* 0x00 */ u32 addr;
    /* 0x04 */ s32 size;
} S_800869C0;

extern S_800869C0 audio_ram_blocks[16];

/*
 * Removes the first matching address from audio_ram_blocks, shifts subsequent records through the
 * zero terminator, and sorts the remaining entries.
 */
void release_sound_ram_block(u32 addr)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        if (audio_ram_blocks[i].addr == addr) {
            for (; i < 16; i++) {
                audio_ram_blocks[i].size = audio_ram_blocks[i + 1].size;
                audio_ram_blocks[i].addr = audio_ram_blocks[i + 1].addr;
                if (audio_ram_blocks[i].addr == 0) {
                    break;
                }
            }
            sort_entries_by_key();
            return;
        }
    }
}
