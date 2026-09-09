#include "common.h"

#define FIELD(obj, type, offset) (*(volatile type *)((u8 *)(obj) + (offset)))

extern s32 D_800786DC[];
extern s32 D_800786E8[];

void func_800B0D7C(void *arg0) {
    register s32 flags ASM_REG("$2");   /* MATCH: shared store at the merge target needs flags in $v0, matching the |=2 fallthrough path's own register choice */

    if (FIELD(arg0, s32, 0x10) > 0) {
        void **state;

        state = FIELD(arg0, void **, 0xCC);
        *FIELD(state, void **, 0x74) = D_800786DC;
        flags = FIELD(arg0, s32, 0x1C);
        flags &= ~2;
    } else {
        flags = FIELD(arg0, s32, 0x1C);
        flags |= 2;
    }
    FIELD(arg0, s32, 0x1C) = flags;

    if (FIELD(arg0, s32, 0x10) < FIELD(arg0, s32, 0x14)) {
        s32 mask;
        void **state;

        mask = ~1;
        ASM_KEEP(mask);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        FIELD(arg0, s32, 0x1C) &= mask;
        state = FIELD(arg0, void **, 0xCC);
        *FIELD(state, void **, 0x78) = D_800786E8;
        return;
    }

    FIELD(arg0, s32, 0x1C) |= 1;
}
