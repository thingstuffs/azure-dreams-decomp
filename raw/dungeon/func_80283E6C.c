#include "common.h"

extern s32 func_80016BF0();
extern u8 D_80083160[];

void func_80016E6C(void)
{
    void *state = D_80083160;

    state = (u8 *)state + 0x1DC;

    func_80016BF0(0, 0, (s16)(1 << *(s16 *)((u8 *)state + 0x14)),
                   (s16)(1 << *(s16 *)((u8 *)state + 0x16)));
}

/* MECHANISM: Keep the natural 24-byte call frame with only $ra saved at 0x10.
   Split D_80083160 address formation from the +0x1DC adjustment to retain
   retail's lui/addiu/addiu sequence without an ASM_KEEP scheduling fence. */
