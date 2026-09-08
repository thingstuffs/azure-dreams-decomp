#include "common.h"

typedef struct {
    s32 unk00;
    s32 unk04;
} S_800869C0;

extern S_800869C0 D_800869C0[16];
extern u8 D_8007382B[9];
extern s32 D_80073830[9];
extern void func_80059DAC(void);

/* Reserves space in the entry table and returns its offset, or -1 if it exceeds the limit. */
s32 func_80059E94(s32 size)
{
    s32 alloc_size;
    s32 offset;
    S_800869C0 *first_entry;
    s32 initial_end;
    s32 *reserve_sizes;
    s32 alloc_limit;
    s32 end_offset;
    S_800869C0 *entry;
    s32 reserved_size;
    s32 entry_index;
    u8 reserve_index;

    alloc_size = size;
    offset = 0x1010;
    first_entry = &D_800869C0[0];
    if (first_entry->unk00 != 0) {
        goto loop_start;
    }
    ASM_KEEP(offset);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    initial_end = alloc_size + 0x1010;
    {
        u8 initial_reserve_index = D_8007382B[0];
        s32 *initial_reserve_sizes = D_80073830;

        alloc_limit = 0x80000 - initial_reserve_sizes[initial_reserve_index];
    }
    if ((u32)initial_end >= (u32)alloc_limit) {
        return -1;
    }
    first_entry->unk00 = offset;
    first_entry->unk04 = alloc_size;
    goto tail;

found:
    entry->unk00 = end_offset;
    entry->unk04 = alloc_size;
    goto tail;

loop_start:
    {
        s32 memory_end;

        entry_index = 0;
        memory_end = 0x80000;
        entry = first_entry;
        reserve_index = D_8007382B[0];
        for (; 16 > entry_index; entry_index++, entry++) {
            if (entry->unk04 != 0) {
                continue;
            }
            reserved_size = (reserve_sizes = D_80073830)[reserve_index];
            offset = entry->unk00;
            end_offset = offset + alloc_size;
            if ((u32)end_offset >= (u32)(memory_end - reserved_size)) {
                return -1;
            }
            goto found;
        }
    }

tail:
    func_80059DAC();
    return offset;
}
