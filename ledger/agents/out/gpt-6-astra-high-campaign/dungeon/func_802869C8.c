#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80012090[3];
extern s16 D_8008146C[5];
extern s16 D_800E3CD8[8];
extern s32 func_80033BC0(s32);
extern s32 func_800A6928(s32, s32);
extern void func_8009A21C(s32, s32, s32);

/* Check second tower availability and initialize the selected entry when available. */
s32 func_800199C8(s32 entry_index) {
    u8 *entry;
    u8 *entries;

    if (D_80012090[0] == 0) {
        if (D_8008146C[0] == 2) {
            if (func_80033BC0(0xA2) != 0) {
                if ((func_800A6928(0xC, 8) << 0x10) != 0) {
                    entries = (u8 *)D_800E3CD8;
                    entry = entries;
                    entry += ((entry_index << 0x10) >> 0xD);
                    *(s16 *)(entry + 0) = 4;
                    *(s16 *)(entry + 2) = 8;
                    *(s16 *)(entry + 4) = 8;
                    *(s16 *)(entry + 6) = 0;
                    func_8009A21C(8, 8, 0x20);
                    return 1;
                }
            }
        }
    }
    return 0;
}
