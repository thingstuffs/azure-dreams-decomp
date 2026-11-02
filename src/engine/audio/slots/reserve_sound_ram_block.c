#include "common.h"
#include "engine/audio/slots.h"
#include "engine/util.h"
#include "slus/data.h"
#include "engine/audio/ram_block.h"

extern s8 sound_ram_reserve_mode[9];

/* Register or resize a memory block at the requested address. */
s32 reserve_sound_ram_block(u32 addr, s32 size)
{
    SoundRamBlock *block;
    SoundRamBlock *next_block;
    s32 slot;
    s32 next_slot;
    u32 block_addr;
    u32 next_addr;

    if ((u32)(addr - 0x1010) > 0x7EFEF) {
        return -1;
    }
    if (addr + size > 0x7FFFF) {
        return -1;
    }
    block = audio_ram_blocks;
    if (audio_ram_blocks[0].address.u == 0) {
        if (addr + size < (u32)(0x80000 - sound_ram_reserved_sizes[*(u8 *)sound_ram_reserve_mode])) {
            audio_ram_blocks[0].address.u = addr;
            block->size = size;
            sort_entries_by_key();
            return addr;
        }
        return -1;
    }
    for (slot = 0; slot < 16; slot++, block++) {
        if (slot == 0) {
            next_addr = audio_ram_blocks[0].address.u;
            if (addr < next_addr) {
                if (next_addr < size + addr) {
                    return -1;
                }
                for (; slot < 16; slot++) {
                    if (audio_ram_blocks[slot].size == 0) {
                        goto insert_first;
                    }
                }
                goto check_slot;
insert_first:
                audio_ram_blocks[slot].address.u = addr;
                audio_ram_blocks[slot].size = size;
                goto check_slot;
            }
        } else if (addr < block->address.u) {
            continue;
        }
        block_addr = block->address.u;
        if (block_addr == addr) {
            block->address.u = addr;
            block->size = size;
            return addr;
        }
        next_slot = slot + 1;
        next_block = &audio_ram_blocks[next_slot];
        if (next_block->size == 0) {
            if (size + addr < (u32)(0x80000 - sound_ram_reserved_sizes[*(u8 *)sound_ram_reserve_mode])) {
                next_block->address.u = addr;
                next_block->size = size;
                break;
            }
            return -1;
        }
        if (block_addr >= addr) {
            continue;
        }
        next_addr = next_block->address.u;
        if (addr >= next_addr) {
            continue;
        }
        if (addr < block_addr + block->size) {
            return -1;
        }
        if ((s32)next_addr < (s32)(addr + size)) {
            return -1;
        }
        for (; slot < 16; slot++) {
            if (audio_ram_blocks[slot].size == 0) {
                audio_ram_blocks[slot].address.u = addr;
                audio_ram_blocks[slot].size = size;
                break;
            }
        }
check_slot:
        if (slot != 16) {
            break;
        }
        return -1;
    }

    sort_entries_by_key();
    return addr;
}
