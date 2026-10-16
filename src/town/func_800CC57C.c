#include "common.h"

extern void townInitializeObjectEntries(void *, s32, void *);
extern s32 scaleRandomToUnsignedHalfwordLimit(s32);
extern u8 D_800C9AD4[];
extern u8 D_800D6504[];

// Initialize the object's data, movement state, and variant.
void townInitializeReactionMovement(void *object, void *movementState, s32 initializationValue) {
    townInitializeObjectEntries(object, initializationValue, D_800D6504);
    *(void **)((u8 *)object + 0x50) = D_800C9AD4;
    *(s32 *)((u8 *)movementState + 0x14) = 0xFFF60000;
    *(s16 *)((u8 *)object + 0x90) = (s16)(scaleRandomToUnsignedHalfwordLimit(3) + 1);
}
