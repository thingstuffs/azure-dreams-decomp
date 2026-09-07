#include "common.h"
#include "m2c_compat.h"

typedef struct S_80175E6C_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xD];
    u8 unk_71;
} S_80175E6C_0;   /* arg3 in func_80175E6C */

typedef struct S_80175E6C_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80175E6C_1;   /* arg2p in func_80175E6C */

typedef struct S_80175E6C_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80175E6C_2;   /* temp_v0 in func_80175E6C */

typedef struct S_80175E6C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80175E6C_3;   /* base in func_80175E6C */

typedef struct S_80175E6C_4 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80175E6C_4;   /* arg0 in func_80175E6C */

typedef struct S_80175E6C_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80175E6C_5;   /* temp_v0_2 in func_80175E6C */

typedef struct S_80175E6C_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80175E6C_6_pre;   /* the 0x14 bytes before ((S_80175E6C_0 *)arg3)->unk_60 in func_80175E6C, addressed as ((S_80175E6C_0 *)arg3)->unk_60[-1] */


void func_80047784(void *, u8, s32);
void *func_800A04F0(void *, u8, u8, s16);
s16 func_800A0818(u8, u8, u8, u8, s32 *);
s32 func_800A2C34(void *);
void func_800A9A0C(void *);
void func_80175E14(void *);
extern s16 D_80083228;
extern u8 D_80083460[];
extern u16 D_80083462;
extern u8 *D_800E3D7C;
extern u8 D_80176348[];

s32 func_80175E6C(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 sp18;
    s32 temp_a0;
    s32 var_s0;
    s32 var_s1;
    s32 var_v0;
    void *temp_v0;
    void *temp_v0_2;
    register void *var_s2 ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    register void *arg2p ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *base;

    arg2p = arg2;
    ASM_KEEP_NV(arg2p);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    var_s2 = NULL;
    ASM_KEEP_NV(var_s2);   /* MATCH pin: retail delay-slot fill depends on it */
    ((S_80175E6C_0 *)arg3)->unk_71 = (u8) (((S_80175E6C_0 *)arg3)->unk_71 & 0x7F);
    if ((D_80083462 & 0x2008) ||
        (var_s1 = (s32) var_s2, ((func_800A2C34(arg3) << 0x10) != 0))) {
        goto return_minus_1;
    }
    var_s0 = 0;
    goto after_minus_1;
return_minus_1:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail branch polarity depends on it */
    var_v0 = -1;
    goto return_label;
after_minus_1:
loop_5:
    temp_v0 = func_800A04F0(arg3, ((S_80175E6C_1 *)arg2p)->unk_24, ((S_80175E6C_1 *)arg2p)->unk_25, (s16) (var_s0 << 9));
    if (temp_v0 != NULL) {
        if (temp_v0 == D_800E3D7C) {
            var_s1 = 1;
            goto block_12;
        }
        temp_a0 = ((S_80175E6C_2 *)temp_v0)->unk_14;
        if (temp_a0 & 0x4000) {
            if (!(temp_a0 & 0x20000000)) {
                var_s2 = temp_v0;
            }
        }
        goto block_12;
    }
block_12:
    var_s0 += 1;
    if (var_s0 >= 8) {
        if ((var_s2 != NULL) && (var_s1 & 0xFFFF)) {
            base = D_80083460;
            ASM_KEEP(var_s1);   /* MATCH pin: load-bearing for the whole function shape */
            ((S_80175E6C_3 *)base)->unk_0A = (u16) (((S_80175E6C_3 *)base)->unk_0A + 1);
            ((S_80175E6C_0 *)arg3)->unk_60 = var_s2;
            func_800A9A0C(var_s2);
            ((S_80175E6C_4 *)arg0)->unk_9A = 0x17;
            ((S_80175E6C_4 *)arg0)->unk_9B = 0;
            ((S_80175E6C_4 *)arg0)->unk_8C = 0;
            temp_v0_2 = ((S_80175E6C_6_pre *)(((S_80175E6C_0 *)arg3)->unk_60))[-1].unk_00;
            ((S_80175E6C_0 *)arg3)->unk_2A = func_800A0818(((S_80175E6C_1 *)arg2p)->unk_24, ((S_80175E6C_1 *)arg2p)->unk_25, ((S_80175E6C_5 *)temp_v0_2)->unk_24, ((S_80175E6C_5 *)temp_v0_2)->unk_25, &sp18);
            (*(u8 **)((u8 *)arg2p + 0x2C)) = D_80176348;
            func_80047784(arg2p, D_80176348[((s32) (D_80083228 + ((S_80175E6C_0 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
            func_80175E14(arg3);
            var_v0 = 1;
            goto return_label;
        }
        var_v0 = 0;
        goto return_label;
    }
    goto loop_5;
return_label:
    return var_v0;
}
