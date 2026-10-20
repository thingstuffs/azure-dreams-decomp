#include "common.h"

typedef struct {
    /* 0x00 */ u32 addr;
    /* 0x04 */ s32 size;
} S_800869C0;

extern S_800869C0 audio_ram_blocks[16];
extern s8 sound_ram_reserve_mode[9];
extern s32 sound_ram_reserved_sizes[9];
extern void sort_entries_by_key(void);

/* Register or resize a memory block at the requested address. */
s32 reserve_sound_ram_block(u32 addr, s32 size)
{
    S_800869C0 *block;
    S_800869C0 *next_block;
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
    if (audio_ram_blocks[0].addr == 0) {
        if (addr + size < (u32)(0x80000 - sound_ram_reserved_sizes[*(u8 *)sound_ram_reserve_mode])) {
            audio_ram_blocks[0].addr = addr;
            block->size = size;
            sort_entries_by_key();
            return addr;
        }
        return -1;
    }
    for (slot = 0; slot < 16; slot++, block++) {
        if (slot == 0) {
            next_addr = audio_ram_blocks[0].addr;
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
                audio_ram_blocks[slot].addr = addr;
                audio_ram_blocks[slot].size = size;
                goto check_slot;
            }
        } else if (addr < block->addr) {
            continue;
        }
        block_addr = block->addr;
        if (block_addr == addr) {
            block->addr = addr;
            block->size = size;
            return addr;
        }
        next_slot = slot + 1;
        next_block = &audio_ram_blocks[next_slot];
        if (next_block->size == 0) {
            if (size + addr < (u32)(0x80000 - sound_ram_reserved_sizes[*(u8 *)sound_ram_reserve_mode])) {
                next_block->addr = addr;
                next_block->size = size;
                break;
            }
            return -1;
        }
        if (block_addr >= addr) {
            continue;
        }
        next_addr = next_block->addr;
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
                audio_ram_blocks[slot].addr = addr;
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
