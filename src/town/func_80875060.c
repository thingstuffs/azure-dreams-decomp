/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

typedef void (*TownCallback)(s32, void *, s16 *, s32);

extern u8 D_80700000[];
extern u8 D_80700BB4[];
extern s32 D_80701968[];

void func_80875060(s32 arg0, s32 arg1, s16 *arg2, s32 arg3) {
    TownCallback sp[3];
    s16 *var_a2;
    register s32 var_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 var_a0;
    s32 var_a3;
    void *var_a1;
    s32 *var_v1;
    s32 var_t0;
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_a1 = (void *)(D_80700000 + 0xBC8);
    ASM_KEEP(var_a1);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    var_v0 = ((s32 *)var_a1)[0];
    var_v1 = ((s32 *)var_a1)[1];
    var_a0 = ((s32 *)var_a1)[2];
    sp[0] = (TownCallback)var_v0;
    sp[1] = (TownCallback)var_v1;
    sp[2] = (TownCallback)var_a0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_a2 = arg2;
    var_a3 = arg3;
    var_v1 = (s32 *)(D_80700BB4 + 8);
    var_a0 = 0;
    if (*(s16 *)var_v1 != 0) {
        var_a3 = D_80701968[0];
        var_t0 = zero | 1;
        var_a2 = (s16 *)var_v1;
loop_2:
        var_a1 = (void *) *var_a2;
        if ((s32)var_a1 < 0) {
            var_v0 = (s32)var_a1 + 0x1F;
        } else {
            var_v0 = (s32)var_a1;
        }
        var_v0 >>= 5;
        var_v1 = (s32 *)((var_v0 * 4) + var_a3);
        var_v0 <<= 5;
        var_v0 = (s32)var_a1 - var_v0;
        var_v1 = (s32 *)*var_v1;
        var_v0 = var_t0 << var_v0;
        var_a2 += 1;
        if (var_v0 & (s32)var_v1) {
            var_a0 += 1;
            if (*var_a2 != 0) {
                goto loop_2;
            }
        }
    }
    sp[var_a0](var_a0, var_a1, var_a2, var_a3);
}
