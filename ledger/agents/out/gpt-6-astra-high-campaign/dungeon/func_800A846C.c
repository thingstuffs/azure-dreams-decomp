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
    s32 flag;
} Scratchpad;

extern void func_800453E0(void *arg0, s32 arg1, Entry *arg2, s16 arg3);

/* Walk linked entries, update the scratch flag, and process entries without bit 0x80 set. */
s32 func_800ADBCC(void *initial_state, s32 context, Entry *entry)
{
    void *state = initial_state;
    Scratchpad *scratch = (Scratchpad *)0x1F800000;

    for (;;) {
        scratch->flag = *(s16 *)((u8 *)state + 8);
        if (!(entry->unk14 & 0x80)) {
            func_800453E0(state, context, entry, entry->unk06);
        }

        entry = *(Entry **)((u8 *)state - 8);
        if (entry != 0) {
            state = (u8 *)entry + 0x20;
            context = (s32)entry->unk08;
            entry = entry->unk0C;
            continue;
        }
        return 0;
    }
}
