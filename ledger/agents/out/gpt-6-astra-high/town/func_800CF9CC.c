#include "common.h"

extern void func_800CCF74(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

/* Update object movement with a 32-tick duration and a positive Y step of 4. */
void func_800CD12C(s32 state, s32 object, s32 unused) {
    func_800CCF74(state, object, unused, 0x20, 0, 4);
}
