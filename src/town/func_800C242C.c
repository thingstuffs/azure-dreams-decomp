#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct S_800BFB8C_0_pre {
    u16 unk_00;
} S_800BFB8C_0_pre;   /* the 0x2 bytes before temp_s2 in func_800BFB8C, addressed as temp_s2[-1] */

typedef struct S_800BFB8C_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
    u16 unk_0E;
} S_800BFB8C_0;   /* temp_s2 in func_800BFB8C */

typedef struct S_800BFB8C_1 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800BFB8C_1;   /* var_a0 in func_800BFB8C */

typedef struct S_800BFB8C_2 {
    u8 pad_00[0xBC];
    s16 unk_BC;
} S_800BFB8C_2;   /* town in func_800BFB8C */

typedef struct S_800BFB8C_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0xC];
    s16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    u8 pad_24[0x2];
    s16 unk_26;
} S_800BFB8C_3;   /* temp_s0 in func_800BFB8C */

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
    register s16 temp_v0_4 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 temp_v1;
    s32 temp_a0;
    register s32 temp_v0_2 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 var_s1;
    s32 initial_v0;
    register s32 rng_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 final_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 var_v0;
    s32 base_coord;
    u16 temp_v0_5;
    u8 *town;
    u8 *kind;
    void *temp_s0;
    register void *temp_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *temp_v0;
    void *var_a0;
    void *callback;

    var_a0 = arg0;
    temp_s2 = var_a0;
    initial_v0 = ((S_800BFB8C_0 *)temp_s2)->unk_0E;
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
                ((S_800BFB8C_1 *)var_a0)->unk_10 = (M2C_UNK *)kind;
                func_8004491C(var_a0, callback);
                rng_v0 = rand();
                temp_v0_2 = rng_v0;
                temp_a0 = ((S_800BFB8C_2 *)town)->unk_BC;
                rng_v0 >>= 0xA;
                if (temp_v0_2 < 0) {
                    rng_v0 = (s32)(temp_v0_2 + 0x3FF) >> 0xA;
                }
                rng_v0 <<= 0xA;
                rng_v0 = temp_v0_2 - rng_v0;
                rng_v0 = temp_a0 + rng_v0;
                rng_v0 -= 0x200;
                ((S_800BFB8C_3 *)temp_s0)->unk_0C = rng_v0;
                ((S_800BFB8C_3 *)temp_s0)->unk_1E = rng_v0;
                temp_a0 = rand()
                        % (s16)((S_800BFB8C_0 *)temp_s2)->unk_0A;
                base_coord = ((S_800BFB8C_0 *)temp_s2)->unk_08;
                temp_v0_4 = -0x180;
                ((S_800BFB8C_3 *)temp_s0)->unk_10 = temp_v0_4;
                ((S_800BFB8C_3 *)temp_s0)->unk_26 = temp_v0_4;
                final_v0 = base_coord;
                final_v0 += temp_a0;
                ((S_800BFB8C_3 *)temp_s0)->unk_0E = final_v0;
                ((S_800BFB8C_3 *)temp_s0)->unk_22 = final_v0;
            }
            var_s1 -= 1;
            var_a0 = (void *)0x202;
        } while (var_s1 >= 0);
    }
    temp_v1 = ((S_800BFB8C_0 *)temp_s2)->unk_0C.s;
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
    temp_v0_5 = ((S_800BFB8C_0 *)temp_s2)->unk_0C.u + 1;
    ((S_800BFB8C_0 *)temp_s2)->unk_0C.u = temp_v0_5;
    goto done;

state_one:
    temp_v0_5 = ((S_800BFB8C_0 *)temp_s2)->unk_0E - 1;
    ((S_800BFB8C_0 *)temp_s2)->unk_0E = temp_v0_5;
    if ((temp_v0_5 << 0x10) <= 0) {
        (*(u16 *)((u8 *)temp_s2 + -2)) =
            (u16)(((S_800BFB8C_0_pre *)temp_s2)[-1].unk_00 | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }

done:
    return;
}

/* MECHANISM: The in-range 800BFCF0 transfers are explicit local CFG edges.
   Guarded v1/a0 roles feed a named s32 v0 sum; separate assignment and +=
   let combine preserve retail's commutative order. The tail flag is direct RMW. */
