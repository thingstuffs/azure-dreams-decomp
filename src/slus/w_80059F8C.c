#include "common.h"

typedef struct {
    /* 0x00 */ u32 addr;
    /* 0x04 */ s32 size;
} S_800869C0;

extern S_800869C0 D_800869C0[16];
extern u8 D_8007382B;
extern s32 D_80073830[9];
extern void func_80059DAC(void);

/* Register or resize a memory block at the requested address. */
s32 func_80059F8C(u32 addr, s32 size)
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
    block = D_800869C0;
    if (D_800869C0[0].addr == 0) {
        if (addr + size < (u32)(0x80000 - D_80073830[D_8007382B])) {
            D_800869C0[0].addr = addr;
            block->size = size;
            func_80059DAC();
            return addr;
        }
        return -1;
    }
    for (slot = 0; slot < 16; slot++, block++) {
        if (slot == 0) {
            next_addr = D_800869C0[0].addr;
            if (addr < next_addr) {
                if (next_addr < size + addr) {
                    return -1;
                }
                for (; slot < 16; slot++) {
                    if (D_800869C0[slot].size == 0) {
                        goto insert_first;
                    }
                }
                goto check_slot;
insert_first:
                D_800869C0[slot].addr = addr;
                D_800869C0[slot].size = size;
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
        next_block = &D_800869C0[next_slot];
        if (next_block->size == 0) {
            if (size + addr < (u32)(0x80000 - D_80073830[D_8007382B])) {
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
            if (D_800869C0[slot].size == 0) {
                D_800869C0[slot].addr = addr;
                D_800869C0[slot].size = size;
                break;
            }
        }
check_slot:
        if (slot != 16) {
            break;
        }
        return -1;
    }

    func_80059DAC();
    return addr;
}
