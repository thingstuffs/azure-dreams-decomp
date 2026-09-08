#include "common.h"

#define FIELD(obj, type, offset) (*(volatile type *)((u8 *)(obj) + (offset)))

extern void func_800B0DBC(void);
extern s32 D_800786DC[];
extern s32 D_800786E8[];

void func_800B0D7C(void *arg0) {
    if (FIELD(arg0, s32, 0x10) > 0) {
        s32 flags;
        void **state;

        state = FIELD(arg0, void **, 0xCC);
        *FIELD(state, void **, 0x74) = D_800786DC;
        flags = FIELD(arg0, s32, 0x1C);
        flags &= ~2;
        ASM_TAILSLOT_PIN(flags);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800B0DBC();
        return;
    }

    FIELD(arg0, s32, 0x1C) |= 2;
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

/* MECHANISM: Branch-local state pointers preserve the frameless 39-word shape and rowbase tail edges.
   ASM_TAILSLOT_PIN sinks the first masked value into its tail jump; the $v1 mask plus ASM_KEEP
   forces li -2 into the second branch delay slot ahead of the volatile flags load. */
