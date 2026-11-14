#include "common.h"
#include "town/minigame/payout_data.h"
#include "town/minigame/keima_selection_mask_data.h"
#include "sdk/libc.h"
#include "town/system.h"
#include "town/data.h"

/* Randomize four entries, set two distinct entries to 1 and 2, and reset state. */
s32 randomize_keima_payout_factors(void) {
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
