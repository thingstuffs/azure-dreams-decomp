/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

typedef void (*Callback)(s32, s32, s16 *, u8 *);

extern u8 D_A0700000[];
__asm__(".set D_A0700000, 0xA0700000");

void func_808B2D90(s32 arg0, s32 arg1, s16 *arg2, u8 *arg3) {
    Callback sp[3];
    Callback temp0;
    Callback temp1;
    Callback temp2;
    s16 *var_a2;
    s32 var_a0;
    u8 *var_a3;
    s32 var_a1;
    s16 *var_v1;

    var_a3 = arg3;
    var_a2 = arg2;
    ASM_KEEP(var_a2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_a1 = (u32)(D_A0700000 + 0x104);
    ASM_KEEP(var_a1);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    temp0 = ((Callback *)var_a1)[0];
    temp1 = ((Callback *)var_a1)[1];
    temp2 = ((Callback *)var_a1)[2];
    sp[0] = temp0;
    sp[1] = temp1;
    sp[2] = temp2;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_v1 = (s16 *)(D_A0700000 + 0xF34);
    ASM_KEEP(var_v1);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    var_a0 = 0;
    if (*var_v1 != 0) {
        register s32 temp_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        var_a3 = D_A0700000;
        var_a3 = *(u8 **)(var_a3 + 0xF40);
        var_a2 = var_v1;
loop_2:
        var_a1 = (s32) *var_a2;
        temp_v0 = var_a1;
        if ((s32) var_a1 < 0) {
            temp_v0 = var_a1 + 0x1F;
        }
        temp_v0 >>= 5;
        var_a2++;
        if (((s32) *(var_a3 + temp_v0) >> (var_a1 - (temp_v0 << 5))) & 1) {
            var_a0 += 1;
            if (*var_a2 != 0) {
                goto loop_2;
            }
        }
    }
    sp[var_a0](var_a0, var_a1, var_a2, var_a3);
}
