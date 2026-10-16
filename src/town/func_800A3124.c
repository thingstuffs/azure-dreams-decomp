#include "modules/town_door.h"

// Increase the object's ramp value, then finalize and change state at the limit.
void townOpenDoorToTarget(void *object, void *context) {
    u16 rampValue;

    rampValue = *(u16 *)((u8 *)object + 0x6E) + 0x40;
    *(u16 *)((u8 *)object + 0x6E) = rampValue;
    if ((s16) rampValue >= 0x400) {
        *(u16 *)((u8 *)object + 0x6E) = 0x400U;
        townChangeDoorMap(object, *(s32 *)((u8 *)context + 0x48));
        *(void **)((u8 *)object + 0x50) = &townDoorNoOp;
    }
}
