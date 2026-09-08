#include "common.h"

extern s32 rand(void);
extern s16 D_80024308[];
extern s16 D_80113158;
extern s32 D_8011315C;

/* Randomize four entries, set two distinct entries to 1 and 2, and reset state. */
s32 func_80953300(void) {
    s32 entry_index;
    s32 random_value;
    s32 second_index;

    entry_index = 3;
    do {
        random_value = rand();
        D_80024308[entry_index] = (random_value % 5) + 3;
        entry_index--;
    } while (entry_index >= 0);

    entry_index = rand() & 3;
    do {
        second_index = rand() & 3;
    } while (entry_index == second_index);

    D_80024308[entry_index] = 1;
    D_80024308[second_index] = 2;
    D_80113158 = 0;
    D_8011315C = 0;
    return 0;
}
