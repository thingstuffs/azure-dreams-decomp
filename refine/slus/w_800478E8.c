#include "common.h"

#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct S_Entry {
    u8 flags;
    u8 pad[0xB];
} S_Entry;

/* Set the value of active entries with the matching ID in type-2 table slots. */
void func_800478E8(void *owner, s32 value, s32 entry_id) {
    u32 slot_addr;
    S_Entry *entry;
    void *table;
    void *entry_value;
    void *slot_entries;
    s32 list_type;

    table = *M2C_FIELD(owner, void ***, 0x28);
    slot_addr = M2C_FIELD(table, s32 *, 0) + (M2C_FIELD(table, s32 *, 4) * 4);
    if (slot_addr < (u32)M2C_FIELD(table, u32 *, 8)) {
        list_type = 2;
        slot_entries = (void *)(slot_addr + 4);
    process_slot:
        if (M2C_FIELD(slot_entries, s16 *, -2) == list_type) {
            entry = M2C_FIELD(slot_entries, S_Entry **, 0);
            entry_value = (s8 *)entry + 8;
            do {
                if ((entry->flags & 0x20) && (M2C_FIELD(entry_value, s16 *, -2) == entry_id)) {
                    M2C_FIELD(entry_value, s32 *, 0) = value;
                }
                entry_value = (s8 *)entry_value + 0xC;
            } while (!((entry++)->flags & 0x80));
        }
        {
            void *current_table = *M2C_FIELD(owner, void ***, 0x28);
            u32 table_end = (u32)M2C_FIELD(current_table, u32 *, 8);
            slot_entries = (s8 *)slot_entries + 8;
            slot_addr += 8;
            if (slot_addr < table_end) {
                goto process_slot;
            }
        }
    }
}
