#include "common.h"

typedef struct EntryS_80047738 {
    /* 0x0 */ u16 unk00;
    /* 0x2 */ u16 pad02;
    /* 0x4 */ s32 unk04;
} EntryS_80047738; /* size 0x8 */

typedef struct S_80047738 {
    /* 0x00 */ EntryS_80047738 *unk00;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 pad05[3];
    /* 0x08 */ s32 unk08;
    /* 0x0C */ u8 pad0C[0x14 - 0x0C];
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8 pad16[0x28 - 0x16];
    /* 0x28 */ EntryS_80047738 ****unk28;
} S_80047738;

/* Selects and caches a table entry and its value, records its index, and clears flag 0x40. */
void func_80047738(S_80047738 *state, s16 table_index, s16 entry_index)
{
    EntryS_80047738 **entry_tables = **state->unk28;
    EntryS_80047738 *entry = entry_tables[table_index] + entry_index;

    state->unk00 = entry;
    state->unk08 = entry->unk04;
    state->unk04 = (u8)entry_index;
    state->unk14 &= 0xFFBF;
}
