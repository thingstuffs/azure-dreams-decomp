#include "common.h"

typedef struct TownEntry {
    s8 pad0[4];
    u8 state;
    u8 pad5[3];
} TownEntry;

typedef struct TownRoot {
    s32 pad0[2];
    s32 entry_index;
    u8 padC[0x34];
    TownEntry *entries;
} TownRoot;

extern TownRoot *D_80016000[];
extern s32 D_80019AFC[];

extern void func_80017E1C(void);
extern s32 func_80018504(void);

/* Updates the current town entry and clears its state on a nonzero result or global state 1. */
s32 func_805D2D5C(void)
{
    s32 update_result;
    u8 entry_state;

    update_result = 0;
    entry_state = D_80016000[0]->entries[D_80016000[0]->entry_index].state;
    D_80019AFC[0] = entry_state;
    if (entry_state != 2) {
        update_result = func_80018504();
    }
    if ((update_result != 0) || (func_80017E1C(), D_80019AFC[0] == 1)) {
        D_80016000[0]->entries[D_80016000[0]->entry_index].state = 0;
        D_80019AFC[0] = 0;
    }
    return update_result;
}
