#include "common.h"

#include "common.h"

typedef struct S_Entry {
    u8 flags;
    u8 pad_01[5];
    s16 unk_06;
    s32 unk_08;
} S_Entry;

typedef struct S_800478E8_0 {
    u8 pad_00[0x28];
    void *unk_28;
} S_800478E8_0;

typedef struct S_800478E8_1 {
    s32 unk_00;
    s32 unk_04;
    u32 unk_08;
} S_800478E8_1;

typedef struct S_800478E8_2 {
    u8 pad_00[2];
    s16 unk_02;
    S_Entry *unk_04;
} S_800478E8_2;

/* Set the value of active entries with the matching ID in type-2 table slots. */
void func_800478E8(S_800478E8_0 *owner, s32 value, s32 entry_id) {
    u32 slot_addr;
    S_Entry *entry;
    S_800478E8_1 *table;
    void *entry_value;
    void *slot_entries;
    s32 list_type;

    table = *(void **)owner->unk_28;
    slot_addr = table->unk_00 + (table->unk_04 * 4);
    if (slot_addr < (u32)table->unk_08) {
        list_type = 2;
        slot_entries = (void *)(slot_addr + 4);
    process_slot:
        if (((S_800478E8_2 *)((u8 *)slot_entries - 4))->unk_02 == list_type) {
            entry = ((S_800478E8_2 *)((u8 *)slot_entries - 4))->unk_04;
            entry_value = (s8 *)entry + 8;
            do {
                if ((entry->flags & 0x20) && (((S_Entry *)((u8 *)entry_value - 8))->unk_06 == entry_id)) {
                    ((S_Entry *)((u8 *)entry_value - 8))->unk_08 = value;
                }
                entry_value = (s8 *)entry_value + 0xC;
            } while (!((entry++)->flags & 0x80));
        }
        {
            S_800478E8_1 *current_table = *(void **)owner->unk_28;
            u32 table_end = (u32)current_table->unk_08;
            slot_entries = (s8 *)slot_entries + 8;
            slot_addr += 8;
            if (slot_addr < table_end) {
                goto process_slot;
            }
        }
    }
}
