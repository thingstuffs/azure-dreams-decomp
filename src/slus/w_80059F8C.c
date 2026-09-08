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
    if (D_800869C0[0].addr != 0) {
        goto scan;
    }
    if (addr + size < (u32)(0x80000 - D_80073830[D_8007382B])) {
        D_800869C0[0].addr = addr;
        block->size = size;
        goto sort_return;
    }
    return -1;

update_block:
    block->addr = addr;
    block->size = size;
    return addr;

append_block:
    next_block->addr = addr;
    next_block->size = size;
    goto sort_return;

scan:
    slot = 0;
    do {
        if (slot != 0) {
            goto check_start;
        }
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
        goto check_gap;
check_start:
        if (addr < block->addr) {
            goto advance;
        }
check_gap:
        block_addr = block->addr;
        if (block_addr == addr) {
            goto update_block;
        }
        next_slot = slot + 1;
        next_block = &D_800869C0[next_slot];
        if (next_block->size == 0) {
            if (size + addr < (u32)(0x80000 - D_80073830[D_8007382B])) {
                goto append_block;
            }
            return -1;
        }
        if (block_addr >= addr) {
            goto advance;
        }
        next_addr = next_block->addr;
        if (addr >= next_addr) {
            goto advance;
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
            goto sort_return;
        }
        return -1;
advance:
        slot++;
        block++;
    } while (slot < 16);

sort_return:
    func_80059DAC();
    return addr;
}
