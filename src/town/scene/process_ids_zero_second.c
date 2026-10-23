#include "common.h"

typedef struct TownValuePair {
    u8 pad_00[0x20];
    s32 first_value;
    s32 second_value;
} TownValuePair;

extern void *D_800189D0;
extern s32 D_800189D4;

/* Caches the second D_800189D0 pair value in D_800189D4 and returns its first value. */
s32 process_ids_zero(void) {
    TownValuePair *values;

    values = D_800189D0;
    D_800189D4 = values->second_value;
    return values->first_value;
}
