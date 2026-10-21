#include "common.h"

extern s32 rand(void);
extern s16 keima_payout_factors[];
extern s16 keima_selection_mask;
extern s32 keima_payout_remaining;

/* Randomize four entries, set two distinct entries to 1 and 2, and reset state. */
s32 randomize_four_entries_and_reset_state(void) {
    s32 entry_index;
    s32 random_value;
    s32 second_index;

    entry_index = 3;
    do {
        random_value = rand();
        keima_payout_factors[entry_index] = (random_value % 5) + 3;
        entry_index--;
    } while (entry_index >= 0);

    entry_index = rand() & 3;
    do {
        second_index = rand() & 3;
    } while (entry_index == second_index);

    keima_payout_factors[entry_index] = 1;
    keima_payout_factors[second_index] = 2;
    keima_selection_mask = 0;
    keima_payout_remaining = 0;
    return 0;
}
