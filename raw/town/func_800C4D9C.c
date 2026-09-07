#include "common.h"

extern s32 func_80033B2C(s32 arg0);
extern void func_80033AA8(s32 arg0);
extern void func_80033AE8(s32 arg0);
extern void func_800C2560(void);
extern s16 D_800D4770[];

void func_800C24FC(void) {
    s16 *current;
    register s16 *value ASM_REG("$16");

    current = D_800D4770;
    if (*current != -1) {
        s32 sentinel = -1;
        value = current + 1;
        do {
            if (func_80033B2C(*current) != 0) {
                current += 2;
                func_80033AA8(*value);
                ASM_KEEP(current);
                func_800C2560();
                return;
            }
            current += 2;
            func_80033AE8(*value);
            value += 2;
        } while (*current != sentinel);
    }
}

/* MECHANISM: The 0x20 frame holds current/value/sentinel in $s1/$s0/$s2.
   A success-path increment kept live across func_80033AA8 fills delay-slot word 19;
   pinning value to $s0 preserves retail coloring without adding a saved register. */
