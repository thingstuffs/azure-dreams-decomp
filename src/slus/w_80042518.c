#include "common.h"

typedef struct {
    s8 type;
    s8 value;
} S_80042518_Slot;

typedef struct {
    u8 pad[0x2C];
    S_80042518_Slot slot[4];
} S_80042518;

/* Search backward through a 4-entry slot array (each slot: type byte + value byte)
   for one whose type matches a1; if found, clear that slot and return its value,
   otherwise return 0. */
s32 findSlotByType(S_80042518 *a0, s8 a1) {
    s32 i;

    for (i = 3; i >= 0; i--) {
        if (a0->slot[i].type == a1) {
            s32 v0 = a0->slot[i].value;
            a0->slot[i].type = 0;
            a0->slot[i].value = 0;
            return v0;
        }
    }
    return 0;
}
