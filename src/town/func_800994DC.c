#include "common.h"

extern u8 D_800133A6;
extern s32 D_800FE508[4];
extern s32 D_800FE520[33];

void func_80096C3C(void) {
    register s32 c30000000 ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    s32 c065FFFFF;
    s32 cF0000000;
    s32 c09EFFFFF;
    s32 *page;
    s32 *state;
    u8 *mode_page;
    s32 *head;
    s32 temp_v0;
    s32 temp_v1;

    D_800FE508[0] = 0x025FFFFF;
    c065FFFFF = 0x065FFFFF;
    c09EFFFFF = 0x09EFFFFF;
    head = D_800FE508;
    head[2] = 0x01000000;
    head[1] = 0x1DA00000;
    head[3] = 0x1DA00000;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
#ifdef NON_MATCHING
    page = D_800FE520 + 1720;
#else
    page = (s32 *)0x80100000;
#endif
    ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    cF0000000 = 0xF0000000;
    state = page - 1720;
    page[-1720] = cF0000000;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    temp_v0 = 0x0FE00000;
    temp_v1 = 0x04000000;
    state[1] = temp_v0;
    temp_v0 = 0x10200000;
    c30000000 = 0x30000000;
    state[4] = temp_v0;
    temp_v0 = 0x0F500000;
    state[9] = temp_v0;
    temp_v0 = 0x10B00000;
    state[12] = temp_v0;
    temp_v0 = 0x0F980000;
    state[3] = temp_v1;
    state[7] = temp_v1;
    temp_v1 = 0x05E80000;
    state[17] = temp_v0;
    temp_v0 = 0x10680000;
    state[20] = temp_v0;
    temp_v0 = 0x1A100000;
    state[2] = 0;
    state[5] = c30000000;
    state[6] = 0;
    state[8] = cF0000000;
    state[10] = 0;
    state[11] = c065FFFFF;
    state[13] = c30000000;
    state[14] = 0;
    state[15] = c065FFFFF;
    state[16] = cF0000000;
       /* MATCH pin: retail register colouring depends on it */
    state[18] = temp_v1;
    state[19] = c065FFFFF;
    state[21] = c30000000;
    state[22] = temp_v1;
    state[23] = c065FFFFF;
    state[24] = temp_v0;
    state[25] = c30000000;
    ASM_KEEP(c30000000);   /* MATCH pin: retail schedule: same instructions, different order without it */
    state[26] = 0;
    state[27] = c09EFFFFF;
#ifdef NON_MATCHING
    mode_page = &D_800133A6 - 0x33A6;
#else
    mode_page = (u8 *)0x80010000;
#endif
    if (mode_page[0x33A6] == 0xA) {
        state[29] = 0x05F00000;
        state[28] = cF0000000;
        state[30] = 0;
        state[31] = c09EFFFFF;
        state[32] = 0x80000000;
    } else {
        state[28] = 0x80000000;
    }
}
