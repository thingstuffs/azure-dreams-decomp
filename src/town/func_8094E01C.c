#include "common.h"

extern u8 D_80016038[16];
extern u8 *D_80016D08[3];

/* Sets the first buffer pointer to D_80016038. */
void func_8094E01C(void) {
    D_80016D08[0] = D_80016038;
}
