#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
} TownPair;

extern TownPair D_80701DCC[];
extern void func_807026C0(u16 value);

/* Process both values in table pairs one through three. */
void func_807022BC(void) {
    s32 pair_index;

    for (pair_index = 1; pair_index < 4; pair_index++) {
        func_807026C0(D_80701DCC[pair_index].field_0);
        func_807026C0(D_80701DCC[pair_index].field_2);
    }
}
