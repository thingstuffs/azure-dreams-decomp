#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

typedef struct Copy12 {
    s32 word[3];
} Copy12;

extern s32 func_80034A1C();
extern s32 func_8003EA54();
extern s32 func_80071494();
extern s32 func_80245C10();
extern s16 func_8025E01C();
extern void func_80528F24() __attribute__((noreturn));
extern void func_80529030() __attribute__((noreturn));
extern s32 D_80084D5C;
extern s32 D_80526430[3];
extern u8 D_80288EE0[];
extern u8 D_80288FF0[];
extern u8 D_80289030[];
extern u8 D_80289058[];
extern u8 D_80288F60[];
extern u8 D_80288F88[];

__asm__(".set D_80288FF0, D_80288EE0 + 0x110");
__asm__(".set D_80289030, D_80288EE0 + 0x150");
__asm__(".set D_80289058, D_80288EE0 + 0x178");

void func_8080DF94(void *arg0, void *arg1, void *arg2) {
    Copy12 scratch;
    s16 temp_v1;
    s32 temp_ret;
    s32 *temp_s5;
    register s32 var_s4 ASM_REG("$20");
    u16 temp_a0;
    u16 temp_v0_3;
    register void *tail_arg ASM_REG("$4");
    void *temp_s3;
    void *temp_s6;

    temp_s3 = FIELD(arg0, void **, 0);
    temp_s5 = scratch.word;
    var_s4 = 0;
    temp_s6 = FIELD(FIELD(temp_s3, void **, 4), void **, 8);
    scratch = *(Copy12 *)D_80526430;
    func_8003EA54(arg2);
    func_80245C10(arg1);
    temp_v1 = FIELD(arg0, s16 *, 4);

    if (temp_v1 == 0x21) {
        goto case_21;
    }
    if (temp_v1 < 0x22) {
        if (temp_v1 == 1) {
            goto case_1;
        }
        if (temp_v1 < 2) {
            if (temp_v1 == 0) {
                goto case_0;
            }
            return func_80529030();
        }
        tail_arg = arg1;
        if (temp_v1 == 0x20) {
            goto case_20;
        }
        func_80529030(tail_arg);
    }
    if (temp_v1 == 0x100) {
        goto case_100;
    }
    if (temp_v1 < 0x101) {
        if (temp_v1 == 0x22) {
            goto case_22;
        }
        return func_80529030();
    }
    if (temp_v1 == 0x101) {
        goto case_101;
    }
    if (temp_v1 == 0xFFF) {
        goto case_fff;
    }
    return func_80529030();

case_0:
    FIELD(arg2, s32 *, 0xC) = (s32)(FIELD(arg2, s32 *, 0xC) + 0x101010);
    if ((u8)FIELD(arg2, s32 *, 0xC) < 0xA0U) {
        goto block_60;
    }
    FIELD(arg2, s32 *, 0xC) = 0x808080;
    FIELD(arg2, u16 *, 0x14) = (u16)(FIELD(arg2, u16 *, 0x14) & 0xFFF3);
    return func_80528F24();

case_1:
    if (FIELD(arg0, u16 *, 8) & 1) {
        temp_ret = func_80071494();
        var_s4 = temp_s5[temp_ret % 3];
        FIELD(arg1, s32 *, 0xC) = (s32)(((func_80071494(temp_ret / 3) & 0x7F) - 0x40) << 0xF);
        FIELD(arg1, s32 *, 0x14) = (s32)((0 - ((func_80071494() & 0xF) + 8)) << 0x10);
        if (FIELD(arg1, s32 *, 0xC) > 0) {
            FIELD(arg2, u16 *, 0x14) = (u16)(FIELD(arg2, u16 *, 0x14) | 1);
        }
        FIELD(arg1, s32 *, 0x10) = (s32)FIELD(temp_s6, s32 *, 0x10);
        FIELD(arg0, s16 *, 4) = 0x20;
    }
    if (FIELD(temp_s3, s16 *, 0x36) == 0xA) {
        if (func_80071494() & 1) {
            var_s4 = (s32)D_80289030;
        } else {
            var_s4 = (s32)D_80289058;
        }
        {
            s32 next_state = 0x100;
            ASM_USE(var_s4);
            FIELD(arg0, s16 *, 4) = (s16)next_state;
        }
        return func_80529030();
    }
    goto block_60;

case_20: {
    s16 floor_y;
    register s32 pos_x ASM_REG("$2");
    s32 vel_x;
    s32 step_x;

    FIELD(arg1, s32 *, 0x14) = (s32)(FIELD(arg1, s32 *, 0x14) + 0x40000);
    floor_y = func_8025E01C(arg1);
    if (floor_y < FIELD(arg1, s32 *, 8)) {
        FIELD(arg1, s32 *, 8) = (s32)floor_y;
        FIELD(arg1, s32 *, 0x14) = (s32)((s32)(0 - FIELD(arg1, s32 *, 0x14)) >> 3);
    }
    if (FIELD(arg2, u16 *, 0x14) & 0x6000) {
        FIELD(arg0, u16 *, 6) = 0xA;
        if (FIELD(arg2, s32 *, 0) == (s32)D_80288FF0) {
            FIELD(arg2, s32 *, 0xC) = 0xA0A0A0;
            FIELD(arg2, u16 *, 0x14) = (u16)(FIELD(arg2, u16 *, 0x14) | 0xC);
            FIELD(arg0, s16 *, 4) = 0x22;
            return func_80529030((void *)floor_y);
        }
        if (func_80071494(floor_y) & 1) {
            var_s4 = (s32)D_80288F60;
        } else {
            var_s4 = (s32)D_80288F88;
        }
        ASM_USE(var_s4);
        FIELD(arg0, s16 *, 4) = (s16)((u16)FIELD(arg0, s16 *, 4) + 1);
    }
    pos_x = FIELD(arg1, s32 *, 0xC);
    vel_x = FIELD(arg1, s32 *, 0x10);
    step_x = pos_x >> 3;
    pos_x -= step_x;
    FIELD(arg1, s32 *, 0xC) = pos_x;
    pos_x = vel_x >> 3;
    vel_x -= pos_x;
    FIELD(arg1, s32 *, 0x10) = vel_x;
    return func_80529030((void *)step_x);
}

case_21: {
    s16 floor_y;
    register s32 pos_x ASM_REG("$2");
    s32 vel_x;
    s32 step_x;

    FIELD(arg1, s32 *, 0x14) = (s32)(FIELD(arg1, s32 *, 0x14) + 0x40000);
    floor_y = func_8025E01C(arg1);
    if (floor_y < FIELD(arg1, s32 *, 8)) {
        FIELD(arg1, s32 *, 8) = (s32)floor_y;
        FIELD(arg1, s32 *, 0x14) = (s32)((s32)(0 - FIELD(arg1, s32 *, 0x14)) >> 3);
    }
    pos_x = FIELD(arg1, s32 *, 0xC);
    vel_x = FIELD(arg1, s32 *, 0x10);
    step_x = pos_x >> 3;
    pos_x -= step_x;
    FIELD(arg1, s32 *, 0xC) = pos_x;
    pos_x = vel_x >> 3;
    vel_x -= pos_x;
    FIELD(arg1, s32 *, 0x10) = vel_x;
    temp_a0 = FIELD(arg2, u16 *, 0x14);
    if (temp_a0 & 0x6000) {
        FIELD(arg2, u16 *, 0x14) = (u16)(temp_a0 | 0xC);
        FIELD(arg2, s32 *, 0xC) = 0xA0A0A0;
        FIELD(arg0, s16 *, 4) = (s16)((u16)FIELD(arg0, s16 *, 4) + 1);
        return func_80529030((void *)temp_a0);
    }
    goto block_60;
}

case_22:
    FIELD(arg2, s32 *, 0xC) = (s32)(FIELD(arg2, s32 *, 0xC) + 0xFFDFDFE0);
    if (FIELD(arg1, s32 *, 8) > 0) {
        FIELD(arg1, s32 *, 0x14) = 0;
        FIELD(arg1, s32 *, 8) = 0;
    }
    if ((u8)FIELD(arg2, s32 *, 0xC) < 0x20U) {
        FIELD(arg2, s32 *, 0xC) = 0;
    }
    if ((FIELD(temp_s3, s16 *, 0x36) == 9) || (temp_v0_3 = FIELD(arg0, u16 *, 6) - 1, FIELD(arg0, u16 *, 6) = temp_v0_3, ((temp_v0_3 << 0x10) <= 0))) {
        FIELD(arg0, s16 *, 4) = 0xFFF;
        return func_80529030();
    }
    goto block_60;

case_100:
    FIELD(arg2, s32 *, 0xC) = 0xA0A0A0;
    FIELD(arg2, u16 *, 0x14) = (u16)(FIELD(arg2, u16 *, 0x14) | 0xC);
    FIELD(arg0, s16 *, 4) = (s16)((u16)FIELD(arg0, s16 *, 4) + 1);
case_101:
    FIELD(arg2, s32 *, 0xC) = (s32)(FIELD(arg2, s32 *, 0xC) + 0xFFDFDFE0);
    if ((u8)FIELD(arg2, s32 *, 0xC) < 0x20U) {
        FIELD(arg2, s32 *, 0xC) = 0;
        FIELD(arg0, s16 *, 4) = 0xFFF;
        return func_80529030();
    }
    goto block_60;

case_fff: {
    s32 global_flags;

    FIELD(arg0, u16 *, -2) = (u16)(FIELD(arg0, u16 *, -2) | 0x8000);
    do {
        global_flags = D_80084D5C;
    } while (0);
    global_flags |= 0x8000;
    D_80084D5C = global_flags;
    goto block_60;
}

block_60:
    if (var_s4 != 0) {
        func_80034A1C(arg2, var_s4, 0);
        FIELD(arg2, u16 *, 0x14) = (u16)(FIELD(arg2, u16 *, 0x14) & 0x9FFF);
    }
    return;
}
