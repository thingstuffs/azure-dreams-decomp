#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001E660(); /* extern */
M2C_UNK func_8009A21C();             /* extern */
s32 func_8009A350();         /* extern */
s32 func_800A6D30();                                /* extern */
s32 func_800A6DA4();                    /* extern */
extern u8 D_800E3549[];
extern u8 D_800E36C8[];

typedef struct S_8001D328_0 {
    u8 unk_00;
    u8 pad_01[0x1];
    u8 unk_02;
    u8 pad_03[0x1];
    u16 unk_04;
    u16 unk_06;
} S_8001D328_0;   /* arg0 in func_8001D328 */

typedef struct S_8001D328_1 {
    u8 unk_00;
    u8 unk_01;
} S_8001D328_1;   /* var_s1 in func_8001D328 */

void func_8001D328(S_8001D328_0 *arg0) {
    s32 rand_v0;
    u16 sp10;
    s16 temp_v1;
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_s2;
    s32 var_v0;
    void *var_s1;
    void *var_s3;
    void *var_s4;
    u8 *base_3549;

    rand_v0 = func_800A6D30();
    {
        register s32 mul_a0 ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
        register s32 mul_v1 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        register s32 mul_t0 ASM_REG("$8");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 calc_v1 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

        mul_a0 = arg0->unk_06;
        mul_v1 = arg0->unk_04;
        mul_t0 = mul_a0 * mul_v1;
        rand_v0 &= 7;
        calc_v1 = (mul_t0 >> 6) + rand_v0 + 4;
        var_v0 = calc_v1;
        ASM_KEEP(var_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        temp_v1 = calc_v1;
    }
    temp_v1 = temp_v1 < 0x3D;
    if (!temp_v1) {
        var_v0 = 0x3C;
    }
    var_s2 = (s16) var_v0;
    if (var_s2 >= 0) {
        register u8 *prev_a0 ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
        register s32 index_v1 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        u8 *base36_v1;
        s32 offset_v0;

        base_3549 = D_800E3549;
        prev_a0 = base_3549 - 1;
        index_v1 = var_s2 * 4;
        var_s4 = (void *) (index_v1 + (s32) prev_a0);
        var_s3 = index_v1 + base_3549;
        base36_v1 = D_800E36C8;
        offset_v0 = var_s2 * 0xC;
        var_s1 = (void *) (offset_v0 + (s32) base36_v1);
        do {
            temp_s0 = func_800A6DA4(0, (arg0->unk_04 - 1) & 0xFFFF) & 0xFFFF;
            temp_v0 = func_800A6DA4(0, (arg0->unk_06 - 1) & 0xFFFF) & 0xFFFF;
            temp_v1_2 = arg0->unk_00 + temp_s0;
            ((S_8001D328_1 *)var_s1)->unk_00 = (u8) temp_v1_2;
            temp_v1_2 = arg0->unk_02 + temp_v0;
            ((S_8001D328_1 *)var_s1)->unk_01 = (u8) temp_v1_2;
            if (((func_8009A350(((S_8001D328_1 *)var_s1)->unk_00 - 1, *(volatile u8 *) ((u8 *) var_s1 + 1), 0, &sp10) << 0x10) == 0) || !(sp10 & 0xFF20)) {
                func_8009A21C(((S_8001D328_1 *)var_s1)->unk_00, ((S_8001D328_1 *)var_s1)->unk_01, 0x800);
                func_8001E660(var_s3, var_s4, 0, 1);
            }
            var_s4 -= 4;
            var_s3 -= 4;
            var_s2 -= 1;
            var_s1 -= 0xC;
        } while (var_s2 >= 0);
    }
}
/* MECHANISM: Short-lived guarded pins encode the multiply, clamp, and held-base register roles.
   Byte-array globals prevent fourfold pointer scaling and preserve the retail address order.
   One reused RMW temp plus a volatile call-site reread closes the final store/load live ranges. */
