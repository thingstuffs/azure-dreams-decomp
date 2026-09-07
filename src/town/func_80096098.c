#include "common.h"

typedef struct {
    u8 pad[0x18];
    s16 field_18;
    s16 field_1A;
} TownState;

extern TownState D_8006ADBC;

s32 func_800937F8(void) {
    s32 result;
    s16 field_18;
    s16 field_1A;

    result = 0;
    field_18 = D_8006ADBC.field_18;
    if (field_18 == 12) {
        field_1A = D_8006ADBC.field_1A;
        if (field_1A == 6 ||
            field_1A == 8 ||
            field_1A == 9 ||
            field_1A == 42 ||
            field_1A == field_18 ||
            field_1A == 43) {
            result = 1;
        }
    }
    return result;
}
