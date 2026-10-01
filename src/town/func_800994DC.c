#include "common.h"

extern u8 D_800133A6;
extern s32 D_800FE508[4];
extern s32 D_800FE520[33];

/* Initializes the state tables with an extra entry for mode 10. */
void func_80096C3C(void) {
    u8 *mode_page;

    D_800FE508[0] = 0x025FFFFF;
    D_800FE508[2] = 0x01000000;
    D_800FE508[1] = 0x1DA00000;
    D_800FE508[3] = 0x1DA00000;
    D_800FE520[0] = 0xF0000000;
    D_800FE520[1] = 0x0FE00000;
    D_800FE520[2] = 0;
    D_800FE520[3] = 0x04000000;
    D_800FE520[4] = 0x10200000;
    D_800FE520[5] = 0x30000000;
    D_800FE520[6] = 0;
    D_800FE520[7] = 0x04000000;
    D_800FE520[8] = 0xF0000000;
    D_800FE520[9] = 0x0F500000;
    D_800FE520[10] = 0;
    D_800FE520[11] = 0x065FFFFF;
    D_800FE520[12] = 0x10B00000;
    D_800FE520[13] = 0x30000000;
    D_800FE520[14] = 0;
    D_800FE520[15] = 0x065FFFFF;
    D_800FE520[16] = 0xF0000000;
    D_800FE520[17] = 0x0F980000;
    D_800FE520[18] = 0x05E80000;
    D_800FE520[19] = 0x065FFFFF;
    D_800FE520[20] = 0x10680000;
    D_800FE520[21] = 0x30000000;
    D_800FE520[22] = 0x05E80000;
    D_800FE520[23] = 0x065FFFFF;
    D_800FE520[24] = 0x1A100000;
    D_800FE520[25] = 0x30000000;
    D_800FE520[26] = 0;
    D_800FE520[27] = 0x09EFFFFF;
#ifdef NON_MATCHING
    mode_page = &D_800133A6 - 0x33A6;
#else
    mode_page = (u8 *)0x80010000;
#endif
    if (mode_page[0x33A6] == 0xA) {
        D_800FE520[29] = 0x05F00000;
        D_800FE520[28] = 0xF0000000;
        D_800FE520[30] = 0;
        D_800FE520[31] = 0x09EFFFFF;
        D_800FE520[32] = 0x80000000;
    } else {
        D_800FE520[28] = 0x80000000;
    }
}
