#include "common.h"
#include "m2c_compat.h"

extern u8 D_80083498[];
void *func_8003FD64();
M2C_UNK func_8004E298();
M2C_UNK func_8004E5A0();
M2C_UNK func_8004E634();
s32 func_80069E98();
M2C_UNK func_800B1320();
void *func_800B1484();
M2C_UNK func_800B13CC();
extern M2C_UNK D_800B45E0;
extern M2C_UNK D_800B490C;
extern M2C_UNK D_800DF24C[];

typedef struct {
    u8 bytes[16];
    u16 arg3;
} StackLocal;


typedef struct S_800B4C7C_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800B4C7C_0;   /* temp_v0_3 in func_800B4C7C */

typedef struct S_800B4C7C_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    void * unk_14;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x5];
    u8 unk_23;
} S_800B4C7C_1;   /* temp_s2 in func_800B4C7C */

typedef struct S_800B4C7C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800B4C7C_2;   /* temp_v0_4 in func_800B4C7C */

typedef struct S_800B4C7C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B4C7C_3;   /* temp_a0_2 in func_800B4C7C */

typedef struct S_800B4C7C_4 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B4C7C_4;   /* temp_v1_ptr in func_800B4C7C */

typedef struct S_800B4C7C_5 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
} S_800B4C7C_5;   /* temp_a1 in func_800B4C7C */

typedef struct S_800B4C7C_6 {
    u8 pad_00[0x2];
    s8 unk_02;
} S_800B4C7C_6;   /* func_800B1484(temp_s3) in func_800B4C7C */

