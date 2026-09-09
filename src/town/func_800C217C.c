#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

s32 func_800352FC(s32 arg0, s32 *arg1, s32 arg2, s32 arg3); /* extern */
M2C_UNK SD_Call();                     /* extern */
s32 func_800C2AB4();                          /* extern */
extern u8 D_80083780[];


void func_800BF8DC(Rec_D_80082D58 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s16 temp_v1;
    s32 temp_a0;
    s32 var_v0;

    temp_a0 = (s32)arg0;
    temp_v1 = arg0->unk_68;
    if (temp_v1 != 1) {
        if (temp_v1 < 2) {
            if (temp_v1 != 0) {
                ASM_SCHED_BARRIER(); /* MATCH: preserve the retail guard layout. */
                goto end;
            }
            goto block_10;
        }
        if (temp_v1 != 2) {
            if (temp_v1 != 3) {
                ASM_SCHED_BARRIER(); /* MATCH: preserve the retail guard layout. */
                goto end;
            }
            goto block_17;
        }
block_10:
        {
            register s32 threshold ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register s32 distance ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            distance = *(s32 *)D_80083780;
            temp_a0 = *arg1;
            distance -= temp_a0;
            threshold = 0x3FFFFF;
            ASM_KEEP(threshold);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            if (distance < 0) {
                distance = -distance;
            }
            threshold = threshold < distance;
            if ((threshold == 0) && (func_800352FC(temp_a0, arg1, arg2, arg3) != 0) && (func_800C2AB4(arg0) != 0)) {
                SD_Call(0x50B);
                distance = (u16)arg0->unk_68;
                threshold = 0x20;
                arg0->unk_6C.as_s16 = threshold;
                distance++;
                var_v0 = distance;
            } else {
                goto end;
            }
        }
    } else {
block_17:
        if ((func_800352FC(temp_a0, arg1, arg2, arg3) == 0) || (func_800C2AB4(arg0) == 0)) {
            var_v0 = ((u16) arg0->unk_68 + 1) & 3;
        } else {
            goto end;
        }
    }
    arg0->unk_68 = var_v0;
end:
    return;
}

/* MECHANISM: The natural long-lived object pointer gives the retail 24-byte frame and sole s0 save.
   A wide global plus block-local v0 distance/v1 threshold lifetimes reproduces the load and compare order.
   The tied tail-slot pin sinks the kept state increment into func_800BF9CC's converted-j delay slot. */
