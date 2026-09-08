#include "common.h"

extern void bzero(void *dst, int n);
extern void *func_8004B404(u32 size);
extern s32 allocBufferArray(s32 *a0, s32 a1);
extern void func_8004CC38(s32 *a0, s32 a1);

/* Rebuilds the pointer buffer and links corresponding records from two sub-buffer banks. */
s32 *reallocField0Buffer(s32 *buffer_slot, s32 entry_count, s32 clear_words)
{
    s32 *entries;
    s32 *bank_slot;
    s32 bank_base;
    s32 bank_bases[32];

    bzero((void *) buffer_slot[0], clear_words * 4);
    entries = (s32 *) func_8004B404(0x104);
    buffer_slot[0] = (s32) entries;
    buffer_slot += 1;
    if (entries == 0)
        goto done;
    if (allocBufferArray(buffer_slot, (s32)((u32) entry_count >> 4) + 1) == 0)
        goto fail;
    if (*(volatile s32 *) buffer_slot != 0) {
        bank_slot = bank_bases;
        bank_base = *buffer_slot;
        do {
            buffer_slot++;
            *bank_slot = bank_base;
            bank_base = *buffer_slot;
            bank_slot++;
        } while (bank_base != 0);
    }
    if (allocBufferArray(buffer_slot, (s32)((u32) entry_count >> 4) + 1) != 0)
        goto cont;
fail:
    entries = 0;
    goto done;
cont:
    if (*(volatile s32 *) buffer_slot != 0) {
        bank_slot = bank_bases;
        bank_base = *buffer_slot;
        do {
            buffer_slot++;
            bank_slot[16] = bank_base;
            bank_base = *buffer_slot;
            bank_slot++;
        } while (bank_base != 0);
    }
    if (entry_count > 0) {
        s32 entry_index = 0;
        s32 *banks = bank_bases;
        s32 *entry_slot = entries;
        s32 *record;
        do {
            s32 bank_index = (u32) entry_index >> 4;
            s32 record_offset = (entry_index & 0xF) << 4;
            entry_index++;
            record = (s32 *)(banks[bank_index] + record_offset);
            *entry_slot = (s32) record;
            record[1] = banks[bank_index + 16] + record_offset;
            entry_slot++;
        } while (entry_index < entry_count);
    }
    func_8004CC38(entries, entry_count);
done:
    return entries;
}
