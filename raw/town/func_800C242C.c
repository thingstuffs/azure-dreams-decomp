#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_80033BC0();
void *func_8003FD64();
void func_8004491C(void *, void *);
s32 rand(void);
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083160;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BFD14;
extern M2C_UNK D_800BFFF4;

void func_800BFB8C(void *arg0)
{
    s16 temp_v0_3;
    register s16 temp_v0_4 ASM_REG("$2");
    s16 temp_v1;
    register s32 temp_a0 ASM_REG("$4");
    register s32 temp_v0_2 ASM_REG("$3");
    register s32 var_s1 ASM_REG("$17");
    register s32 initial_v0 ASM_REG("$2");
    register s32 rng_v0 ASM_REG("$2");
    register s32 final_v0 ASM_REG("$2");
    s32 var_v0;
    s32 base_coord;
    u16 temp_v0_5;
    u8 *town;
    u8 *kind;
    void *temp_s0;
    register void *temp_s2 ASM_REG("$18");
    void *temp_v0;
    void *var_a0;
    void *callback;

    var_a0 = arg0;
    temp_s2 = var_a0;
    initial_v0 = M2C_FIELD(temp_s2, u16 *, 0xE);
    initial_v0 <<= 0x10;
    var_s1 = initial_v0 >> 0x11;
    town = (u8 *)&D_80083160;
    if (var_s1 >= 0) {
        kind = (u8 *)&D_800BFD14;
        do {
            temp_v0 = func_8003FD64((void *)0x202, &D_80083498);
            if (temp_v0 != NULL) {
                var_a0 = temp_v0;
                callback = &D_800BFFF4;
                temp_s0 = var_a0 + 0x20;
                M2C_FIELD(var_a0, M2C_UNK **, 0x10) = (M2C_UNK *)kind;
                func_8004491C(var_a0, callback);
                rng_v0 = rand();
                temp_v0_2 = rng_v0;
                temp_a0 = M2C_FIELD(town, s16 *, 0xBC);
                rng_v0 >>= 0xA;
                if (temp_v0_2 < 0) {
                    rng_v0 = (s32)(temp_v0_2 + 0x3FF) >> 0xA;
                }
                rng_v0 <<= 0xA;
                rng_v0 = temp_v0_2 - rng_v0;
                rng_v0 = temp_a0 + rng_v0;
                rng_v0 -= 0x200;
                M2C_FIELD(temp_s0, s16 *, 0xC) = rng_v0;
                M2C_FIELD(temp_s0, s16 *, 0x1E) = rng_v0;
                temp_a0 = rand()
                        % (s16)M2C_FIELD(temp_s2, s16 *, 0xA);
                base_coord = M2C_FIELD(temp_s2, s16 *, 8);
                temp_v0_4 = -0x180;
                M2C_FIELD(temp_s0, s16 *, 0x10) = temp_v0_4;
                M2C_FIELD(temp_s0, s16 *, 0x26) = temp_v0_4;
                final_v0 = base_coord;
                final_v0 += temp_a0;
                M2C_FIELD(temp_s0, s16 *, 0xE) = final_v0;
                M2C_FIELD(temp_s0, s16 *, 0x22) = final_v0;
            }
            var_s1 -= 1;
            var_a0 = (void *)0x202;
        } while (var_s1 >= 0);
    }
    temp_v1 = M2C_FIELD(temp_s2, s16 *, 0xC);
    if (temp_v1 == 0) {
        goto state_zero;
    }
    if (temp_v1 == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    if (func_80033BC0(0xA1) == 0) {
        goto done;
    }
    temp_v0_5 = M2C_FIELD(temp_s2, u16 *, 0xC) + 1;
    M2C_FIELD(temp_s2, u16 *, 0xC) = temp_v0_5;
    goto done;

state_one:
    temp_v0_5 = M2C_FIELD(temp_s2, u16 *, 0xE) - 1;
    M2C_FIELD(temp_s2, u16 *, 0xE) = temp_v0_5;
    if ((temp_v0_5 << 0x10) <= 0) {
        M2C_FIELD(temp_s2, u16 *, -2) =
            (u16)(M2C_FIELD(temp_s2, u16 *, -2) | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }

done:
    return;
}

/* MECHANISM: The in-range 800BFCF0 transfers are explicit local CFG edges.
   Guarded v1/a0 roles feed a named s32 v0 sum; separate assignment and +=
   let combine preserve retail's commutative order. The tail flag is direct RMW. */
