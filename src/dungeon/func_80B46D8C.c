#include "modules/dungeon_resource12_slot0.h"

s32 func_8017458C(void *initial_payload, s32 entry_data, R12_8017458C_Entry *entry, s32 unused)
{
    void *payload = initial_payload;
    R12_8017458C_Scratchpad *scratch = (R12_8017458C_Scratchpad *)0x1F800000;
    R12_8017458C_Entry *next_entry;

    for (;;) {
        scratch->value = ((s16 *)D_80175B20)[0];

        if (!(entry->unk14 & 0x80)) {
            project_sprite_commands(payload, entry_data, entry,(s16)(entry->unk06));
        }

        next_entry = *(R12_8017458C_Entry **)((u8 *)payload - 8);
        if (next_entry == 0) {
            return 0;
        }
        payload = (u8 *)next_entry + 0x20;
        entry_data = (s32)next_entry->unk08;
        entry = next_entry->unk0C;
    }
}

/* MECHANISM: Typed page and scratch fields preserve the signed lh/sw widths and offsets. */
