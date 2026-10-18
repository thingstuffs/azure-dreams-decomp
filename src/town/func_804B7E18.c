#include "common.h"

extern void store_supplied_values(void *, s32);
extern void func_800176B4(void);
extern void call_helper_with_fixed_id_0x118a(s32);
extern void func_800188CC(s32);
extern s32 func_8001894C(s16);

s32 process_scene_status_actions(void *object, s32 value)
{
    store_supplied_values(object, value);
    if (func_8001894C(*(s16 *)((u8 *)object + 0x18)) != 0) {
        func_800188CC(0x513);
        call_helper_with_fixed_id_0x118a(0x512);
        call_helper_with_fixed_id_0x118a(0x50E);
    } else {
        func_800176B4();
        call_helper_with_fixed_id_0x118a(0x513);
        func_800188CC(0x512);
        func_800188CC(0x50E);
    }
    return 0;
}

/* MECHANISM: A 24-byte frame holds arg0 in the sole saved register s0 across
   store_supplied_values; explicit jump blocks preserve retail's nonzero-first layout.
   The two arms merge at one literal-zero epilogue, with no phantom tail call. */
