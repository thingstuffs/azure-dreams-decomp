#include "common.h"

typedef void (*Callback)(s32);

typedef struct {
    u8 pad[0x248];
    Callback callback;
} CallbackTable;

typedef struct {
    s32 pad;
    s32 x;
    s32 y;
} Position;

typedef struct {
    u8 pad[0x1C];
    Position *position;
    CallbackTable *callbacks;
} TownState;

extern TownState *D_80016000;

/* Invoke the town callback with 1 and advance both position coordinates by 0x40. */
void func_800171CC(void)
{
    D_80016000->callbacks->callback(1);
    D_80016000->position->x += 0x40;
    D_80016000->position->y += 0x40;
}
