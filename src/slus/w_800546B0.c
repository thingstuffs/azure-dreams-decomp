#include "common.h"

/* D_80084858: large struct (sibling func_800559B4 shows fields out past 0x34 bytes);
 * this function only takes its address, no fields are accessed here, so only an
 * opaque >8B placeholder is declared to force %hi/%lo addressing. */
typedef struct S_80084858 {
    u8 pad[0x40];
} S_80084858;

/* Declared as an array (>8B) so gcc emits %hi/%lo addressing (lui+lw), matching
 * the target's lui v1,%hi(D_800847DC); lw v1,%lo(D_800847DC)(v1) sequence. */
extern u32 D_800847DC[3];
extern S_80084858 D_80084858;

extern int func_80053D64(void);
extern int func_800545F4(S_80084858 *a0);
extern void func_80054E00(s32 a0);

/* Fires event 0x74 when the CD read position reaches its target or the pending read check fails. */
void func_800546B0(void) {
    if ((u32)func_80053D64() < D_800847DC[0]) {
        if (func_800545F4(&D_80084858) == -1) {
            func_80054E00(0x74);
        }
    } else {
        func_80054E00(0x74);
    }
}
