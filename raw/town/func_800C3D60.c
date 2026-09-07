#include "common.h"

typedef struct {
    u8 pad0[0x18];
    s16 state;
    s16 index;
} TownState;

typedef struct {
    s16 unk0;
    s16 effect;
    u16 sound;
    s16 unk6;
    s16 unk8;
} TownEntry;

extern TownState D_8006ADBC;
extern TownEntry D_800D4094[];

extern s32 func_800C0F60(s16 arg0);
extern void func_800540A8(void);
extern void func_8004425C(s32 arg0);
extern s16 func_80053DA8(s32 arg0);

s32 func_800C14C0(void) {
    TownState *state;
    s32 index;
    TownEntry *entries;
    TownEntry *entry;

    state = &D_8006ADBC;
    index = func_800C0F60(state->index);
    func_800540A8();
    if (state->state == 12) {
        entries = D_800D4094;
        entry = &entries[index];
        if (entry->effect != -1) {
            func_8004425C(entry->effect);
        }
        if ((s16)entry->sound != -1) {
            func_80053DA8(entry->sound);
        }
    }
    return 1;
}

/* MECHANISM: Preserve the seed's exact 0x20 frame and held s0/s1 lifetimes.
   The sole residue was the table symbol's high half: D_800D4094, not D_800C4094.
   Typed 10-byte entries retain the retail index*10 and halfword access widths. */
