#include "common.h"

typedef struct Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} Entry;

#ifdef NON_MATCHING
#define ASM_CLOBBER_A0() ((void)0)
#else
#define ASM_CLOBBER_A0() ASM_CLOBBER("$4")
#endif

extern void func_800D3738(void *arg0, s32 arg1, Entry *arg2, s16 arg3);
#ifndef NON_MATCHING
extern void func_800D36E0(void);
#else
extern void func_800D36E0(void) __attribute__((noreturn));
#endif

s32 func_800D36D0(void *arg0, s32 arg1, Entry *arg2)
{
    register void *state ASM_REG("$16") = arg0;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    ASM_CLOBBER_A0();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (!(arg2->unk14 & 0x80)) {
        func_800D3738(state, arg1, arg2, arg2->unk06);
    }

    arg2 = *(Entry **)((u8 *)state - 8);
    if (arg2 != 0) {
        state = (u8 *)arg2 + 0x20;
        arg1 = (s32)arg2->unk08;
        arg2 = arg2->unk0C;
        ASM_USE(state);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_USE(arg1);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ASM_USE(arg2);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        func_800D36E0();
    }
    return 0;
}

/* MECHANISM: The three-argument entry ABI forwards a0-a2 and the signed halfword as a3.
   State stays in s0; an a0 equivalence break retains retail's call-delay move.
   The implicit-register tail hands off state+0x20 in s0 and payload in a1/a2. */
