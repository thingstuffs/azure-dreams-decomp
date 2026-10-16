#include "common.h"
#include "shared/object_index_slots.h"

typedef s32 M2C_UNK;

extern void townCallTheHandlerSelectsNonzeroEntry();
extern s16 townClampTransformCoordinateDeltas();
extern M2C_UNK D_80099874;

/* Clears the object slot flag, sets its handler, and updates its position-dependent value. */
void townSetPlayerHandlerAndPositionValue(void *object, M2C_UNK value_arg, s32 handler_param) {
    M2C_UNK saved_value_arg;

    townCallTheHandlerSelectsNonzeroEntry(*(s32 **)(*(void **)((u8 *)object + 0x44) + 0x14), object, handler_param);
    saved_value_arg = value_arg;
    *((s8 *)(D_80082660) + (*(s32 *)((u8 *)object + 0x40) * 8)) = 0;
    *(void **)((u8 *)object + 4) = &D_80099874;
    *(s16 *)((u8 *)object + 0x10) = townClampTransformCoordinateDeltas(
        *(s16 *)((u8 *)object + 0x36),
        *(s16 *)((u8 *)object + 0x38),
        saved_value_arg);
}