void *func_800B4C7C(s32 arg0, u8 *arg1, s16 arg2, u16 arg3) {
    StackLocal local;
    void *callback;
    void *call_a0;
    u8 *call_a1;
    s32 call_a2;
    s16 temp_v0_8;
    register u16 temp_t0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 temp_cmp ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 temp_v1;
    register s32 temp_a3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    register s32 temp_s6 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 temp_s4 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *temp_s7;
    s16 temp_s8;
    void *temp_s5;
    s8 *temp_s0;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    S_800B4C7C_3 *temp_a0_2;
    S_800B4C7C_5 *temp_a1;
    void *temp_s0_2;
    void *temp_s3;
    void *temp_s2;
    void *temp_v0;
    register void *temp_v0_2 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    S_800B4C7C_0 *temp_v0_3;
    S_800B4C7C_2 *temp_v0_4;
    register void *temp_v1_ptr ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    local.arg3 = arg3;
    temp_v0 = func_8003FD64(0x212, D_80083498);
    temp_s7 = (void *)(u32) arg0;
    ASM_KEEP(temp_s7);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    temp_s5 = temp_v0;
    if (temp_s5 != NULL) {
        temp_s8 = arg2;
        ASM_KEEP(temp_s8);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_a0_2 = (*(void **)((u8 *)temp_s5 + 8));
        temp_a1 = (*(void **)((u8 *)temp_s5 + 0xC));
        temp_v0_3 = arg1 - 0x20;
        (*(void **)((u8 *)temp_s5 + 0x20)) = temp_v0_3;
        temp_v0_4 = temp_v0_3->unk_08;
        temp_s2 = temp_s5 + 0x20;
        ((S_800B4C7C_1 *)temp_s2)->unk_14 = temp_v0_4;
        temp_v0_5 = temp_v0_4->unk_02;
        temp_a0_2->unk_02 = temp_v0_5;
        temp_v1_ptr = ((S_800B4C7C_1 *)temp_s2)->unk_14;
        ((S_800B4C7C_1 *)temp_s2)->unk_18 = temp_v0_5;
        temp_v0_6 = ((S_800B4C7C_4 *)temp_v1_ptr)->unk_06;
        temp_a3 = 0x20;
        temp_a0_2->unk_06 = temp_v0_6;
        temp_v1_ptr = ((S_800B4C7C_1 *)temp_s2)->unk_14;
        temp_s4 = arg0 & 0xF;
        ((S_800B4C7C_1 *)temp_s2)->unk_1A = temp_v0_6;
        temp_v0_7 = ((S_800B4C7C_4 *)temp_v1_ptr)->unk_0A;
        temp_s6 = temp_s4;
        temp_a0_2->unk_0A = temp_v0_7;
        ((S_800B4C7C_1 *)temp_s2)->unk_1C = temp_v0_7;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        temp_v0_2 = temp_s5 + 0x40;
        temp_s3 = temp_v0_2;
        ASM_KEEP(temp_s3);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        temp_a1->unk_08 = temp_v0_2;
        temp_a1->unk_06 = temp_a3;
        if (arg0 & 0x8000) {
            ((S_800B4C7C_1 *)temp_s2)->unk_0E = 1;
        }
        temp_a0 = arg0 & 0xF0;
        temp_v1 = (s16) arg2;
        if (temp_v1 >= 0) {
            arg0 = 0x50;
            temp_s0 = (s8 *) local.bytes;
            switch (temp_a0) {
            case 0x10:
                temp_v0_8 = 0x7F;
                goto store_and_advance;
            case 0x20:
                temp_v0_8 = 0x80;
                goto store_and_advance;
            case 0x30:
                local.bytes[0] = 0x2B;
                goto mode_check;
            case 0x40:
                temp_v0_8 = 0x2D;
                goto store_and_advance;
            case 0x50:
                local.bytes[0] = 0x81;
                goto mode_check;
            case 0x60:
                local.bytes[0] = 0x82;
                goto advance_buffer;
store_and_advance:
                local.bytes[0] = temp_v0_8;
advance_buffer:
                temp_s0 = (s8 *) local.bytes + 1;
                goto mode_check;
            case 0x80:
                func_8004E634(temp_v1, temp_s0);
                temp_s0 = (s8 *) temp_s0 + func_80069E98(temp_s0);
                *temp_s0++ = 0x45;
                *temp_s0++ = 0x58;
                *temp_s0++ = arg0;
                *temp_s0++ = 0;
                func_8004E298(temp_s3, local.bytes, temp_s4);
                goto mode_check;
            case 0xA0:
                local.bytes[0] = temp_a3;
                func_8004E5A0(temp_v1, 3, local.bytes + 1);
                temp_s0 = (s8 *) local.bytes + 6;
                local.bytes[4] = 0x25;
                local.bytes[5] = 0;
                func_8004E298(temp_s3, local.bytes, temp_s4);
                goto mode_check;
            case 0x90:
                func_8004E5A0(temp_v1, 4, temp_s0);
                temp_s0 = (s8 *) local.bytes + 6;
                local.bytes[4] = 0x47;
                local.bytes[5] = 0;
                func_8004E298(temp_s3, local.bytes, temp_s4);
                goto mode_check;
            default:
                goto mode_check;
            }
mode_check:
            if (((u32) temp_s7 & 0xF0) < 0x80U) {
                func_8004E5A0(temp_s8, 3, temp_s0);
                func_8004E298(temp_s3, local.bytes, temp_s6);
            }
            goto block_46;
        }
        temp_v0_8 = ~arg2;
        if (temp_v0_8 > 0) {
            ((S_800B4C7C_1 *)temp_s2)->unk_10 = 0x18;
        }
        func_8004E298(temp_s3, D_800DF24C[temp_v0_8], temp_s4);
        goto block_46;
block_46:
        temp_t0 = *(volatile u16 *) &local.arg3;
        temp_cmp = (s16) temp_t0;
        if (temp_cmp == 1) {
            callback = &D_800B490C;
        } else {
            callback = &D_800B45E0;
        }
        (*(void * volatile *)((u8 *)temp_s5 + 0x10)) = callback;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        temp_s0_2 = temp_s2 + 0x20;
        func_800B1320(temp_s0_2, 0x80 - ((s32) (((S_800B4C7C_6 *)(func_800B1484(temp_s3)))->unk_02 + 0x88) / 2), (s16) ((0 - (s8) ((S_800B4C7C_1 *)temp_s2)->unk_23) - 4));
        func_800B13CC(temp_s0_2, 0x20);
    }
    return temp_s5;
}
