#include "common.h"

extern u8 D_80016038[16];
extern u8 *D_80016D08[3];

/* Point the first data slot at D_80016038. */
void func_8001601C(void) {
    D_80016D08[0] = D_80016038;
}
