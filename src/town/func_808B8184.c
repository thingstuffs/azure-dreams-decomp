/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

extern s32 D_00003F50;
extern s32 D_00003F54;
extern s32 D_00003FBC[];
extern s32 D_000045F8;
extern s32 D_00001598[];

extern s32 func_800036D8(s32 index, s32 mode);

/* Picks the selected table value (or a fixed table's address) and returns it plus the global offset after a mode-one call. */
s32 func_808B8184(void) {
    s32 held;

    if (D_00003F54 == 0) {
        held = D_00003FBC[D_00003F50 * 8];
    } else {
        held = (s32)&D_00001598[0];
    }
    func_800036D8(D_00003F50, 1);
    return held + D_000045F8;
}
