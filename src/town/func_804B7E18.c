#include "common.h"

extern void func_8001611C(void);
extern void func_800176B4(void);
extern void func_80018854(s32);
extern void func_800188CC(s32);
extern s32 func_8001894C(s16);

s32 func_80016618(void *arg0)
{
    func_8001611C();
    if (func_8001894C(*(s16 *)((u8 *)arg0 + 0x18)) == 0) {
        goto no_event;
    }

    func_800188CC(0x513);
    func_80018854(0x512);
    func_80018854(0x50E);
    goto done;

no_event:
    func_800176B4();
    func_80018854(0x513);
    func_800188CC(0x512);
    func_800188CC(0x50E);

done:
    return 0;
}

/* MECHANISM: A 24-byte frame holds arg0 in the sole saved register s0 across
   func_8001611C; explicit goto blocks preserve retail's nonzero-first layout.
   The two arms merge at one literal-zero epilogue, with no phantom tail call. */
