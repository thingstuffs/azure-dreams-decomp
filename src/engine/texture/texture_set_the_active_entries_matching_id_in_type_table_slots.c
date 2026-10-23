#include "common.h"

#include "common.h"
#include "engine/texture.h"

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

/*
 * Walks type-two table slots and their 12-byte nodes through flag 0x80, replacing the value only
 * for nodes with flag 0x20 and the requested ID.
 */
void texture_set_the_active_entries_matching_id_in_type_n_2_table_slots(S_800478E8_0 *owner, s32 value, s32 entry_id) {
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
        do {
            if (((S_800478E8_2 *)((u8 *)slot_entries - 4))->unk_02 == list_type) {
                entry = ((S_800478E8_2 *)((u8 *)slot_entries - 4))->unk_04;
                entry_value = &entry->unk_08;
                do {
                    if ((entry->flags & 0x20) && (((S_Entry *)((u8 *)entry_value - 8))->unk_06 == entry_id)) {
                        ((S_Entry *)((u8 *)entry_value - 8))->unk_08 = value;
                    }
                    entry_value = (s8 *)entry_value + 0xC;
                } while (!((entry++)->flags & 0x80));
            }
            slot_entries = (s8 *)slot_entries + 8;
            slot_addr += 8;
        } while (slot_addr < (u32)((S_800478E8_1 *)*(void **)owner->unk_28)->unk_08);
    }
}
