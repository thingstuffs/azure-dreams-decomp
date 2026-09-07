#include "common.h"

#define F_S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define F_U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define F_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern s32 func_800352FC(void);
extern s32 func_800C2AB4(void *);
extern void func_80053DA8(s32);
extern void func_800478B8(void *);
extern s32 rand(void);
extern void func_8003DB94(void *, void *, s32);

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern void *D_800D210C[];
extern u8 D_800E9CD4[];
extern u8 D_800E9CFC[];
extern u8 D_800E9D0C[];
extern u8 D_800E9D34[];
extern u8 D_800E9D54[];
extern u8 D_800E9D8C[];
extern u8 D_800E9DAC[];
extern u8 D_800E9DD4[];
extern u8 D_800E9DEC[];

void func_800BC990(void *arg0, void *arg1, void *arg2) {
    void *handler;
    s16 *base_x;
    s16 *base_y;
    register s16 *step_y ASM_REG("$4");
    register s16 *step_x ASM_REG("$5");
    register s16 *probe_x ASM_REG("$4");
    s32 state;
    u16 timer;
    s32 choice;
    s32 index;
    register s32 byte_off ASM_REG("$6");
    register s32 distance ASM_REG("$3");
    register s32 delta_x ASM_REG("$4");
    register s32 delta_y ASM_REG("$2");
    s32 direction;
    s32 value;

    handler = 0;
    if (func_800352FC() == 0) {
        goto clear_flag;
    }
    if (func_800C2AB4(arg0) == 0) {
        goto clear_flag;
    }
    if (F_S32(arg0, 0xAC) & 1) {
        goto after_flag;
    }
    func_80053DA8(0x601);
    F_S32(arg0, 0xAC) |= 1;
    goto after_flag;

clear_flag:
    F_S32(arg0, 0xAC) &= -2;
after_flag:
    func_800478B8(arg2);
    timer = F_U16(arg0, 0x6C) - 1;
    state = F_S16(arg0, 0x68);
    F_U16(arg0, 0x6C) = timer;

    if (state == 0x61) {
        goto case_61;
    }
    if (state >= 0x62) {
        goto states_high;
    }
    if (state == 0x40) {
        goto case_40;
    }
    if (state >= 0x41) {
        goto states_mid;
    }
    if (state == 0) {
        goto case_0;
    }
    goto common;

states_mid:
    if (state == 0x60) {
        goto case_60;
    }
    goto common;

states_high:
    if (state == 0xA0) {
        goto case_A0;
    }
    if (state < 0xA1) {
        if (state == 0x80) {
            goto case_80;
        }
        goto common;
    }
    if (state == 0xF0) {
        goto case_F0;
    }
    goto common;

case_0:
    choice = rand() & 0xF;
    if ((choice < 4) && (F_S16(arg0, 0xA4) == 0x40)) {
        choice += 4;
    }
    F_U16(arg0, 0x6C) = (rand() & 0x1F) + 0x28;
    if (choice < 4) {
        handler = D_800E9CD4;
        F_S16(arg0, 0x68) = 0x40;
    }
    if (choice == 4) {
        F_S16(arg0, 0xA6) = rand() & 1;
        handler = D_800E9D34;
        F_S16(arg0, 0x68) = 0x60;
        goto finish_state;
    }
    if (choice < 8) {
        F_S16(arg0, 0xA6) = rand() & 1;
        handler = D_800E9DAC;
        F_S16(arg0, 0x68) = 0x80;
        goto finish_state;
    }

    base_x = D_8006CCD8;
    base_y = D_8006CCE8;
random_direction:
    index = rand() & 3;
    byte_off = index * 4;
    probe_x = (s16 *)(byte_off + (s32)base_x);
    ASM_KEEP(probe_x);
    distance = F_S16(arg0, 0xA2);
    delta_x = *probe_x;
    ASM_KEEP(delta_x);
    distance += delta_x;
    if (distance < 0) {
        distance = -distance;
    }
    choice = index * 2;
    if (distance >= 2) {
        goto random_direction;
    }
    distance = F_S16(arg0, 0xA0);
    delta_y = *(s16 *)(byte_off + (s32)base_y);
    ASM_KEEP(delta_y);
    distance += delta_y;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance >= 2) {
        goto random_direction;
    }

    value = 0x40;
    ASM_KEEP(value);
    step_x = D_8006CCD8;
    step_x = (s16 *)((u8 *)step_x + byte_off);
    step_y = D_8006CCE8;
    step_y = (s16 *)((u8 *)step_y + byte_off);
    F_U16(arg0, 0x6C) = value;
    F_S16(arg0, 0xA2) = (u16)F_S16(arg0, 0xA2) + (u16)*step_x;
    F_S16(arg0, 0xA0) = (u16)F_S16(arg0, 0xA0) + (u16)*step_y;
    F_S32(arg1, 0xC) = *step_x << 16;
    F_S32(arg1, 0x10) = *step_y << 16;
    F_S16(arg0, 0x68) = 0xA0;
    if ((F_S16(arg0, 0xA4) != 0xA0) ||
        ((choice >> 1) != F_S16(arg0, 0xA6))) {
        F_S16(arg0, 0xA6) = choice >> 1;
        handler = D_800D210C[choice >> 1];
    }
finish_state:
    F_U16(arg0, 0xA4) = F_U16(arg0, 0x68);
    goto common;

case_40:
    if (F_U16(arg2, 0x14) & 0x6000) {
        handler = D_800E9CFC;
    }
    if ((s16)timer > 0) {
        goto common;
    }
    handler = D_800E9D0C;
    goto set_zero;

case_60:
    if ((s16)timer > 0) {
        goto common;
    }
    handler = D_800E9D54;
    F_S16(arg0, 0x68) = 0x61;
    goto common;

case_61:
    if (!(F_U16(arg2, 0x14) & 0x6000)) {
        goto common;
    }
    handler = D_800E9D8C;
    goto set_f0;

case_80:
    if (F_U16(arg2, 0x14) & 0x6000) {
        handler = D_800E9DD4;
    }
    if ((s16)timer > 0) {
        goto common;
    }
    handler = D_800E9DEC;
set_f0:
    F_S16(arg0, 0x68) = 0xF0;
    goto common;

case_A0:
    F_S32(arg1, 0) += F_S32(arg1, 0xC);
    F_S32(arg1, 4) += F_S32(arg1, 0x10);
    if (F_S16(arg0, 0x6C) > 0) {
        goto common;
    }
    F_S16(arg0, 0x68) = 0;
    goto common;

case_F0:
    if (!(F_U16(arg2, 0x14) & 0x6000)) {
        goto common;
    }
set_zero:
    F_S16(arg0, 0x68) = 0;

common:
    if (F_S16(arg0, 0xA6) != 0) {
        F_U16(arg2, 0x14) &= 0xFFFE;
        goto status_done;
    }
    F_U16(arg2, 0x14) |= 1;
status_done:
    if (handler != 0) {
        func_8003DB94(arg2, handler, 0);
    }
}
