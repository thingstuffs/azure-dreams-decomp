#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
} TownPair;

extern TownPair D_80701DCC[];
extern void func_807026C0(u16 value);

void func_807022BC(void) {
    s32 i;

    for (i = 1; i < 4; i++) {
        func_807026C0(D_80701DCC[i].field_0);
        func_807026C0(D_80701DCC[i].field_2);
    }
}
