#include "common.h"

typedef struct TownEntry {
    s8 field0;
    s8 field1;
    s16 field2;
    s32 field4;
} TownEntry;

extern TownEntry D_800CF720[];

s32 func_8008AD1C(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; D_800CF720[i].field1 != -1; i++) {
        if (arg0 == D_800CF720[i].field0 &&
            arg1 == D_800CF720[i].field1 &&
            arg2 == D_800CF720[i].field2) {
            return i;
        }
    }
    return i - 0x80000000;
}
