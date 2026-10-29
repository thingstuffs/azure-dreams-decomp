/* Apply pending values to flagged player records (G00577). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A8BC8, CL:town/func_800A8C3C, CL:town/func_800A8C68, PD:town/engine:80100E2C. */
#include "town/player/pending_record_values_g00577.h"
#include "town/player.h"

/* Looks up a table value using the signed low 16 bits of the index. */
TownRecord *lookup_signed_index_value(s32 index) {
    TownRecord **table = **D_80082EA8.p;
    index = (s16)index;
    return table[index];
}

/* Walks active records and writes the supplied value to +8 of each entry carrying flag 0x20. */
void set_flagged_record_values(TownRecord *record, s32 entryValue)
{
    s32 entryOffset;
    s32 lastEntryFlag;

    s32 i;

    for (i = 0; record[i].active != 0; i++) {
        entryOffset = 0;
        do {
            if (*(u32 *)(entryOffset + record[i].data) & 0x20) {
                *(s32 *)(entryOffset + record[i].data + 8) = entryValue;
            }
            lastEntryFlag = *(u8 *)(entryOffset + record[i].data) & 0x80;
            entryOffset += 12;
        } while (!lastEntryFlag);
    }
}

/* Resolve the low-byte index, apply its value, and clear the pending state. */
void apply_pending_indexed_value(s32 index, s32 value) {
    s32 *pending_state;
    set_flagged_record_values(lookup_signed_index_value(index & 0xFF), value);
    pending_state = D_80100E2C;
    *pending_state = 0;
}

/* Apply the table entry selected by the signed low-halfword index and clear pending state. */
void apply_pending_table_entry(s32 index, s32 entryValue) {
    s32 shifted_index = (s16)index;
    TownRecord **entries;
    entries = **loaded_town_resource_attributes;

    set_flagged_record_values(entries[shifted_index], entryValue);
    D_80100E2C[0] = 0;
}
