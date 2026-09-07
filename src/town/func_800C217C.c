#include "common.h"
#include "m2c_compat.h"

s32 func_800352FC();                             /* extern */
M2C_UNK func_80053DA8();                     /* extern */
M2C_UNK func_800BF9CC();                            /* extern */
M2C_UNK func_800BF9D0();                            /* extern */
s32 func_800C2AB4();                          /* extern */
extern u8 D_80083780[];

typedef struct S_800BF8DC_0 {
    u8 pad_00[0x68];
    s16 unk_68;
    u8 pad_6A[0x2];
    s16 unk_6C;
} S_800BF8DC_0;   /* arg0 in func_800BF8DC */

void func_800BF8DC(S_800BF8DC_0 *arg0, s32 *arg1) {
    s16 temp_v1;
    s32 temp_a0;
    s32 var_v0;

    temp_v1 = arg0->unk_68;
    if (temp_v1 != 1) {
        if (temp_v1 < 2) {
            if (temp_v1 != 0) {
                func_800BF9D0();
                return;
            }
            goto block_10;
        }
        if (temp_v1 != 2) {
            if (temp_v1 != 3) {
                func_800BF9D0();
                return;
            }
            goto block_17;
        }
block_10:
        {
            register s32 threshold ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
            register s32 distance ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

            distance = *(s32 *)D_80083780;
            temp_a0 = *arg1;
            distance -= temp_a0;
            threshold = 0x3FFFFF;
            ASM_KEEP(threshold);   /* MATCH pin: retail schedule: same instructions, different order without it */
            if (distance < 0) {
                distance = -distance;
            }
            threshold = threshold < distance;
            if ((threshold == 0) && (func_800352FC() != 0) && (func_800C2AB4(arg0) != 0)) {
                func_80053DA8(0x50B);
                distance = (u16)arg0->unk_68;
                threshold = 0x20;
                arg0->unk_6C = threshold;
                distance++;
                ASM_TAILSLOT_PIN_TIED(distance);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                func_800BF9CC();
            }
        }
    } else {
block_17:
        if ((func_800352FC() == 0) || (func_800C2AB4(arg0) == 0)) {
            arg0->unk_68 = (s16) (((u16) arg0->unk_68 + 1) & 3);
        }
    }
}

/* MECHANISM: The natural long-lived object pointer gives the retail 24-byte frame and sole s0 save.
   A wide global plus block-local v0 distance/v1 threshold lifetimes reproduces the load and compare order.
   The tied tail-slot pin sinks the kept state increment into func_800BF9CC's converted-j delay slot. */
