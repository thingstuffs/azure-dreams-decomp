#include "common.h"

extern u8 D_80016034[16];
extern u8 *D_80016D08;

void func_8095001C(void) {
    D_80016D08 = D_80016034;
}
