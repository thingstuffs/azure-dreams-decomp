#include "modules/dungeon_resource16_slot0.h"

s32 func_801736AC(void *initial_payload, s32 entry_data, R16_801736AC_Entry *entry, s32 unused)
{
    void *payload = initial_payload;
    R16_801736AC_Scratchpad *scratch = (R16_801736AC_Scratchpad *)0x1F800000;
    R16_801736AC_Entry *next_entry;

    for (;;) {
        scratch->value = ((s16 *)D_801742E0)[0];

        if (!(entry->unk14 & 0x80)) {
            func_800453E0(payload, entry_data, entry,(s16)(entry->unk06));
        }

        next_entry = *(R16_801736AC_Entry **)((u8 *)payload - 8);
        if (next_entry == 0) {
            return 0;
        }
        payload = (u8 *)next_entry + 0x20;
        entry_data = (s32)next_entry->unk08;
        entry = next_entry->unk0C;
    }
}

/* MECHANISM: Typed page and scratch fields preserve the signed lh/sw widths and offsets.
   ASM_KEEP breaks absolute-page constant folding; the guarded s1 page pin plus kept
   scratch base preserves the retail 0x20-frame save/init order s0, s2, s1, ra. */
