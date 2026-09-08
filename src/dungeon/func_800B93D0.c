#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800BEB30_0 {
    u8 pad_00[0x4C];
    u8 * unk_4C;
    u8 pad_50[0xC0];
    u8 * unk_110;
    s32 unk_114;
} S_800BEB30_0;   /* global in func_800BEB30 */


typedef struct S_800BEB30_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BEB30_2;   /* decrement_base in func_800BEB30 */



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
    register u8 *held_arg1 ASM_REG("$20") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u8 *global;
    u8 *temp_s2;
    register s32 temp_s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 temp_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u32 temp_s0;
    register s32 temp_a1 ASM_REG("$5") = arg3;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 temp_call_a1;
    register u8 *temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *decrement_base;
    s32 temp_v0;
    u8 temp_v1;

    if (arg2 == 0xD) {
        return func_80098864(held_arg1, temp_a1);
    }

    global = D_800E3D7C[0];
    if (arg0 == (u32)global) {
        ((S_800BEB30_0 *)global)->unk_110 = held_arg1;
        func_8008D344(global, D_80083780, D_80082E80, global);
        held_arg1[3] &= (u8)~0x20;
        return 0;
    }

    if (arg0 <= 0x9FFFFFFF) {
        func_800A6480(arg0, held_arg1, arg2);
        if (func_800AD6FC(arg0, D_800DDE84[((Rec_D_800E3D7C *)arg0)->unk_10.at03_u8.v] & 3, 0) == 0) {
            func_800A5F38(arg0, held_arg1);
            return 1;
        }
        goto decrement;
    }

    temp_s2 = ((S_800BEB30_0 *)global)->unk_4C;
    if (temp_s2 != 0) {
        if (!(held_arg1[3] & 0x20)) {
            ((S_800BEB30_0 *)global)->unk_114 = 0x202080;
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
                temp_v0 = func_80099368(temp_s2, temp_s1);
                temp_call_a1 = temp_s1;
                temp_s1 = temp_v0;
                func_800998C0(temp_s0, temp_call_a1);
                return func_800BED78(D_80089368, temp_s1);
            }
            func_80099368(temp_s2, temp_s3);
            return func_800BED74(D_800E112A);
        }

other:
        temp_call_a1 = temp_s1;
        temp_v0 = func_80099368(temp_a0, temp_call_a1);
        temp_a0 = D_800E1156;
        temp_call_a1 = temp_v0;
        ASM_KEEP(temp_call_a1);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        temp_s1 = func_80099194(temp_a0, temp_call_a1);
        func_80099290(temp_s1);
        ASM_KEEP(temp_s1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800A5720(temp_s3);
        decrement_base = (u8 *)0x80080000;
        ASM_TAILSLOT_PIN(decrement_base);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        return func_800BEDAC();
    }

    func_800997FC(D_800E116E, temp_a1, arg2);

decrement:
    decrement_base = (u8 *)&D_80083460;
    ASM_KEEP(decrement_base);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ((S_800BEB30_2 *)decrement_base)->unk_0A--;
    func_80098B38(held_arg1);
    return 1;
}
