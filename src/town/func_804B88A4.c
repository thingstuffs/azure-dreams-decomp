#include "common.h"

typedef void (*TownCallback)(s32);

typedef struct {
    u8 pad_000[0x244];
    TownCallback callback2;
    u8 pad_248[0x10];
    TownCallback callback1;
} TownCallbacks;

typedef struct {
    s32 value_00;
    s32 value_04;
    s32 value_08;
} TownPosition;

typedef struct {
    u8 pad_00[0x1C];
    TownPosition *position;
    TownCallbacks *callbacks;
} TownState;

extern TownState *D_80016000;

void func_800170A4(void)
{
    TownPosition *position;
    s32 x;

    D_80016000->callbacks->callback1(0xB);
    D_80016000->callbacks->callback2(1);

    position = D_80016000->position;
    x = position->value_00;
    if (x == 2 || x == 0) {
        position->value_08 += 0x30;
        return;
    }
    position->value_04 -= 0x40;
}
