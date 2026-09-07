#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 rand();
extern void func_8002472C(void) __attribute__((noreturn));
extern u16 D_80027330[5];

void func_8195EE48(void *arg0, void *arg1)
{
    s32 temp_a0;
    s16 temp_a1;
    s16 temp_v0;
    register u16 counter ASM_REG("$3");

    counter = D_80027330[0];
    ASM_KEEP(counter);
    temp_a0 = FIELD(arg0, s16, 0x48);
    D_80027330[0] = counter + 1;
    if (temp_a0 == 0) {
        temp_a1 = FIELD(arg0, s16, 0x4C);
        if (temp_a1 > 0) {
            temp_a0 = FIELD(arg0, s16, 0x3C);
            FIELD(arg0, s16, 0x3C) =
                (u16)FIELD(arg0, s16, 0x3C) +
                ((FIELD(arg0, s16, 0x62) + FIELD(arg0, s16, 0x60) - temp_a0) / temp_a1);
            FIELD(arg1, s16, 0xA) =
                ((u16)FIELD(arg0, s16, 0x3C) + (rand(temp_a0, temp_a1) & 3)) - 2;
        }
        temp_v0 = (u16)FIELD(arg0, s16, 0x4C) - 1;
        FIELD(arg0, s16, 0x4C) = temp_v0;
        if ((temp_v0 << 16) <= 0) {
            FIELD(arg0, s16, 0x4C) = 0x20;
            FIELD(arg0, s16, 0x48) = (u16)FIELD(arg0, s16, 0x48) + 1;
            func_8002472C();
        }
    } else {
        FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
        FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
        FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
    }
}

/* MECHANISM: An s32-held 0x48 condition produces retail's signed load and exact s0/s1/ra frame.
   Reading the counter first preserves retail emission order; a guarded $v1 runtime-value pin
   fixes the final counter/base coloring while the natural CFG retains both delay-slot stores. */
