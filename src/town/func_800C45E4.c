#include "common.h"
#include "m2c_compat.h"

s32 townFindContainingRangeGroup();                  /* extern */
extern M2C_UNK D_8006ADBC;
extern M2C_UNK D_800D4640;
extern M2C_UNK D_800D4658;
extern M2C_UNK D_800D4660;

/* Checks a masked value against the table selected by the current state. */
s32 townCheckMaskedValueInCurrentRange(s32 value) {
    s8 *state;
    s32 result;

    state = (s8 *)&D_8006ADBC;
    value &= 0x3FFF;
    if (*(s16 *)(state + 0x18) != 0xC) {
        townFindContainingRangeGroup(value, &D_800D4640);
        return;
    }
    if (*(s16 *)(state + 0x1A) == 0xD) {
        if (townFindContainingRangeGroup(value, &D_800D4658) != 0) {
            return 6;
        }
    } else if (*(s16 *)(state + 0x1A) == 0x2A) {
        if (townFindContainingRangeGroup(value, &D_800D4660) != 0) {
            return 7;
        }
    }
    result = 0;
    return result;
}
