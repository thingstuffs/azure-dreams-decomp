#include "common.h"

#ifndef NON_MATCHING
register s32 zero ASM_REG("$0"); /* Pin $zero to preserve ori instead of addiu. */
#else
#define zero 0
#endif

/* Set the value at 0x807003B4 to 9. */
void func_808757A0(void) {
    *(s32 *)0x807003B4 = zero | 9;
}
