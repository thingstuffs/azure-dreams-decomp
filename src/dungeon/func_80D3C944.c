#include "common.h"

typedef struct S_80172144_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    s16 unk_8A;
} S_80172144_0;   /* state in func_80172144 */

typedef struct S_80172144_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    u8 pad_9B[0x15];
    u8 unk_B0;
    u8 pad_B1[0x4];
    u8 unk_B5;
} S_80172144_1;   /* arg0 in func_80172144 */

typedef struct S_80172144_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 ** unk_2C;
} S_80172144_2;   /* entity in func_80172144 */

typedef struct S_80172144_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80172144_3;   /* temp_v0_2 in func_80172144 */

typedef struct S_80172144_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80172144_4;   /* (u8 *)state + ((S_80172144_0 *)state)->unk_8A in func_80172144 */



extern s32 func_80042900();
extern void func_80047784();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern void func_801708B8();
extern void func_80172378() __attribute__((noreturn));
extern void func_80172B4C();
extern s16 D_80083228[5];
extern u16 D_80083462[5];
extern u8 D_800E23E0[];

void func_80172144(void *arg0, s32 arg1, void *arg2, void *arg3) {
    register void *state ASM_REG("$17") = arg3;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *entity ASM_REG("$18") = arg2;   /* MATCH pin: retail register colouring depends on it */
    s32 var_a2_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s32 temp_v0;
    u8 temp_s0;
    u8 temp_s3;
    s32 temp_v1;
    S_80172144_3 *temp_v0_2;

    if ((((S_80172144_0 *)state)->unk_71.s > 0) &&
        ((s32)((S_80172144_0 *)state)->unk_71.u > ((S_80172144_0 *)state)->unk_8A)) {
        if ((((S_80172144_1 *)arg0)->unk_B5 == 0) &&
            (((S_80172144_2 *)entity)->unk_2C != D_800E23E0)) {
            ((S_80172144_2 *)entity)->unk_2C = D_800E23E0;
            func_80047784(entity,
                D_800E23E0[((D_80083228[0] + ((S_80172144_0 *)state)->unk_2A + 0x100) >> 9) & 7],
                0);
            if (((S_80172144_1 *)arg0)->unk_B0 == 0) {
                func_801708B8(arg0, arg1, entity);
            }
        }
        temp_s0 = ((S_80172144_2 *)entity)->unk_24;
        temp_s3 = ((S_80172144_2 *)entity)->unk_25;
        temp_v0 = func_80042900(state, 0x1B);
        if ((temp_v0 << 0x10) == 0) {
            register s32 call_a0 ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
            register s32 call_a1 ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
            s32 flags;
            s32 mode;

            call_a0 = temp_s0;
            mode = 0x3000;
            flags = ((S_80172144_0 *)state)->unk_1C;
            call_a1 = temp_s3;
            if (flags & 0x2000) {
                mode = 0x300;
            }
            func_8009A3D0(call_a0, call_a1, mode);
        }
        temp_v0_2 = (u8 *)state + ((S_80172144_0 *)state)->unk_8A;
        temp_v0_3 = func_800A0818(temp_s0, temp_s3,
            temp_v0_2->unk_74, temp_v0_2->unk_7C,
            (u8 *)arg0 + 0x98);
        temp_v0_4 = func_8009A66C(temp_v0_3, entity, state, 0x20);
        ((S_80172144_2 *)entity)->unk_24 = ((S_80172144_4 *)((u8 *)state + ((S_80172144_0 *)state)->unk_8A))->unk_74;
        ((S_80172144_2 *)entity)->unk_25 = ((S_80172144_4 *)((u8 *)state + ((S_80172144_0 *)state)->unk_8A))->unk_7C;
        ((S_80172144_0 *)state)->unk_8A = (u16)((S_80172144_0 *)state)->unk_8A + 1;
        if ((temp_v0 << 0x10) == 0) {
            s32 new_x;
            s32 new_y;

            var_a2_2 = 0x3000;
            new_x = ((S_80172144_2 *)entity)->unk_24;
            new_y = ((S_80172144_2 *)entity)->unk_25;
            if (((S_80172144_0 *)state)->unk_1C & 0x2000) {
                var_a2_2 = 0x300;
            }
            func_8009A21C(new_x, new_y, var_a2_2);
        }
        ((S_80172144_0 *)state)->unk_2A = temp_v0_3;
        if (temp_v0_4 == 3) {
            if ((((S_80172144_1 *)arg0)->unk_B5 == 0) && !(D_80083462[0] & 0x80) &&
                !(((S_80172144_2 *)entity)->unk_14 & 0x8000)) {
                func_80172B4C(arg0, arg1, entity, state);
                ((S_80172144_1 *)arg0)->unk_8C = 0;
                func_80172378();
                return;
            }
            goto block_21;
        }
block_21:
        ((S_80172144_1 *)arg0)->unk_9A = 0xF;
        ((S_80172144_1 *)arg0)->unk_8C = 0;
        ((S_80172144_0 *)state)->unk_1C |= 0x40000000;
        if (D_80083462[0] & 0x80) {
            ((S_80172144_1 *)arg0)->unk_96 = 0;
            return;
        }
        ((S_80172144_1 *)arg0)->unk_96 = 8;
        temp_v1 = ((S_80172144_0 *)state)->unk_71.u;
        if ((s32)temp_v1 > 0) {
            ((S_80172144_1 *)arg0)->unk_96 = 8 / (s32)temp_v1;
        }
    }
}

/* MECHANISM: true-space args stay in s4/s6/s2/s1 (frame -0x38, retail save order);
   >8B global arrays force the %hi/%lo pairs; the $5 carrier assigned BEFORE the
   effect-diamond puts `move a1,s3` in the beqz delay (backward-scan fill) and leaves
   the lw load-delay nop. RESIDUE (1 word, delay-slot): gcc still emits call1's own
   `move a0,s0` arg setup inside the beqz-target block, and reorg's backward scan
   hides it in the jal delay slot where retail has a nop -- retail's build emitted
   only TWO `move a0,s0` (the func_800A0818 setup plus reorg's target-thread copy in
   the bnez delay), i.e. call1's a0 setup never existed there. */
