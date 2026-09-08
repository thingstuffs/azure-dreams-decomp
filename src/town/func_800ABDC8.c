#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void func_800A9358(s32 arg2);

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
} Struct800ABDC8;

s32 func_800A9528(void *arg0, s32 arg1, s32 arg2) {
    register s32 v0 ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    register Struct800ABDC8 *v1 ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    register s32 x ASM_REG("$5");   /* MATCH pin: retail keeps this dead load in $a1 */

    v0 = arg2;
    v1 = (Struct800ABDC8 *)arg0;
    for (;;) {
        ASM_KEEP(v0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        func_800A9358(v0);
        v0 = *(s32 *)((u8 *)v1 - 8);
        v1 = (Struct800ABDC8 *)((u8 *)v0 + 0x20);
        if (v0 == 0) {
            ASM_CLOBBER("$4");   /* MATCH pin: retail register colouring depends on it */
            return 0;
        }
        ASM_KEEP(v1);   /* MATCH pin: retail delay-slot contents depend on it */
        x = ((Struct800ABDC8 *)v0)->unk08;
        ASM_KEEP(x);   /* MATCH pin: retail keeps this dead load */
        v0 = ((Struct800ABDC8 *)v0)->unk0C;
    }
}
