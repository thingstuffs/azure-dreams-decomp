#include "common.h"

typedef struct Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} Entry;

extern void func_800D3738(void *arg0, s32 arg1, Entry *arg2, s16 arg3);

/* Processes unflagged entries while following the state chain. */
s32 func_800D36D0(void *state_base, s32 entry_data, Entry *entry)
{
    void *state = state_base;

    for (;;) {
        if (!(entry->unk14 & 0x80)) {
            func_800D3738(state, entry_data, entry, entry->unk06);
        }
        entry = *(Entry **)((u8 *)state - 8);
        if (entry == 0) {
            break;
        }
        state = (u8 *)entry + 0x20;
        entry_data = (s32)entry->unk08;
        entry = entry->unk0C;
    }
    return 0;
}
