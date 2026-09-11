#include "common.h"
extern int abs(int);

#define F_S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define F_U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define F_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern s32 func_800352FC(void *, void *, void *, s32);
extern s32 func_800C2AB4(void *);
extern void SD_Call(s32);
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

/* Updates random idle actions, bounded wandering, and sprite animation. */
void func_800BC990(void *actor, void *motion, void *sprite, s32 update_context) {
    void *anim_script;
    s16 *x_steps;
    s16 *y_steps;
    register s16 *step_y ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s16 *step_x;
    s16 *probe_x;
    s32 state;
    u16 timer;
    s32 choice;
    s32 direction_index;
    s32 step_offset;
    register s32 distance ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 delta_x;
    s32 delta_y;
    s32 walk_ticks;

    anim_script = 0;
    if (func_800352FC(actor, motion, sprite, update_context) == 0) {
        goto clear_flag;
    }
    if (func_800C2AB4(actor) == 0) {
        goto clear_flag;
    }
    if (F_S32(actor, 0xAC) & 1) {
        goto after_flag;
    }
    SD_Call(0x601);
    F_S32(actor, 0xAC) |= 1;
    goto after_flag;

clear_flag:
    F_S32(actor, 0xAC) &= -2;
after_flag:
    func_800478B8(sprite);
    timer = F_U16(actor, 0x6C) - 1;
    state = F_S16(actor, 0x68);
    F_U16(actor, 0x6C) = timer;

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
    if ((choice < 4) && (F_S16(actor, 0xA4) == 0x40)) {
        choice += 4;
    }
    F_U16(actor, 0x6C) = (rand() & 0x1F) + 0x28;
    if (choice < 4) {
        anim_script = D_800E9CD4;
        F_S16(actor, 0x68) = 0x40;
    }
    if (choice == 4) {
        F_S16(actor, 0xA6) = rand() & 1;
        anim_script = D_800E9D34;
        F_S16(actor, 0x68) = 0x60;
        goto finish_state;
    }
    if (choice < 8) {
        F_S16(actor, 0xA6) = rand() & 1;
        anim_script = D_800E9DAC;
        F_S16(actor, 0x68) = 0x80;
        goto finish_state;
    }

    x_steps = D_8006CCD8;
    y_steps = D_8006CCE8;
random_direction:
    direction_index = rand() & 3;
    step_offset = direction_index * 4;
    probe_x = (s16 *)(step_offset + (s32)x_steps);
    distance = F_S16(actor, 0xA2);
    delta_x = *probe_x;
    distance += delta_x;
    distance = abs(distance);
    choice = direction_index * 2;
    if (distance >= 2) {
        goto random_direction;
    }
    distance = F_S16(actor, 0xA0);
    delta_y = *(s16 *)(step_offset + (s32)y_steps);
    distance += delta_y;
    distance = abs(distance);
    if (distance >= 2) {
        goto random_direction;
    }

    do {
        walk_ticks = 0x40;
    } while (0);
    step_x = D_8006CCD8;
    step_x = (s16 *)((u8 *)step_x + step_offset);
    step_y = D_8006CCE8;
    step_y = (s16 *)((u8 *)step_y + step_offset);
    F_U16(actor, 0x6C) = walk_ticks;
    F_S16(actor, 0xA2) = (u16)F_S16(actor, 0xA2) + (u16)*step_x;
    F_S16(actor, 0xA0) = (u16)F_S16(actor, 0xA0) + (u16)*step_y;
    F_S32(motion, 0xC) = *step_x << 16;
    F_S32(motion, 0x10) = *step_y << 16;
    F_S16(actor, 0x68) = 0xA0;
    if ((F_S16(actor, 0xA4) != 0xA0) ||
        ((choice >> 1) != F_S16(actor, 0xA6))) {
        F_S16(actor, 0xA6) = choice >> 1;
        anim_script = D_800D210C[choice >> 1];
    }
finish_state:
    F_U16(actor, 0xA4) = F_U16(actor, 0x68);
    goto common;

case_40:
    if (F_U16(sprite, 0x14) & 0x6000) {
        anim_script = D_800E9CFC;
    }
    if ((s16)timer > 0) {
        goto common;
    }
    anim_script = D_800E9D0C;
    goto set_zero;

case_60:
    if ((s16)timer > 0) {
        goto common;
    }
    anim_script = D_800E9D54;
    F_S16(actor, 0x68) = 0x61;
    goto common;

case_61:
    if (!(F_U16(sprite, 0x14) & 0x6000)) {
        goto common;
    }
    anim_script = D_800E9D8C;
    goto set_f0;

case_80:
    if (F_U16(sprite, 0x14) & 0x6000) {
        anim_script = D_800E9DD4;
    }
    if ((s16)timer > 0) {
        goto common;
    }
    anim_script = D_800E9DEC;
set_f0:
    F_S16(actor, 0x68) = 0xF0;
    goto common;

case_A0:
    F_S32(motion, 0) += F_S32(motion, 0xC);
    F_S32(motion, 4) += F_S32(motion, 0x10);
    if (F_S16(actor, 0x6C) > 0) {
        goto common;
    }
    F_S16(actor, 0x68) = 0;
    goto common;

case_F0:
    if (!(F_U16(sprite, 0x14) & 0x6000)) {
        goto common;
    }
set_zero:
    F_S16(actor, 0x68) = 0;

common:
    if (F_S16(actor, 0xA6) != 0) {
        F_U16(sprite, 0x14) &= 0xFFFE;
        goto status_done;
    }
    F_U16(sprite, 0x14) |= 1;
status_done:
    if (anim_script != 0) {
        func_8003DB94(sprite, anim_script, 0);
    }
}
