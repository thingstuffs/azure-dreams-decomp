#include "common.h"

typedef struct __attribute__((packed)) {
    u8 pad0000[0x248];
    u32 copy_src;
    u8 pad024c[0x21E8 - 0x24C];
    u32 copy_dst;
} Global1004C;

typedef struct {
    u32 word[35];
} Blob140;

extern s32 D_800E3DF0[];
extern u8 D_800E3E48[];

extern void func_800422DC(void *, void *);
extern s8 func_800422A8(s32, void *, s32, s32);
extern s32 func_80042900(void *, s32);
extern void func_800A9160(u16);

/* Snapshot records and state fields, converting stored pointers to table indices. */
void func_800945E8(void *input_state) {
    void *state;

    state = input_state;
    func_800422DC((void *)0x80012194, state);

    {
        s32 slot_index;
        s32 record_index;
        u8 entry_flags;
        register u8 *entry_flags_ptr ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
        register u8 *record ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
        s32 *record_table;
        u8 *record_buffer;
        Blob140 *copy_src;
        Blob140 *copy_dst;
        u8 *buffer_addr;
        unsigned long record_offset;
        s32 *record_slot;

        slot_index = 0x13;
        buffer_addr = (u8 *)0x800E0000;
        ASM_KEEP_NV(buffer_addr);   /* MATCH pin: load-bearing for the whole function shape */
        record_table = (s32 *)(buffer_addr + 0x3DF0);
        buffer_addr = (u8 *)0x800E0000;
        ASM_KEEP_NV(buffer_addr);   /* MATCH pin: load-bearing for the whole function shape */
        record_buffer = buffer_addr + 0x3E48;
        entry_flags_ptr = (u8 *)0x8001024B;
        do {
            if (entry_flags_ptr[-2] == 0x13) {
                entry_flags = entry_flags_ptr[0];
                if ((entry_flags & 0x20) != 0) {
                    record_index = entry_flags & 0x1F;
                    record = (u8 *)record_table[record_index];
                    if ((func_80042900(record, 0xA) << 0x10) != 0) {
                        record[0x13] = record[0xA8];
                    }
                    record_offset = record_index * 0x8C;
                    copy_dst = (Blob140 *)(record_offset + (unsigned long)record_buffer);
                    copy_src = (Blob140 *)record;
                    ASM_KEEP_NV(copy_dst);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    ASM_KEEP_NV(copy_src);   /* MATCH pin: retail address form (%hi/%lo vs base+record_offset) depends on it */
                    {
                        u32 *copy_src_cursor = copy_src->word;
                        volatile u32 *copy_dst_cursor = copy_dst->word;
                        u32 *copy_end = copy_src_cursor + 32;

                        do {
                            u32 copy_word0 = copy_src_cursor[0];
                            u32 copy_word1 = copy_src_cursor[1];
                            u32 copy_word2 = copy_src_cursor[2];
                            u32 copy_word3 = copy_src_cursor[3];

                            copy_dst_cursor[0] = copy_word0;
                            copy_dst_cursor[1] = copy_word1;
                            copy_dst_cursor[2] = copy_word2;
                            copy_dst_cursor[3] = copy_word3;
                            ASM_MEM_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                            copy_src_cursor += 4;
                            copy_dst_cursor += 4;
                        } while (copy_src_cursor != copy_end);

                        {
                            u32 copy_word0 = copy_src_cursor[0];
                            u32 copy_word1 = copy_src_cursor[1];
                            u32 copy_word2 = copy_src_cursor[2];

                            copy_dst_cursor[0] = copy_word0;
                            copy_dst_cursor[1] = copy_word1;
                            copy_dst_cursor[2] = copy_word2;
                        }
                    }
                    ASM_KEEP(record_index);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                    record_slot = (s32 *)((record_index << 2) + (unsigned long)record_table);
                    record_offset = record_index * 0x8C;
                    ASM_KEEP_NV(record_slot);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    *record_slot = (s32)(record_offset + (unsigned long)record_buffer);
                }
            }
            ASM_KEEP(slot_index);   /* MATCH pin: load-bearing for the whole function shape */
            ASM_KEEP(entry_flags_ptr);   /* MATCH pin: load-bearing for the whole function shape */
            slot_index -= 1;
            entry_flags_ptr += 4;
        } while (slot_index >= 0);
    }

    {
        s32 slot_index;
        register s32 *record_slot ASM_REG("$21");   /* MATCH pin: retail register colouring depends on it */
        u8 *src_cursor;
        register u8 *dst_cursor ASM_REG("$20");   /* MATCH pin: keeps a constant in a register as retail does */
        register u8 *index_cursor ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
        Global1004C *slot_fields;
        register u8 *buffer_page ASM_REG("$23");   /* MATCH pin: retail address form (%hi/%lo vs base+record_offset) depends on it */
        Blob140 *copy_src;
        Blob140 *copy_dst;
        u8 *buffer_addr;
        s32 lookup_ptr;
        void *lookup_base;
        s32 entry_size;
        s32 entry_count;

        slot_index = 0x13;
        index_cursor = (u8 *)0x80010013;
        buffer_addr = (u8 *)0x800E0000;
        ASM_KEEP_NV(buffer_addr);   /* MATCH pin: load-bearing for the whole function shape */
        buffer_addr += 0x3DF0;
        ASM_KEEP_NV(buffer_addr);   /* MATCH pin: load-bearing for the whole function shape */
        record_slot = (s32 *)buffer_addr + 0x13;
        buffer_page = (u8 *)0x800E0000;
        ASM_KEEP_NV(buffer_page);   /* MATCH pin: keeps a constant in a register as retail does */
        buffer_addr = buffer_page + 0x3E48;
        ASM_KEEP_NV(buffer_addr);   /* MATCH pin: load-bearing for the whole function shape */
        src_cursor = buffer_addr + 0xA64;
        dst_cursor = (u8 *)0x80010A64;
        slot_fields = (Global1004C *)0x8001004C;
        do {
            slot_fields->copy_dst = slot_fields->copy_src;
            ASM_SET(lookup_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            lookup_base = (void *)0x80010248;
            entry_size = 4;
            lookup_ptr = *(s32 *)((u8 *)slot_fields + 0x29C);
            entry_count = 0x14;
            index_cursor[0x2238] = func_800422A8(lookup_ptr, lookup_base, entry_size, entry_count);
            copy_dst = (Blob140 *)(dst_cursor + 0x2260);
            copy_src = (Blob140 *)src_cursor;
            ASM_KEEP_NV(copy_dst);   /* MATCH pin: retail schedule: same instructions, different order without it */
            {
                u32 *copy_src_cursor = copy_src->word;
                volatile u32 *copy_dst_cursor = copy_dst->word;
                u32 *copy_end = (u32 *)(src_cursor + 0x80);

                do {
                    u32 copy_word0 = copy_src_cursor[0];
                    u32 copy_word1 = copy_src_cursor[1];
                    u32 copy_word2 = copy_src_cursor[2];
                    u32 copy_word3 = copy_src_cursor[3];

                    copy_dst_cursor[0] = copy_word0;
                    copy_dst_cursor[1] = copy_word1;
                    copy_dst_cursor[2] = copy_word2;
                    copy_dst_cursor[3] = copy_word3;
                    ASM_MEM_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                    copy_src_cursor += 4;
                    copy_dst_cursor += 4;
                } while (copy_src_cursor != copy_end);

                {
                    u32 copy_word0 = copy_src_cursor[0];
                    u32 copy_word1 = copy_src_cursor[1];
                    u32 copy_word2 = copy_src_cursor[2];

                    copy_dst_cursor[0] = copy_word0;
                    copy_dst_cursor[1] = copy_word1;
                    copy_dst_cursor[2] = copy_word2;
                }
            }
            ASM_KEEP(buffer_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
            ASM_KEEP(slot_index);   /* MATCH pin: load-bearing for the whole function shape */
            ASM_KEEP(record_slot);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            ASM_KEEP(src_cursor);   /* MATCH pin: load-bearing for the whole function shape */
            ASM_KEEP(dst_cursor);   /* MATCH pin: retail schedule: same instructions, different order without it */
            ASM_KEEP(slot_fields);   /* MATCH pin: keeps a statement from moving across a call/branch */
            lookup_base = buffer_page + 0x3E48;
            entry_size = 0x8C;
            entry_count = 0x14;
            lookup_ptr = *record_slot;
            ASM_KEEP4_NV(lookup_ptr, lookup_base, entry_size, entry_count);   /* MATCH pin: retail schedule: same instructions, different order without it */
            record_slot -= 1;
            src_cursor -= 0x8C;
            dst_cursor -= 0x8C;
            slot_fields = (Global1004C *)((u8 *)slot_fields - 4);
            slot_index -= 1;
            index_cursor[0x224C] = func_800422A8(lookup_ptr, lookup_base, entry_size, entry_count);
            ASM_KEEP(index_cursor);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            index_cursor -= 1;
        } while (slot_index >= 0);
    }

    {
        register s32 slot_index ASM_REG("$18");   /* MATCH pin: load-bearing for the whole function shape */
        register u8 *src_cursor ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
        u8 *index_cursor;
        s32 lookup_ptr;
        void *lookup_base;
        s32 entry_size;
        s32 entry_count;

        slot_index = 1;
        index_cursor = (u8 *)0x80010000;
        ASM_KEEP(state);   /* MATCH pin: keeps a constant in a register as retail does */
        src_cursor = (u8 *)state + 4;
        do {
            lookup_base = (void *)0x80010248;
            entry_size = 4;
            entry_count = 0x14;
            lookup_ptr = *(s32 *)(src_cursor + 0xD0);
            ASM_KEEP4_NV(lookup_ptr, lookup_base, entry_size, entry_count);   /* MATCH pin: retail schedule: same instructions, different order without it */
            src_cursor -= 4;
            index_cursor[slot_index + 0x2D52] = func_800422A8(lookup_ptr, lookup_base, entry_size, entry_count);
            slot_index -= 1;
        } while (slot_index >= 0);
    }

    {
        u8 *state_base;
        u32 field_value;
        u32 saved_setting;

        state_base = (u8 *)0x80010000;
        field_value = *(u16 *)(state_base + 0x3626);
        saved_setting = *(u16 *)(state_base + 0x209E);
        *(u16 *)(state_base + 0x3624) = field_value;
        *(u16 *)(state_base + 0x209C) = saved_setting;
        field_value = *(u16 *)((u8 *)state + 0xF8);
        *(u16 *)(state_base + 0x2D50) = field_value;
        field_value = *(s32 *)((u8 *)state + 0xFC);
        *(s32 *)(state_base + 0x2D58) = field_value;
        field_value = ((u8 *)state)[0xFA];
        state_base[0x2D6C] = field_value;
        field_value = ((u8 *)state)[0xFB];
        state_base[0x2D6D] = field_value;
        func_800A9160(saved_setting);
    }
}
