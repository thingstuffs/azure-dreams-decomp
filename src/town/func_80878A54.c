#include "common.h"

extern s32 D_80702C14[];

void func_80878A54(void) {
    D_80702C14[0] = (D_80702C14[0] * 8) + *(s32 *)0x807030B0;
}

/* MECHANISM: Frameless leaf; preserve the seed's single expression and register lifetimes.
   An unsized s32 array extern forces D_80702C14 through %hi/%lo with an addiu low half.
   The literal 0x807030B0 retains retail's separate lui/lw and the store fills the return slot. */
