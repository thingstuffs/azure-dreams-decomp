#include "common.h"

extern int D_800814A0;
extern u16 D_80083460[];

/* Decrements an entity's countdown and finalizes it when the countdown expires. */
void func_800C1EC4(u16 *entity) {
    s16 remainingTicks;
    u16 *destination;

    remainingTicks = entity[1] - 1;
    entity[1] = remainingTicks;
    if (remainingTicks <= 0) {
        destination = *(u16 **)((u8 *)entity + 0xC);
        destination[0x88 / 2] = entity[4];
        entity[-1] |= 0x8000;
        D_800814A0 |= 0x8000;
        D_80083460[5]--;
    }
}
