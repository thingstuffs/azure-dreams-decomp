#include "common.h"

typedef void (*Callback)(s32);

typedef struct {
    u8 pad[0x244];
    Callback callback2;
    Callback callback1;
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

/* Invoke both town callbacks with 1 and shift the position by (+32, -16). */
void func_80017270(void)
{
    D_80016000->callbacks->callback1(1);
    D_80016000->callbacks->callback2(1);
    D_80016000->position->x += 0x20;
    D_80016000->position->y -= 0x10;
}
