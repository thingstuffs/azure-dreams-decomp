#include "common.h"

typedef struct {
    u8 pad0[0x4C];
    void *unk4C;
    u8 pad50[0x35];
    u8 unk85;
} Unk80092A98;

/* Return the base value plus an optional signed modifier, clamped to 0 through 99. */
s16 func_800981F8(Unk80092A98 *object) {
    s16 adjusted_value;
    u8 modifier_byte;

    adjusted_value = object->unk85;
    if (object->unk4C != 0) {
        modifier_byte = *((u8 *)object->unk4C + 2);
        adjusted_value += (s8)modifier_byte;
    }
    if (adjusted_value < 0) {
        adjusted_value = 0;
    }
    if (adjusted_value >= 100) {
        adjusted_value = 99;
    }
    return adjusted_value;
}
