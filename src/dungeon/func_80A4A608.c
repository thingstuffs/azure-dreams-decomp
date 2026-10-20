#include "modules/dungeon_resource06_slot0.h"

s32 func_80173E08(void *initial_payload, s32 entry_data, R06_80173E08_Entry *entry, s32 unused)
{
    void *payload = initial_payload;
    R06_80173E08_Scratchpad *scratch = (R06_80173E08_Scratchpad *)0x1F800000;
    R06_80173E08_Entry *next_entry;

    for (;;) {
        scratch->value = ((s16 *)D_8017591C)[0];

        if (!(entry->unk14 & 0x80)) {
            project_sprite_commands(payload, entry_data, entry,(s16)(entry->unk06));
        }

        next_entry = *(R06_80173E08_Entry **)((u8 *)payload - 8);
        if (next_entry == 0) {
            return 0;
        }
        payload = (u8 *)next_entry + 0x20;
        entry_data = (s32)next_entry->unk08;
        entry = next_entry->unk0C;
    }
}

/* MECHANISM: Typed page and scratch fields preserve the signed lh/sw widths and offsets. */
