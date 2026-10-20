#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
} TownPair;

extern TownPair D_80701DCC[];
extern void shop_clear_indexed_flag(u16 value);

/* Process both values in table pairs one through three. */
void shop_process_entry_pairs(void) {
    s32 pair_index;

    for (pair_index = 1; pair_index < 4; pair_index++) {
        shop_clear_indexed_flag(D_80701DCC[pair_index].field_0);
        shop_clear_indexed_flag(D_80701DCC[pair_index].field_2);
    }
}
