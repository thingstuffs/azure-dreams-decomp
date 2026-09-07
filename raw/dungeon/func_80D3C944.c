#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80042900();
extern void func_80047784();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern void func_801708B8();
extern void func_80172378() __attribute__((noreturn));
extern void func_801723CC() __attribute__((noreturn));
extern void func_80172B4C();
extern s16 D_80083228[5];
extern u16 D_80083462[5];
extern u8 D_800E23E0[];

void func_80172144(void *arg0, s32 arg1, void *arg2, void *arg3) {
    register void *state ASM_REG("$17") = arg3;
    register void *entity ASM_REG("$18") = arg2;
    s32 var_a2_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s32 temp_v0;
    u8 temp_s0;
    u8 temp_s3;
    s32 temp_v1;
    void *temp_v0_2;

    if ((FIELD(state, s8, 0x71) > 0) &&
        ((s32)FIELD(state, u8, 0x71) > FIELD(state, s16, 0x8A))) {
        if ((FIELD(arg0, u8, 0xB5) == 0) &&
            (FIELD(entity, u8 **, 0x2C) != D_800E23E0)) {
            FIELD(entity, u8 **, 0x2C) = D_800E23E0;
            func_80047784(entity,
                D_800E23E0[((D_80083228[0] + FIELD(state, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            if (FIELD(arg0, u8, 0xB0) == 0) {
                func_801708B8(arg0, arg1, entity);
            }
        }
        temp_s0 = FIELD(entity, u8, 0x24);
        temp_s3 = FIELD(entity, u8, 0x25);
        temp_v0 = func_80042900(state, 0x1B);
        if ((temp_v0 << 0x10) == 0) {
            register s32 call_a0 ASM_REG("$4");
            register s32 call_a1 ASM_REG("$5");
            s32 flags;
            s32 mode;

            call_a0 = temp_s0;
            mode = 0x3000;
            ASM_KEEP(mode);
            flags = FIELD(state, s32, 0x1C);
            ASM_KEEP(flags);
            call_a1 = temp_s3;
            if (flags & 0x2000) {
                mode = 0x300;
            }
            ASM_KEEP(call_a1);
            func_8009A3D0(call_a0, call_a1, mode);
        }
        temp_v0_2 = (u8 *)state + FIELD(state, s16, 0x8A);
        temp_v0_3 = func_800A0818(temp_s0, temp_s3,
            FIELD(temp_v0_2, u8, 0x74), FIELD(temp_v0_2, u8, 0x7C),
            (u8 *)arg0 + 0x98);
        temp_v0_4 = func_8009A66C(temp_v0_3, entity, state, 0x20);
        FIELD(entity, u8, 0x24) = FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x74);
        FIELD(entity, u8, 0x25) = FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x7C);
        FIELD(state, s16, 0x8A) = (u16)FIELD(state, s16, 0x8A) + 1;
        if ((temp_v0 << 0x10) == 0) {
            s32 new_x;
            s32 new_y;

            var_a2_2 = 0x3000;
            new_x = FIELD(entity, u8, 0x24);
            new_y = FIELD(entity, u8, 0x25);
            if (FIELD(state, s32, 0x1C) & 0x2000) {
                var_a2_2 = 0x300;
            }
            func_8009A21C(new_x, new_y, var_a2_2);
        }
        FIELD(state, s16, 0x2A) = temp_v0_3;
        if (temp_v0_4 == 3) {
            if ((FIELD(arg0, u8, 0xB5) == 0) && !(D_80083462[0] & 0x80) &&
                !(FIELD(entity, u16, 0x14) & 0x8000)) {
                func_80172B4C(arg0, arg1, entity, state);
                FIELD(arg0, s32, 0x8C) = 0;
                func_80172378();
                return;
            }
            goto block_21;
        }
block_21:
        FIELD(arg0, s8, 0x9A) = 0xF;
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(state, s32, 0x1C) |= 0x40000000;
        if (D_80083462[0] & 0x80) {
            FIELD(arg0, s16, 0x96) = 0;
            func_801723CC();
            return;
        }
        FIELD(arg0, s16, 0x96) = 8;
        temp_v1 = FIELD(state, u8, 0x71);
        if ((s32)temp_v1 > 0) {
            FIELD(arg0, s16, 0x96) = 8 / (s32)temp_v1;
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
