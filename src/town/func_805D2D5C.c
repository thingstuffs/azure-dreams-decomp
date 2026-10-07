#include "shared/town_root.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef struct TownEntry {
    s8 pad0[4];
    u8 state;
    u8 pad5[3];
} TownEntry;

extern s32 D_80019AFC[];

extern void func_80017E1C(void);
extern s32 func_80018504(void);

/* Updates the current town entry and clears its state on a nonzero result or global state 1. */
s32 func_805D2D5C(void)
{
    s32 update_result;
    u8 entry_state;

    update_result = 0;
    entry_state = ((TownEntry *)D_80016000->unk_40)[D_80016000->unk_08].state;
    D_80019AFC[0] = entry_state;
    if (entry_state != 2) {
        update_result = func_80018504();
    }
    if ((update_result != 0) || (func_80017E1C(), D_80019AFC[0] == 1)) {
        ((TownEntry *)D_80016000->unk_40)[D_80016000->unk_08].state = 0;
        D_80019AFC[0] = 0;
    }
    return update_result;
}
