#include "common.h"

#ifndef NON_MATCHING
register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#else
#define zero 0
#endif

void func_808757A0(void) {
    *(s32 *)0x807003B4 = zero | 9;
}

/* MECHANISM: The frameless leaf keeps a raw absolute lvalue so the store expands through $at.
   A guarded file-scope $zero carrier makes zero | 9 emit retail's ori instead of li/addiu.
   Avoiding a symbolic base also preserves the store-before-jr order and trailing nop. */
