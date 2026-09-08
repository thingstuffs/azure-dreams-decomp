/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

extern s32 D_00003F50[];
extern s32 D_00003F54[];
extern s32 D_00003FBC[];
extern s32 D_000045F8[];
extern s32 D_00001598[];

extern s32 func_800036D8(s32 arg0, s32 arg1);
extern void func_800039C8(void) __attribute__((noreturn));

s32 func_808B8184(void) {
    s32 index;
    s32 held;

    if (D_00003F54[0] == 0) {
        index = D_00003F50[0];
        held = D_00003FBC[index * 8];
        ASM_KEEP(held);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        func_800039C8();
    } else {
        held = (s32)&D_00001598[0];
        ASM_KEEP(held);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        func_800036D8(D_00003F50[0], 1);
        return held + D_000045F8[0];
    }
}
