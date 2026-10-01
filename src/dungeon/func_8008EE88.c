#include "common.h"

typedef struct { u8 bytes[4]; } WordCopy;

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
    s32 slot_index;
    u8 *src_cursor;

    state = input_state;
    func_800422DC((void *)0x80012194, state);

    {
        s32 record_index;
        u8 entry_flags;
        u8 *entry_flags_ptr;
        s32 *record_table;
        u8 *record_buffer;
        Blob140 *copy_src;
        Blob140 *copy_dst;
        unsigned long record_offset;
        s32 *record_slot;

        slot_index = 0x13;
        record_table = D_800E3DF0;
        record_buffer = D_800E3E48;
        entry_flags_ptr = (u8 *)0x8001024B;
        do {
            if (entry_flags_ptr[-2] == 0x13) {
                entry_flags = entry_flags_ptr[0];
                if ((entry_flags & 0x20) != 0) {
                    record_index = entry_flags & 0x1F;
                    src_cursor = (u8 *)record_table[record_index];
                    if ((func_80042900(src_cursor, 0xA) << 0x10) != 0) {
                        src_cursor[0x13] = src_cursor[0xA8];
                    }
                    record_offset = record_index * 0x8C;
                    copy_dst = (Blob140 *)(record_offset + (unsigned long)record_buffer);
                    copy_src = (Blob140 *)src_cursor;
                    *copy_dst = *copy_src;
                    record_slot = (s32 *)((record_index << 2) + (unsigned long)record_table);
                    *record_slot = (s32)((record_index * 0x8C) + (unsigned long)record_buffer);
                }
            }
            slot_index -= 1;
            entry_flags_ptr += 4;
        } while (slot_index >= 0);
    }

    {
        u8 *globals;

        globals = (u8 *)0x80010000;
        slot_index = 0x13;
        do {
            ((WordCopy *)(globals + 0x21E8))[slot_index] = ((WordCopy *)(globals + 0x248))[slot_index];
            (globals + 0x2238)[slot_index] = func_800422A8(((s32 *)(globals + 0x29C))[slot_index], (void *)0x80010248, 4, 0x14);
            ((Blob140 *)(globals + 0x2260))[slot_index] = ((Blob140 *)D_800E3E48)[slot_index];
            (globals + 0x224C)[slot_index] = func_800422A8(D_800E3DF0[slot_index], D_800E3E48, 0x8C, 0x14);
            slot_index -= 1;
        } while (slot_index >= 0);
    }

    {
        u8 *src_cursor;
        u8 *index_cursor;

        slot_index = 1;
        index_cursor = (u8 *)0x80010000;
        src_cursor = (u8 *)state;
        src_cursor += 4;
        do {
            index_cursor[slot_index + 0x2D52] = func_800422A8(*(s32 *)(src_cursor + 0xD0), (void *)0x80010248, 4, 0x14);
            src_cursor -= 4;
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
