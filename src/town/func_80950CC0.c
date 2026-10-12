#include "common.h"

extern u8 D_80016034[16];
extern u8 *D_80016D08[3];

/* Initialize the first data pointer to D_80016034. */
void func_8001601C(void) {
    D_80016D08[0] = D_80016034;
}
