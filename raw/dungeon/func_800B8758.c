#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
    register void *var_s2 ASM_REG("$18") = arg0;
    register s32 var_s5 ASM_REG("$21") = arg1;
    register s32 var_s3 ASM_REG("$19") = 0;
    register s32 var_s4 ASM_REG("$20");
    register s32 var_s1 ASM_REG("$17");
    register s32 var_s0 ASM_REG("$16");
    register void *entry_ra ASM_REG("$31");
    register u32 id ASM_REG("$3");
    register s32 temp_v0 ASM_REG("$2");
    u32 flag_mask;

    ASM_KEEP4_NV(var_s2, var_s5, var_s3, entry_ra);
    ASM_KEEP4_NV(var_s2, var_s5, var_s3, var_s4);
    ASM_KEEP4_NV(var_s2, var_s5, var_s3, var_s1);
    if (var_s2 == current_entity) {
        FIELD(var_s2, s32, 0x110) = var_s5;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        func_800BE0F8();
        return 0;
    }

    if ((u32)var_s2 <= 0x9FFFFFFF) {
        func_800A63B8(var_s2, var_s5, arg2);
        if (func_800AD6FC(var_s2, (D_800DDE84[FIELD(var_s2, u8, 0x13)] >> 6) & 3, 0) == 0) {
            func_800A5F38(var_s2, var_s5);
            func_800BE0F8();
            return 1;
        }
    }

    id = FIELD(var_s2, u8, 0x13);
    ASM_KEEP(id);
    if (id >= 0x2E) {
        goto set_s3;
    }
    if (id == 0x1E) {
        if ((FIELD(var_s2, s32, 0xA4) != 0) || (FIELD(var_s2, s16, 0xAA) != 0)) {
            var_s3 = 1;
        }
    }
    temp_v0 = var_s3;
    ASM_KEEP(temp_v0);
    if (temp_v0 != 0) {
        goto special;
    }

            flag_mask = 0x80000;
            var_s4 = FIELD(var_s2, u8, 0x13);
            if (FIELD(var_s2, u32, 0x1C) & flag_mask) {
                FIELD(FIELD(var_s2, void *, -0x14), s16, 6) = 0;
            }

            temp_v0 = func_800A48F0(var_s2, 10, 0x20);
            if ((s16)temp_v0 >= 0) {
                var_s0 = FIELD(var_s2, u8, 0x13);
                ASM_KEEP(var_s0);
                var_s1 = func_800990FC();
                ASM_KEEP(var_s1);
                FIELD(var_s2, u8, 0x13) = var_s4;
                temp_v0 = func_80099734(var_s2, var_s1);
                FIELD(var_s2, u8, 0x13) = var_s0;
                return func_800BE04C(D_800E0FA4, temp_v0);
            }

            var_s1 = func_800990FC();
            ASM_KEEP(var_s1);
            {
                register u8 *call_a0 ASM_REG("$4") = D_800E0FB9;
                register s32 call_a1 ASM_REG("$5") = var_s1;
                ASM_KEEP(call_a0);
                ASM_KEEP(call_a1);
                temp_v0 = func_80099194(call_a0, call_a1);
            }
            func_80099290(temp_v0);
            func_800A5720(var_s1);
            func_800D5460((u8 *)var_s2 - 0x20, 0x20A0A0, 0x613);
            func_800BE088();
            return var_s3;

set_s3:
    var_s3 = 1;
    ASM_KEEP(var_s3);
    temp_v0 = var_s3;
    ASM_KEEP(temp_v0);
    if (temp_v0 == 0) {
        goto common;
    }
special:
        temp_v0 = func_800990FC();
        {
            register u8 *call_a0 ASM_REG("$4") = D_800E0FD7;
            register s32 call_a1 ASM_REG("$5") = temp_v0;
            ASM_KEEP(call_a0);
            ASM_KEEP(call_a1);
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
