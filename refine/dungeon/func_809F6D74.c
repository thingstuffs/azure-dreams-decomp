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
extern void func_800453E0(void *, s32, Entry *, s16);

/* Process linked entries whose 0x80 flag is clear, refreshing scratch state for each. */
s32 func_80174574(void *initial_payload, s32 entry_data, Entry *entry, s32 unused)
{
    void *payload = initial_payload;
    Scratchpad *scratch = (Scratchpad *)0x1F800000;
    GlobalPage *global_page =
        (GlobalPage *)0x80170000;
    Entry *next_entry;

    ASM_KEEP(scratch);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(global_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    for (;;) {
        scratch->value = global_page->value;

        if (!(entry->unk14 & 0x80)) {
            func_800453E0(payload, entry_data, entry, entry->unk06);
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

/* MECHANISM: Typed page and scratch fields preserve the signed lh/sw widths and offsets.
   ASM_KEEP breaks absolute-page constant folding; the guarded s1 page pin plus kept
   scratch base preserves the retail 0x20-frame save/init order s0, s2, s1, ra. */
