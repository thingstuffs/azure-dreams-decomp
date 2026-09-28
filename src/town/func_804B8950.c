#include "common.h"
#include "shared/record_ptrs.h"

typedef void (*Callback)(s32);

typedef struct {
    u8 pad[0x244];
    Callback callback2;
    Callback callback1;
} CallbackTable;

typedef struct {
    s32 state;
    s32 value;
} StateEntry;

typedef struct {
    u8 pad[0x1C];
    StateEntry *entry;
    CallbackTable *callbacks;
} TownState;


/* Invoke both town callbacks and subtract 0x30 from the entry value in state 3. */
s32 func_80017150(void)
{
    ((TownState *)D_80016000)->callbacks->callback1(1);
    ((TownState *)D_80016000)->callbacks->callback2(1);
    if (((TownState *)D_80016000)->entry->state == 3) {
        ((TownState *)D_80016000)->entry->value -= 0x30;
        return 1;
    }
    return 0;
}
