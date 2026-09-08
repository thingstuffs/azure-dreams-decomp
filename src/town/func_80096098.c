#include "common.h"

typedef struct {
    u8 pad[0x18];
    s16 field_18;
    s16 field_1A;
} TownState;

extern TownState D_8006ADBC;

/* Returns whether the town state matches one of the accepted state pairs. */
s32 func_800937F8(void) {
    s32 isAcceptedStatePair;
    s16 primaryState;
    s16 secondaryState;

    isAcceptedStatePair = 0;
    primaryState = D_8006ADBC.field_18;
    if (primaryState == 12) {
        secondaryState = D_8006ADBC.field_1A;
        if (secondaryState == 6 ||
            secondaryState == 8 ||
            secondaryState == 9 ||
            secondaryState == 42 ||
            secondaryState == primaryState ||
            secondaryState == 43) {
            isAcceptedStatePair = 1;
        }
    }
    return isAcceptedStatePair;
}
