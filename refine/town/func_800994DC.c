#include "common.h"

extern u8 D_800133A6;
extern s32 D_800FE508[4];
extern s32 D_800FE520[33];

/* Initializes the state tables with an extra entry for mode 10. */
void func_80096C3C(void) {
    register s32 packed_30 ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    s32 packed_065fffff;
    s32 packed_f0;
    s32 packed_09efffff;
    s32 *state_page;
    s32 *state;
    u8 *mode_page;
    s32 *header;
    s32 entry_value;
    s32 shared_value;

    D_800FE508[0] = 0x025FFFFF;
    packed_065fffff = 0x065FFFFF;
    packed_09efffff = 0x09EFFFFF;
    header = D_800FE508;
    header[2] = 0x01000000;
    header[1] = 0x1DA00000;
    header[3] = 0x1DA00000;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
#ifdef NON_MATCHING
    state_page = D_800FE520 + 1720;
#else
    state_page = (s32 *)0x80100000;
#endif
    ASM_KEEP(state_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    packed_f0 = 0xF0000000;
    state = state_page - 1720;
    state_page[-1720] = packed_f0;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    entry_value = 0x0FE00000;
    shared_value = 0x04000000;
    state[1] = entry_value;
    entry_value = 0x10200000;
    packed_30 = 0x30000000;
    state[4] = entry_value;
    entry_value = 0x0F500000;
    state[9] = entry_value;
    entry_value = 0x10B00000;
    state[12] = entry_value;
    entry_value = 0x0F980000;
    state[3] = shared_value;
    state[7] = shared_value;
    shared_value = 0x05E80000;
    state[17] = entry_value;
    entry_value = 0x10680000;
    state[20] = entry_value;
    entry_value = 0x1A100000;
    state[2] = 0;
    state[5] = packed_30;
    state[6] = 0;
    state[8] = packed_f0;
    state[10] = 0;
    state[11] = packed_065fffff;
    state[13] = packed_30;
    state[14] = 0;
    state[15] = packed_065fffff;
    state[16] = packed_f0;
    ASM_KEEP(packed_f0);   /* MATCH pin: retail register colouring depends on it */
    state[18] = shared_value;
    state[19] = packed_065fffff;
    state[21] = packed_30;
    state[22] = shared_value;
    state[23] = packed_065fffff;
    state[24] = entry_value;
    state[25] = packed_30;
    ASM_KEEP(packed_30);   /* MATCH pin: retail schedule: same instructions, different order without it */
    state[26] = 0;
    state[27] = packed_09efffff;
#ifdef NON_MATCHING
    mode_page = &D_800133A6 - 0x33A6;
#else
    mode_page = (u8 *)0x80010000;
#endif
    if (mode_page[0x33A6] == 0xA) {
        state[29] = 0x05F00000;
        state[28] = packed_f0;
        state[30] = 0;
        state[31] = packed_09efffff;
        state[32] = 0x80000000;
    } else {
        state[28] = 0x80000000;
    }
}
