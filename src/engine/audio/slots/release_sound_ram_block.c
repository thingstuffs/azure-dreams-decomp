#include "common.h"
#include "engine/audio/slots.h"
#include "engine/util.h"
#include "engine/audio/ram_block.h"

/*
 * Removes the first matching address from audio_ram_blocks, shifts subsequent records through the
 * zero terminator, and sorts the remaining entries.
 */
void release_sound_ram_block(u32 addr)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        if (audio_ram_blocks[i].address.u == addr) {
            for (; i < 16; i++) {
                audio_ram_blocks[i].size = audio_ram_blocks[i + 1].size;
                audio_ram_blocks[i].address.u = audio_ram_blocks[i + 1].address.u;
                if (audio_ram_blocks[i].address.u == 0) {
                    break;
                }
            }
            sort_entries_by_key();
            return;
        }
    }
}
