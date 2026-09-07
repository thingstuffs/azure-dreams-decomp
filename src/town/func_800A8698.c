#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A5DF8_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800A5DF8_0;   /* var_s0 in func_800A5DF8 */

typedef struct S_800A5DF8_1 {
    u8 unk_00;
} S_800A5DF8_1;   /* &D_800CFCEF in func_800A5DF8 */

typedef struct S_800A5DF8_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800A5DF8_2;   /* var_v0 in func_800A5DF8 */

typedef struct S_800A5DF8_3 {
    u8 pad_00[0xC4];
    union { s16 s; u16 u; } unk_C4;   /* accessed as both */
    u8 pad_C6[0x2];
    s16 unk_C8;
} S_800A5DF8_3;   /* var_s1 in func_800A5DF8 */

typedef struct S_800A5DF8_4 {
    void * unk_00;
    u8 pad_04[0x4];
    s16 unk_08;
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800A5DF8_4;   /* var_s2 in func_800A5DF8 */


s32 func_8008C180();                        /* extern */
s16 func_80094AA0();           /* extern */
M2C_UNK func_80095094();                      /* extern */
M2C_UNK func_80095388();                 /* extern */
M2C_UNK func_800954F4();                 /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
s32 func_800A5894();                          /* extern */
M2C_UNK func_800A55CC();                         /* extern */
s32 func_800C1D44();                             /* extern */
void func_800A5EA0(void);                         /* extern */
extern u8 D_80083160[];
extern u8 D_80083780[];
extern u8 D_800CFCEF;
extern u8 D_800FE488[];
extern u8 D_800A5FDC[];

/* Rowbase-resolved true symbol for catalog row func_800A8698. */
void func_800A5DF8(void *arg0, void *arg1, M2C_UNK arg2) {
    s16 temp_v0;
    s16 temp_v0_2;
    s32 tail_v0;
    u16 temp_v0_3;
    u8 *var_v0;
    u32 page;
    register S_800A5DF8_4 *var_s2 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_800A5DF8_0 *var_s0;
    M2C_UNK var_s4;
    register u8 *var_s1;
    register u8 *var_s3;

    var_s2 = arg0;
    var_s0 = arg1;
    var_s4 = arg2;
    var_s1 = D_80083160;
    func_80095C80(var_s0);
    var_s3 = D_800FE488;
    temp_v0 = func_80095978(var_s0, var_s3);
    if (var_s0->unk_0A >= temp_v0) {
        func_80095A94(var_s0, temp_v0, var_s3);
        page = 0x80080000;
        ASM_PAGEBASE_PIN(page);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800A5EA0();
        return;
    }
    if (((S_800A5DF8_1 *)(&D_800CFCEF))->unk_00 != 0) {
        var_s0->unk_14 = 0;
        func_800954F4(var_s0, temp_v0);
        page = 0x80080000;
        ASM_PAGEBASE_PIN(page);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800A5EA0();
        return;
    }
    func_80095388(var_s0, temp_v0);
    var_v0 = D_80083780;

after_effect:
    if (func_800C1D44(func_8008C180(((S_800A5DF8_2 *)var_v0)->unk_02, ((S_800A5DF8_2 *)var_v0)->unk_06) & 0xFFFF) != 0) {
        var_s0->unk_14 = (s32) (var_s0->unk_14 - func_800A5894(var_s0));
    }
    func_80095094(var_s0);
    func_80095094(var_s0);
    temp_v0_2 = func_80094AA0(((S_800A5DF8_3 *)var_s1)->unk_C8, 0, 0x80);
    ((S_800A5DF8_3 *)var_s1)->unk_C8 = temp_v0_2;
    if ((temp_v0_2 & 0xFFF) < 0x80) {
        ((S_800A5DF8_3 *)var_s1)->unk_C8 = 0;
    }
    temp_v0_3 = var_s2->unk_0A.s - 1;
    var_s2->unk_0A.s = temp_v0_3;
       /* MATCH pin: load-bearing for the whole function shape */
    {
        s32 sign_v0;
        s32 count_a0;
        register s32 quotient_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
        sign_v0 = (s32) temp_v0_3 << 16;
        count_a0 = sign_v0 >> 16;
        quotient_v1 = -0x280;
        if (count_a0 <= 0) {
            var_s2->unk_0A.u = 0;
        }
        tail_v0 = count_a0 > 0
            ? (quotient_v1 = (quotient_v1 - ((S_800A5DF8_3 *)var_s1)->unk_C4.s) / count_a0,
               ((S_800A5DF8_3 *)var_s1)->unk_C4.u + quotient_v1)
            : -0x280;
        ((S_800A5DF8_3 *)var_s1)->unk_C4.s = tail_v0;
    }
    if ((var_s2->unk_0A.u == 0) &&
        (((S_800A5DF8_3 *)var_s1)->unk_C8 == 0)) {
        if (var_s2->unk_08 != 0) {
            func_800A55CC(var_s2, var_s0, var_s4);
            goto done;
        }
        var_s2->unk_0A.u = 0;
        var_s2->unk_00 = D_800A5FDC;
    }

done:
    ASM_KEEP(var_s4);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(var_s0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(var_s2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    return;
}
