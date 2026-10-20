#include "modules/dungeon_resource10_slot0.h"

s32 func_80174BE4(void *initial_payload, s32 entry_data, R10_80174BE4_Entry *entry, s32 unused)
{
    void *payload = initial_payload;
    R10_80174BE4_Scratchpad *scratch = (R10_80174BE4_Scratchpad *)0x1F800000;
    R10_80174BE4_Entry *next_entry;

    for (;;) {
        scratch->value = ((s16 *)D_80175A18)[0];

        if (!(entry->unk14 & 0x80)) {
            project_sprite_commands(payload, entry_data, entry,(s16)(entry->unk06));
        }

        next_entry = *(R10_80174BE4_Entry **)((u8 *)payload - 8);
        if (next_entry == 0) {
            return 0;
        }
        payload = (u8 *)next_entry + 0x20;
        entry_data = (s32)next_entry->unk08;
        entry = next_entry->unk0C;
    }
}

/* MECHANISM: Typed page and scratch fields preserve the signed lh/sw widths and offsets. */
