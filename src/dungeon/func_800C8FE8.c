#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CE748_0 {
    void * unk_00;
    u8 pad_04[0x13];
    u8 unk_17;
    u8 pad_18[0x10];
    s32 unk_28;
    u8 pad_2C[0x34];
    void * unk_60;
    void * unk_64;
    u8 pad_68[0x34];
    s16 unk_9C;
} S_800CE748_0;   /* arg0 in func_800CE748; pointer addresses record offset 0x14 */

typedef struct S_800CE748_1 {
    u8 unk_00;
    u8 unk_01;
    s8 unk_02;
} S_800CE748_1;   /* temp_s0 in func_800CE748 */

typedef struct S_800CE748_2 {
    u8 unk_00;
    u8 pad_01[0x1];
    s8 unk_02;
} S_800CE748_2;   /* temp_s0_2 in func_800CE748 */

typedef struct S_800CE748_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CE748_3;   /* temp_v1_2 in func_800CE748 */


extern u8 D_800E3D40[];
s32 func_800990FC(void);
s32 func_80099194(void *, s32);
void func_80099290(s32);
s32 func_8009929C(s32, s32);
s32 func_8009955C(void *, s32);
void func_800A56E0(s32);
void func_800A5720(s32);
void func_800A6508(void);
s32 func_800A6D30();
void func_800C5BBC(s32, s32, s32, s32, s32, s32);
s32 func_800C80F0(void);
s32 func_800CE7F0();
s32 func_800CE8A0();
void func_800CE9C0(void) __attribute__((noreturn));

extern u8 D_800E1B76[18];
extern u8 D_800E1B87[18];
extern u8 D_800E1B99[18];
extern u8 D_800E1BAA[18];

s32 func_800CE748(void *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_s1;
    s32 var_s2;
    s32 temp_a0_3;
    S_800CE748_1 *temp_s0;
    S_800CE748_2 *temp_s0_2;
    S_800CE748_3 *temp_v1_2;

    var_s2 = 0;
    var_s1 = 0;
    if (func_800C80F0() == 0) {
        temp_s0 = ((S_800CE748_0 *)((u8 *)arg0 - 0x14))->unk_60;
        if (temp_s0 != NULL) {
            s32 probability;

            probability = 0;
            var_s1 = 1;
            if (temp_s0->unk_01 == 0xF) {
                s32 is_one;

                is_one = temp_s0->unk_00 == 1;
                ASM_KEEP_NV(is_one);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                var_s1 = is_one;
            }
            if (*D_800E3D40 == 0) {
                temp_a0_2 = func_800A6D30() & 0xFFFF;
                if (((S_800CE748_0 *)((u8 *)arg0 - 0x14))->unk_17 != 0) {
                    register s32 random_mod ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    random_mod = temp_a0_2 % ((S_800CE748_0 *)((u8 *)arg0 - 0x14))->unk_17;
                    ASM_KEEP(random_mod);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                    func_800CE7F0(temp_a0_2);
                    return random_mod;
                }
                goto block_9;
            }
block_9:
            if (probability < 0x40) {
                if (!(var_s1 & 1)) {
                    if (temp_s0->unk_02 >= -0x62) {
                        temp_s0->unk_02 = (s8) ((u8) temp_s0->unk_02 - 1);
                    }
                }
                var_s2 = 1;
            }
            goto block_13;
        }
block_13:
        temp_s0_2 = ((S_800CE748_0 *)((u8 *)arg0 - 0x14))->unk_64;
        if (temp_s0_2 != NULL) {
            s32 probability;

            probability = 0;
            temp_a0_3 = temp_s0_2->unk_00;
            temp_v1 = temp_a0_3 & 0xFF;
            if ((temp_v1 == 1) || (temp_v1 == 7) || (((u32) (temp_a0_3 - 2) < 2U) != 0)) {
                var_s1 |= 2;
            }
            if (*D_800E3D40 == 0) {
                temp_a0 = func_800A6D30(temp_a0_3) & 0xFFFF;
                if (((S_800CE748_0 *)((u8 *)arg0 - 0x14))->unk_17 != 0) {
                    register s32 random_mod ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    random_mod = temp_a0 % ((S_800CE748_0 *)((u8 *)arg0 - 0x14))->unk_17;
                    ASM_KEEP(random_mod);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                    func_800CE8A0(temp_a0);
                    return random_mod;
                }
                goto block_23;
            }
block_23:
            if (probability < 0x40) {
                if (!(var_s1 & 2)) {
                    if (temp_s0_2->unk_02 >= -0x62) {
                        temp_s0_2->unk_02 = (s8) ((u8) temp_s0_2->unk_02 - 1);
                    }
                }
                var_s2 |= 2;
            }
            goto block_28;
        }
        goto block_28;
    }
block_28:
    if (((S_800CE748_0 *)((u8 *)arg0 - 0x14))->unk_28 & 0x4000) {
        if ((var_s2 << 0x10) == 0) {
            s32 dead_shift;

            func_800A6508();
            dead_shift = (u16) var_s2 << 0x10;
            ASM_TAILSLOT_PIN(dead_shift);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800CE9C0();
        }
        temp_v0 = func_800990FC();
        var_a1 = temp_v0;
        if (var_s2 & 1) {
            temp_a1_2 = func_8009955C(((S_800CE748_0 *)((u8 *)arg0 - 0x14))->unk_60, var_a1);
            {
                register void *message ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

                if (!(var_s1 & 1)) {
                    message = D_800E1B76;
                } else {
                    message = D_800E1B87;
                }
                var_a1 = func_80099194(message, temp_a1_2);
            }
            if (var_s2 & 2) {
                var_a1 = func_8009929C(0xA, var_a1);
            }
        }
        if (var_s2 & 2) {
            temp_a1 = func_8009955C(((S_800CE748_0 *)((u8 *)arg0 - 0x14))->unk_64, var_a1);
            {
                register void *message ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

                if (!(var_s1 & 2)) {
                    message = D_800E1B99;
                } else {
                    message = D_800E1BAA;
                }
                ASM_KEEP_NV(message);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                var_a1 = func_80099194(message, temp_a1);
            }
        }
        func_80099290(var_a1);
        func_800A5720(temp_v0);
    }
    if ((var_s2 << 0x10) != 0) {
        temp_v1_2 = ((S_800CE748_0 *)((u8 *)arg0 - 0x14))->unk_00;
        if (!(temp_v1_2->unk_14 & 0x8000)) {
            func_800C5BBC((temp_v1_2->unk_24 << 6) | 0x20, (temp_v1_2->unk_25 << 6) | 0x20, ((S_800CE748_0 *)((u8 *)arg0 - 0x14))->unk_9C, 0xC0C040, 0x20, 0);
            func_800A56E0(0x615);
        }
    }
    return 1;
}
