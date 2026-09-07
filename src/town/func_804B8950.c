#include "common.h"

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

extern TownState *D_80016000;

s32 func_80017150(void)
{
    D_80016000->callbacks->callback1(1);
    D_80016000->callbacks->callback2(1);
    if (D_80016000->entry->state == 3) {
        D_80016000->entry->value -= 0x30;
        return 1;
    }
    return 0;
}
