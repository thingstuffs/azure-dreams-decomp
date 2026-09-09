#include "common.h"

#define FIELD(obj, type, offset) (*(volatile type *)((u8 *)(obj) + (offset)))

extern s32 D_800786DC[];
extern s32 D_800786E8[];

/* Update status flags and state pointers from the current value and its limit. */
void func_800B0D7C(void *object) {
    register s32 flags ASM_REG("$2");

    if (FIELD(object, s32, 0x10) > 0) {
        void **state;

        state = FIELD(object, void **, 0xCC);
        *FIELD(state, void **, 0x74) = D_800786DC;
        flags = FIELD(object, s32, 0x1C);
        flags &= ~2;
    } else {
        flags = FIELD(object, s32, 0x1C);
        flags |= 2;
    }
    FIELD(object, s32, 0x1C) = flags;

    if (FIELD(object, s32, 0x10) < FIELD(object, s32, 0x14)) {
        s32 clear_mask;
        void **state;

        clear_mask = ~1;
        ASM_KEEP(clear_mask);
        FIELD(object, s32, 0x1C) &= clear_mask;
        state = FIELD(object, void **, 0xCC);
        *FIELD(state, void **, 0x78) = D_800786E8;
        return;
    }

    FIELD(object, s32, 0x1C) |= 1;
}
