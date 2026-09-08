#include "common.h"

extern s32 func_800A0668(void *);
extern s32 func_800A0F10(void *arg0, void *arg1);
extern void func_800A0B1C(void *arg0);
extern void func_800A0B74(void *arg0, s32 arg1);
extern void func_8009A8EC(s16 arg0, s16 arg1, s16 arg2);
extern void *D_800A08E8;

void func_800A0AC8(void *arg0, void *arg1, void *arg2) {
    if (*(s16 *)((u8 *)arg0 + 0x68) == 0) {
        if (func_800A0668(arg0) == 0) {
            void *call_arg = arg0;
            ASM_KEEP(call_arg);   /* MATCH pin: retail delay-slot contents depend on it */
            func_800A0B1C(call_arg);
        }
    } else if ((func_800A0668(arg0) != 0) && (func_800A0F10(arg0, arg1) != 0)) {
        func_800A0B74(arg0, *(s32 *)((u8 *)arg1 + 0x48));
        *(void **)((u8 *)arg0 + 0x50) = &D_800A08E8;
        func_8009A8EC(*(s16 *)((u8 *)arg0 + 0x72), *(s16 *)((u8 *)arg2 + 2), *(s16 *)((u8 *)arg2 + 6));
    }
}

/* MECHANISM: Preserve the seed's exact 0x20 frame, s0/s1/s2 holds, and CFG.
   A block-local $a0 call-argument pin plus ASM_KEEP moves arg0 into the
   conditional-branch delay slot, leaving the LEAD-22 tail-jump slot as nop. */
