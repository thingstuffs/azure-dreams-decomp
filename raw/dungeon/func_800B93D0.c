#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_8008D344();
extern s32 func_8008D368();
extern s32 func_80098864();
extern s32 func_80098B38();
extern s32 func_800990FC();
extern s32 func_80099194();
extern s32 func_80099290();
extern s32 func_80099368();
extern s32 func_8009955C();
extern s32 func_800997FC();
extern s32 func_800998C0();
extern s32 func_80099978();
extern s32 func_800A5720();
extern s32 func_800A5F38();
extern s32 func_800A6480();
extern s32 func_800AD6FC();
extern s32 func_800BED74();
extern s32 func_800BED78();
extern s32 func_800BEDAC();

extern u8 D_80082E80[];
extern s32 D_80083460;
extern u8 D_80083780[];
extern u8 D_80089364[];
extern u8 D_80089368[];
extern u8 D_800DD148[];
extern u16 D_800DDE84[];
extern u8 D_800E110B[];
extern u8 D_800E112A[];
extern u8 D_800E1156[];
extern u8 D_800E116E[];
extern u8 *D_800E3D7C[];

s32 func_800BEB30(u32 arg0, u8 *arg1, s16 arg2, s32 arg3) {
    register u8 *held_arg1 ASM_REG("$20") = arg1;
    u8 *global;
    register u8 *temp_s2 ASM_REG("$18");
    register s32 temp_s3 ASM_REG("$19");
    register s32 temp_s1 ASM_REG("$17");
    register u32 temp_s0 ASM_REG("$16");
    register s32 temp_a1 ASM_REG("$5") = arg3;
    register s32 temp_call_a1 ASM_REG("$5");
    register u8 *temp_a0 ASM_REG("$4");
    register u8 *decrement_base ASM_REG("$3");
    s32 temp_v0;
    u8 temp_v1;

    if (arg2 == 0xD) {
        return func_80098864(held_arg1, temp_a1);
    }

    global = D_800E3D7C[0];
    if (arg0 == (u32)global) {
        FIELD(global, u8 *, 0x110) = held_arg1;
        func_8008D344(global, D_80083780, D_80082E80, global);
        held_arg1[3] &= (u8)~0x20;
        return 0;
    }

    if (arg0 <= 0x9FFFFFFF) {
        func_800A6480(arg0, held_arg1, arg2);
        if (func_800AD6FC(arg0, D_800DDE84[FIELD(arg0, u8, 0x13)] & 3, 0) == 0) {
            func_800A5F38(arg0, held_arg1);
            return 1;
        }
        goto decrement;
    }

    temp_s2 = FIELD(global, u8 *, 0x4C);
    ASM_KEEP(temp_s2);
    if (temp_s2 != 0) {
        if (!(held_arg1[3] & 0x20)) {
            FIELD(global, s32, 0x114) = 0x202080;
            func_8008D368(global, D_80083780, D_80082E80, D_800DD148, 2);
            held_arg1[3] |= 0x20;
            return 0;
        }

        temp_s3 = func_800990FC(global, temp_a1, arg2);
        temp_s1 = temp_s3;
        temp_v1 = temp_s2[1];
        if (temp_v1 != 0xF) {
            temp_a0 = temp_s2;
            if (temp_v1 != 0x10) {
                goto other;
            }
            if (temp_s2[0] != 2) {
                goto other;
            }
        }
        {
            if (!(temp_s2[3] & 0x40)) {
                temp_s1 = func_8009955C(temp_s2, temp_s3);
                if ((s8)temp_s2[2] < 0x63) {
                    temp_s2[2] = (u8)(temp_s2[2] + 1);
                }
                temp_s1 = func_80099978(func_80099194(D_800E110B, temp_s1));
                temp_s0 = temp_s1 - 2;
                temp_s1 = func_80099194(D_80089364, temp_s1);
                ASM_KEEP(temp_s1);
                temp_v0 = func_80099368(temp_s2, temp_s1);
                temp_call_a1 = temp_s1;
                ASM_KEEP(temp_call_a1);
                temp_s1 = temp_v0;
                ASM_KEEP(temp_s1);
                func_800998C0(temp_s0, temp_call_a1);
                return func_800BED78(D_80089368, temp_s1);
            }
            func_80099368(temp_s2, temp_s3);
            return func_800BED74(D_800E112A);
        }

other:
        ASM_KEEP(temp_s1);
        ASM_CLOBBER("$5");
        temp_call_a1 = temp_s1;
        temp_v0 = func_80099368(temp_a0, temp_call_a1);
        temp_a0 = D_800E1156;
        ASM_KEEP(temp_a0);
        temp_call_a1 = temp_v0;
        ASM_KEEP(temp_call_a1);
        temp_s1 = func_80099194(temp_a0, temp_call_a1);
        func_80099290(temp_s1);
        ASM_KEEP(temp_s1);
        func_800A5720(temp_s3);
        decrement_base = (u8 *)0x80080000;
        ASM_TAILSLOT_PIN(decrement_base);
        return func_800BEDAC();
    }

    func_800997FC(D_800E116E, temp_a1, arg2);

decrement:
    decrement_base = (u8 *)&D_80083460;
    ASM_KEEP(decrement_base);
    FIELD(decrement_base, u16, 0xA)--;
    func_80098B38(held_arg1);
    return 1;
}
