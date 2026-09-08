#include "common.h"

#define F8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define FS8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define F16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define FS16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define F32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define FPTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern u8 D_801713A8[];
extern u8 D_8017449C[];
extern u8 D_801744B4[];
extern u8 D_801744BC[];
extern u8 D_801744C4[];
extern u8 D_801744CC[];

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

/* Updates a staged movement action, its velocity, and directional animation. */
void func_80172700(void *action_arg, void *motion_arg, void *sprite_arg, void *actor_arg)
{
    void *action;
    register void *motion ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
    void *sprite;
    void *actor;
    s32 step_x;
    s32 step_y;
    s32 phase_ticks;
    s32 state;
    s32 dir_offset;
    register s32 result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 adjustment ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    void *turn_actor;
    u16 flags;
    register u8 *anim_table ASM_REG("$5");   /* MATCH pin: keeps a constant in a register as retail does */
    register u8 *dir_x ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u8 *dir_y ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    action = action_arg;
    motion = motion_arg;
    sprite = sprite_arg;
    actor = actor_arg;
    ASM_KEEP4_NV(action, motion, sprite, actor);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    dir_x = D_8006CCD8;
    dir_y = D_8006CCE8;
    dir_offset = (F16(actor, 0x2A) >> 8) & 0xE;
    step_x = *(s16 *)(dir_x + dir_offset);
    step_y = *(s16 *)(dir_y + dir_offset);
    state = F8(action, 0x9B);
    F16(action, 0x96)--;

    if (state == 2) goto state_2;
    if (state < 3) {
        if (state == 0) goto state_0;
        if (state == 1) goto state_1;
        goto done;
    }
    if (state == 4) goto state_4;
    if (state <= 3) goto state_3;
    if (state == 0xFF) goto state_ff;
    goto done;

state_0:
    flags = F16(sprite, 0x14);
    turn_actor = actor;
    if (flags & 0x8000) {
        F8(action, 0x9B) = 0xFF;
        F16(sprite, 0x14) |= 0x6000;
        func_8009C12C(turn_actor, sprite, FS16(turn_actor, 0x2A), 1);
        goto done;
    }
    if (!(flags & 0xE000)) goto done;
    anim_table = D_801744B4;
    FPTR(sprite, 0x2C) = anim_table;
    result = (D_80083228 + FS16(actor, 0x2A) + 0x100) >> 9;
    func_80047784(sprite, anim_table[result & 7], 0);
    F32(motion, 0xC) = (-step_x) << 18;
    F32(motion, 0x10) = (-step_y) << 18;
    F16(action, 0x98) |= 8;
    F32(actor, 0x1C) &= 0xF7FFFFFF;
    F32(actor, 0x1C) &= 0xFFFBFFFF;
    F16(action, 0x96) = 4;
    F32(motion, 0x14) = 0xFFFE8000;
    goto increment;

state_1:
    result = F32(motion, 0x14);
    F32(motion, 0x14) = result + (result >> 2);
    if (FS16(action, 0x96) > 0) goto done;
    adjustment = 8;
    result = F8(action, 0x9B);
    F16(action, 0x96) = adjustment;
    goto increment_loaded;

state_2:
    result = F32(motion, 0xC);
    adjustment = F32(motion, 0x10);
    result -= result >> 3;
    adjustment -= adjustment >> 3;
    F32(motion, 0xC) = result;
    result = F32(motion, 0x14);
    F32(motion, 0x10) = adjustment;
    result -= result >> 3;
    F32(motion, 0x14) = result;
    phase_ticks = 4;
    if (FS16(action, 0x96) == phase_ticks) {
        anim_table = D_801744BC;
        F32(motion, 0xC) = 0;
        F32(motion, 0x10) = 0;
        F32(motion, 0x14) = 0;
        FPTR(sprite, 0x2C) = anim_table;
        result = (D_80083228 + FS16(actor, 0x2A) + 0x100) >> 9;
        func_80047784(sprite, anim_table[result & 7], 0);
    }
    if (FS16(action, 0x96) > 0) goto done;
    if (!(F16(sprite, 0x14) & 0xE000)) goto done;
    F16(action, 0x96) = phase_ticks;
    result = step_x << 18;
    adjustment = step_x << 17;
    F32(motion, 0xC) = result + adjustment;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    result = step_y << 18;
    adjustment = step_y << 17;
    result += adjustment;
    F32(motion, 0x10) = result;
    anim_table = D_801744C4;
    FPTR(sprite, 0x2C) = anim_table;
    result = (D_80083228 + FS16(actor, 0x2A) + 0x100) >> 9;
    func_80047784(sprite, anim_table[result & 7], 0);
    goto increment;

state_3:
    F32(action, 0x90) += 0x80000;
    F32(motion, 0xC) += step_x << 18;
    F32(motion, 0x10) += step_y << 18;
    if (FS16(action, 0x96) == 2) {
        func_800A56E0(0x809);
    }
    turn_actor = actor;
    if (FS16(action, 0x96) > 0) goto done;
    func_8009C12C(turn_actor, sprite, FS16(turn_actor, 0x2A), 1);

increment:
    result = F8(action, 0x9B);
increment_loaded:
    result++;
    F8(action, 0x9B) = result;
    goto done;

state_4:
    F32(action, 0x90) += 0x80000;
    if (!(F16(sprite, 0x14) & 0xE000)) goto done;
    anim_table = D_801744CC;
    FPTR(sprite, 0x2C) = anim_table;
    result = (D_80083228 + FS16(actor, 0x2A) + 0x100) >> 9;
    func_80047784(sprite, anim_table[result & 7], 0);
    F32(motion, 0x14) = 0;
    F32(action, 0x90) = 0;
    F16(action, 0x98) &= 0xFFF7;
    F32(actor, 0x1C) |= 0x08000000;
    F8(action, 0x9B) = 0xFF;
    goto done;

state_ff:
    result = F8(sprite, 0x24) << 6;
    adjustment = FS16(motion, 2);
    adjustment -= 0x20;
    result -= adjustment;
    result <<= 15;
    result >>= 1;
    F32(motion, 0xC) = result;
    result = F8(sprite, 0x25) << 6;
    adjustment = FS16(motion, 6);
    adjustment -= 0x20;
    result -= adjustment;
    result <<= 15;
    result >>= 1;
    F32(motion, 0x10) = result;
    if (!(F16(sprite, 0x14) & 0xE000)) goto done;
    F32(motion, 0x10) = 0;
    F32(motion, 0xC) = 0;
    F32(actor, 0x1C) |= 0x40000;
    func_800A2B04(motion, F8(sprite, 0x24), F8(sprite, 0x25));
    func_800AD594(actor, 0x100);
    FPTR(action, 0x8C) = D_801713A8;
    D_8008346C = 0;
    func_800A4ACC(actor);
    anim_table = D_8017449C;
    FPTR(sprite, 0x2C) = anim_table;
    result = (D_80083228 + FS16(actor, 0x2A) + 0x100) >> 9;
    func_80047784(sprite, anim_table[result & 7], 0);
    if (FS8(actor, 0x6D) == 0) {
        F16(actor, 0x46) &= 0x7FFF;
        goto done;
    }
    D_800E3DE8 = (u8 *)actor - 0x20;

done:
    return;
}
