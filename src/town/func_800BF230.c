#include "common.h"
#include "shared/dir_step.h"
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
    s16 *step_y;
    register s16 *step_x;
    s16 *probe_x;
    s32 state;
    u16 timer;
    s32 choice;
    s32 direction_index;
    s32 step_offset;
    s32 distance;
    s32 delta_y;
    s32 walk_ticks;

    anim_script = 0;
    if (func_800352FC(actor, motion, sprite, update_context) != 0 &&
        func_800C2AB4(actor) != 0) {
        if (!(F_S32(actor, 0xAC) & 1)) {
            SD_Call(0x601);
            F_S32(actor, 0xAC) |= 1;
        }
    } else {
        F_S32(actor, 0xAC) &= -2;
    }
    func_800478B8(sprite);
    timer = F_U16(actor, 0x6C) - 1;
    state = F_S16(actor, 0x68);
    F_U16(actor, 0x6C) = timer;

    switch (state) {
    case 0:
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
        } else if (choice < 8) {
            F_S16(actor, 0xA6) = rand() & 1;
            anim_script = D_800E9DAC;
            F_S16(actor, 0x68) = 0x80;
        } else {
            x_steps = dirStepX;
            y_steps = dirStepY;
            for (;;) {
                direction_index = rand() & 3;
                step_offset = direction_index * 4;
                probe_x = (s16 *)(step_offset + (s32)x_steps);
                distance = F_S16(actor, 0xA2) + *probe_x;
                distance = abs(distance);
                choice = direction_index * 2;
                if (distance >= 2) {
                    continue;
                }
                delta_y = F_S16(actor, 0xA0) + *(s16 *)(step_offset + (s32)y_steps);
                delta_y = abs(delta_y);
                if (delta_y < 2) {
                    break;
                }
            }
            walk_ticks = 0x40;
            step_x = dirStepX;
            step_x = (s16 *)((u8 *)step_x + step_offset);
            step_y = dirStepY;
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
        }
        F_U16(actor, 0xA4) = F_U16(actor, 0x68);
        break;
    case 0x40:
        if (F_U16(sprite, 0x14) & 0x6000) {
            anim_script = D_800E9CFC;
        }
        if ((s16)timer > 0) {
            break;
        }
        anim_script = D_800E9D0C;
        F_S16(actor, 0x68) = 0;
        break;
    case 0x60:
        if ((s16)timer > 0) {
            break;
        }
        anim_script = D_800E9D54;
        F_S16(actor, 0x68) = 0x61;
        break;
    case 0x61:
        if (!(F_U16(sprite, 0x14) & 0x6000)) {
            break;
        }
        anim_script = D_800E9D8C;
        F_S16(actor, 0x68) = 0xF0;
        break;
    case 0x80:
        if (F_U16(sprite, 0x14) & 0x6000) {
            anim_script = D_800E9DD4;
        }
        if ((s16)timer > 0) {
            break;
        }
        anim_script = D_800E9DEC;
        F_S16(actor, 0x68) = 0xF0;
        break;
    case 0xA0:
        F_S32(motion, 0) += F_S32(motion, 0xC);
        F_S32(motion, 4) += F_S32(motion, 0x10);
        if (F_S16(actor, 0x6C) > 0) {
            break;
        }
        F_S16(actor, 0x68) = 0;
        break;
    case 0xF0:
        if (!(F_U16(sprite, 0x14) & 0x6000)) {
            break;
        }
        F_S16(actor, 0x68) = 0;
        break;
    }

    if (F_S16(actor, 0xA6) != 0) {
        F_U16(sprite, 0x14) &= 0xFFFE;
    } else {
        F_U16(sprite, 0x14) |= 1;
    }
    if (anim_script != 0) {
        func_8003DB94(sprite, anim_script, 0);
    }
}
