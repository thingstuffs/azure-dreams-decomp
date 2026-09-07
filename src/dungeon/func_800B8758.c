#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800BDEB8_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800BDEB8_0_pre;   /* the 0x14 bytes before var_s2 in func_800BDEB8, addressed as var_s2[-1] */

typedef struct S_800BDEB8_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    u32 unk_1C;
    u8 pad_20[0x84];
    s32 unk_A4;
    u8 pad_A8[0x2];
    s16 unk_AA;
    u8 pad_AC[0x64];
    s32 unk_110;
} S_800BDEB8_0;   /* var_s2 in func_800BDEB8 */

typedef struct S_800BDEB8_1 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_800BDEB8_1;   /* ((S_800BDEB8_0_pre *)var_s2)[-1].unk_00 in func_800BDEB8 */



M2C_UNK func_8008D330();
M2C_UNK func_80098B38();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_80099734();
s32 func_800A48F0();
M2C_UNK func_800A5720();
M2C_UNK func_800A5F38();
M2C_UNK func_800A63B8();
s32 func_800AD6FC();
s32 func_800BE04C();
s32 func_800BE088();
s32 func_800BE0F8();
M2C_UNK func_800D5460();

typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u8 D_80089358[];
extern u16 D_800DDE84[];
extern u8 D_800E0FA4[];
extern u8 D_800E0FB9[];
extern u8 D_800E0FD7[];
extern u8 *D_800E3D7C;

s32 func_800BDEB8(void *arg0, s32 arg1, s16 arg2) {
    void *current_entity = D_800E3D7C;
    void *var_s2 = arg0;
    s32 var_s5 = arg1;
    register s32 var_s3 ASM_REG("$19") = 0;   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 var_s4 ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 var_s1;
    register s32 var_s0 ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register void *entry_ra ASM_REG("$31");   /* MATCH pin: retail schedule: same instructions, different order without it */
    u32 id;
    s32 temp_v0;
    u32 flag_mask;

    ASM_KEEP4_NV(var_s2, var_s5, var_s3, entry_ra);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP4_NV(var_s2, var_s5, var_s3, var_s4);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP4_NV(var_s2, var_s5, var_s3, var_s1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (var_s2 == current_entity) {
        ((S_800BDEB8_0 *)var_s2)->unk_110 = var_s5;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }

    if ((u32)var_s2 <= 0x9FFFFFFF) {
        func_800A63B8(var_s2, var_s5, arg2);
        if (func_800AD6FC(var_s2, (D_800DDE84[((S_800BDEB8_0 *)var_s2)->unk_13] >> 6) & 3, 0) == 0) {
            func_800A5F38(var_s2, var_s5);
            return 1;
        }
    }

    id = ((S_800BDEB8_0 *)var_s2)->unk_13;
    if (id >= 0x2E) {
        goto set_s3;
    }
    if (id == 0x1E) {
        if ((((S_800BDEB8_0 *)var_s2)->unk_A4 != 0) || (((S_800BDEB8_0 *)var_s2)->unk_AA != 0)) {
            var_s3 = 1;
        }
    }
    temp_v0 = var_s3;
    ASM_KEEP(temp_v0);   /* MATCH pin: retail delay-slot fill depends on it */
    if (temp_v0 != 0) {
        goto special;
    }

            flag_mask = 0x80000;
            var_s4 = ((S_800BDEB8_0 *)var_s2)->unk_13;
            if (((S_800BDEB8_0 *)var_s2)->unk_1C & flag_mask) {
                ((S_800BDEB8_1 *)(((S_800BDEB8_0_pre *)var_s2)[-1].unk_00))->unk_06 = 0;
            }

            temp_v0 = func_800A48F0(var_s2, 10, 0x20);
            if ((s16)temp_v0 >= 0) {
                var_s0 = ((S_800BDEB8_0 *)var_s2)->unk_13;
                var_s1 = func_800990FC();
                ASM_KEEP(var_s1);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
                ((S_800BDEB8_0 *)var_s2)->unk_13 = var_s4;
                temp_v0 = func_80099734(var_s2, var_s1);
                ((S_800BDEB8_0 *)var_s2)->unk_13 = var_s0;
                return func_800BE04C(D_800E0FA4, temp_v0);
            }

            var_s1 = func_800990FC();
            ASM_KEEP(var_s1);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            {
                u8 *call_a0 = D_800E0FB9;
                s32 call_a1 = var_s1;
                ASM_KEEP(call_a1);   /* MATCH pin: retail keeps a computation the compiler would drop */
                temp_v0 = func_80099194(call_a0, call_a1);
            }
            func_80099290(temp_v0);
            func_800A5720(var_s1);
            func_800D5460((u8 *)var_s2 - 0x20, 0x20A0A0, 0x613);
            func_800BE088();
            return var_s3;

set_s3:
    var_s3 = 1;
    ASM_KEEP(var_s3);   /* MATCH pin: retail basic-block layout depends on it */
    temp_v0 = var_s3;
    if (temp_v0 == 0) {
        goto common;
    }
special:
        temp_v0 = func_800990FC();
        {
            register u8 *call_a0 ASM_REG("$4") = D_800E0FD7;   /* MATCH pin: retail schedule: same instructions, different order without it */
            register s32 call_a1 ASM_REG("$5") = temp_v0;   /* MATCH pin: retail register colouring depends on it */
            ASM_KEEP(call_a1);   /* MATCH pin: retail keeps a computation the compiler would drop */
            var_s0 = call_a1;
            temp_v0 = func_80099194(call_a0, call_a1);
        }
        temp_v0 = func_80099734(var_s2, temp_v0);
        temp_v0 = func_80099194(D_80089358, temp_v0);
        func_80099290(temp_v0);
        func_800A5720(var_s0);

common:
    func_80098B38(var_s5);
    D_80083460.field_A--;
    return 1;
}
