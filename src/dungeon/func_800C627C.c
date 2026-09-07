#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CB9DC_0_pre {
    u16 unk_00;
} S_800CB9DC_0_pre;   /* the 0x2 bytes before arg0 in func_800CB9DC, addressed as arg0[-1] */

typedef struct S_800CB9DC_0 {
    void * unk_00;
    u8 pad_04[0x2];
    u16 unk_06;
} S_800CB9DC_0;   /* arg0 in func_800CB9DC */

typedef struct S_800CB9DC_1_pre {
    void * unk_00;
    M2C_UNK * unk_04;
    u8 pad_08[0xE];
    u16 unk_16;
} S_800CB9DC_1_pre;   /* the 0x18 bytes before temp_s1 in func_800CB9DC, addressed as temp_s1[-1] */

typedef struct S_800CB9DC_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800CB9DC_1;   /* temp_s1 in func_800CB9DC */

typedef struct S_800CB9DC_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x21C];
    s32 unk_234;
    u8 pad_238[0x34DC];
    u16 unk_3714;
} S_800CB9DC_2;   /* arg1 in func_800CB9DC */

typedef struct S_800CB9DC_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800CB9DC_3;   /* temp_a0 in func_800CB9DC */

typedef struct S_800CB9DC_4 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800CB9DC_4;   /* arg2 in func_800CB9DC */

typedef struct S_800CB9DC_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800CB9DC_5;   /* counts in func_800CB9DC */

typedef struct S_800CB9DC_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CB9DC_6;   /* temp_a1 in func_800CB9DC */

typedef struct S_800CB9DC_7 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800CB9DC_7;   /* page14 in func_800CB9DC */

typedef struct S_800CB9DC_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CB9DC_8;   /* base34 in func_800CB9DC */

typedef struct S_800CB9DC_9 {
    u8 pad_00[0x14A0];
    union { volatile s32 s; s32 u; } unk_14A0;   /* accessed as both */
} S_800CB9DC_9;   /* page14_again in func_800CB9DC */


M2C_UNK func_80040AA0();               /* extern */
M2C_UNK func_800478B8();                      /* extern */
M2C_UNK func_800481E0();                            /* extern */
M2C_UNK func_800945E8();           /* extern */
M2C_UNK func_800948BC();                            /* extern */
M2C_UNK func_8009A028();                      /* extern */
M2C_UNK func_8009A3D0();             /* extern */
M2C_UNK func_800A32A4();                      /* extern */
M2C_UNK func_800A6780();                            /* extern */
M2C_UNK func_800CBB58();                            /* extern */
extern s32 D_80010234;
extern M2C_UNK D_80013714;
extern s16 D_80081468[3];
extern M2C_UNK D_800814A0;
extern u8 D_80082E6B;
extern M2C_UNK D_80083460;
extern u8 *D_800E3D7C;

void func_800CB9DC(void *arg0_in, void *arg1_in, void *arg2_in) {
    void *arg0 = arg0_in;
    S_800CB9DC_2 *arg1 = arg1_in;
    register S_800CB9DC_4 *arg2 ASM_REG("$18") = arg2_in;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    M2C_UNK *temp_a1;
    M2C_UNK var_a2;
    s32 temp_v1;
    u16 temp_v0;
    S_800CB9DC_3 *temp_a0;
    void *temp_s1;

    func_800478B8(arg2);
    temp_s1 = ((S_800CB9DC_0 *)arg0)->unk_00;
    temp_a1 = ((S_800CB9DC_1_pre *)temp_s1)[-1].unk_04;
    temp_a0 = ((S_800CB9DC_1_pre *)temp_s1)[-1].unk_00;
    temp_v1 = arg1->unk_14 + 0xFFFA0000;
    arg1->unk_14 = temp_v1;
    temp_a0->unk_08 = (s32) (temp_a0->unk_08 + temp_v1);
    temp_v0 = ((S_800CB9DC_0 *)arg0)->unk_06 + 1;
    ((S_800CB9DC_0 *)arg0)->unk_06 = temp_v0;
    if (((s16) temp_v0 >= 0x41) || ((arg2->unk_14 & 0x8000) != 0)) {
        if (temp_s1 == D_800E3D7C) {
            s16 *counts;
            u8 call_a0;
            register u8 *page8 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
            register s32 count32 ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
            u16 count16;

            arg1 = (void *)0x80010000;
            ASM_KEEP(arg1);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            if (arg1->unk_3714 & 4) {
                func_80040AA0(3U, temp_a1);
                func_800CBB58();
                return;
            }
            func_800945E8(temp_s1, temp_a1);
            func_800948BC();
            func_800A6780();
            page8 = (u8 *)0x80080000;
            ASM_KEEP(page8);   /* MATCH pin: keeps a constant in a register as retail does */
            counts = D_80081468;
            call_a0 = page8[0x2E6B];
            count32 = arg1->unk_234;
            count16 = ((S_800CB9DC_5 *)counts)->unk_04;
            count32++;
            count16++;
            arg1->unk_234 = count32;
            ((S_800CB9DC_5 *)counts)->unk_04 = count16;
            func_80040AA0(call_a0, counts);
            func_800481E0();
            func_800CBB58();
            return;
        }
        {
            s32 call2_a0;
            s32 call2_a1;
            s32 flags;

            flags = ((S_800CB9DC_1 *)temp_s1)->unk_1C;
            call2_a0 = ((S_800CB9DC_6 *)temp_a1)->unk_24;
            call2_a1 = ((S_800CB9DC_6 *)temp_a1)->unk_25;
            var_a2 = 0x3000;
            if (flags & 0x2000) {
                var_a2 = 0x300;
            }
            func_8009A3D0(call2_a0, call2_a1, var_a2);
        }
        func_800A32A4(temp_s1);
        func_8009A028(temp_s1);
        {
            register u8 *page14 ASM_REG("$5");   /* MATCH pin: retail immediate-load split depends on it */
            u8 *base34;
            register s32 global_value ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
            u16 dec_value;
            u8 *page14_again;
            u16 halfword;

            page14 = (u8 *)0x80080000;
            base34 = (u8 *)&D_80083460;
            halfword = ((S_800CB9DC_1_pre *)temp_s1)[-1].unk_16;
            ((S_800CB9DC_1_pre *)temp_s1)[-1].unk_16 = halfword | 0x8000;
            global_value = ((S_800CB9DC_7 *)page14)->unk_14A0;
            dec_value = ((S_800CB9DC_8 *)base34)->unk_0A;
            global_value |= 0x8000;
            dec_value--;
            ((S_800CB9DC_7 *)page14)->unk_14A0 = global_value;
            ((S_800CB9DC_8 *)base34)->unk_0A = dec_value;
            ASM_CLOBBER("$5");   /* MATCH pin: load-bearing for the whole function shape */
            halfword = ((S_800CB9DC_0_pre *)arg0)[-1].unk_00;
            page14_again = (u8 *)0x80080000;
            ((S_800CB9DC_0_pre *)arg0)[-1].unk_00 = halfword | 0x8000;
            global_value = ((S_800CB9DC_9 *)page14_again)->unk_14A0.s;
            global_value |= 0x8000;
            ((S_800CB9DC_9 *)page14_again)->unk_14A0.u = global_value;
        }
    }
}
/* MECHANISM: Pinned long-lived args reproduce the s3/s0/s2 prologue, with keeps after the first call.
   Split RMW locals and ABI-pinned call args recover both interleaved load/store schedules.
   Held page bases plus a symbolic D_80083460 base and dead-$a1 clobber force the final rematerialization. */
