/* Relinked copy of town/func_808782BC (func_808782BC.c); retail differs only at relocation sites. */
#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
} TownPair;

extern TownPair D_00003F58[];
extern void func_80003C1C(u16 value);

/* Process both values in table pairs one through three. */
void func_80003814(void) {
    s32 pair_index;

    for (pair_index = 1; pair_index < 4; pair_index++) {
        func_80003C1C(D_00003F58[pair_index].field_0);
        func_80003C1C(D_00003F58[pair_index].field_2);
    }
}
