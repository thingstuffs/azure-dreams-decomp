#include "common.h"

extern void func_800CCF74(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

/* Runs a 32-tick movement phase with velocity (0, -4). */
void func_800CD014(s32 state_addr, s32 object_addr, s32 unused) {
    func_800CCF74(state_addr, object_addr, unused, 0x20, 0, -4);
}
