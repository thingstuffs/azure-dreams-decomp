#include "common.h"

typedef struct Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} Entry;

typedef struct {
    u8 pad[0x13C];
    s32 value;
} Scratchpad;

typedef struct {
    u8 pad[0x5218];
    s16 value;
} GlobalPage;

extern s16 D_80175218[];
extern void project_sprite_commands(void *, s32, Entry *, s16);

/* Process linked entries whose 0x80 flag is clear, refreshing scratch state for each. */
/* Projects visible entries in the linked sprite chain using the current transition depth adjustment. */
s32 update_actor_state_after_map_check(void *initial_payload, s32 entry_data, Entry *entry, s32 unused)
{
    void *payload = initial_payload;
    Scratchpad *scratch = (Scratchpad *)0x1F800000;
    Entry *next_entry;

    for (;;) {
        scratch->value = D_80175218[0];

        if (!(entry->unk14 & 0x80)) {
            project_sprite_commands(payload, entry_data, entry, entry->unk06);
        }

        next_entry = *(Entry **)((u8 *)payload - 8);
        if (next_entry == 0) {
            return 0;
        }
        payload = (u8 *)next_entry + 0x20;
        entry_data = (s32)next_entry->unk08;
        entry = next_entry->unk0C;
    }
}

/* MECHANISM: Typed page and scratch fields preserve the signed lh/sw widths and offsets. */
