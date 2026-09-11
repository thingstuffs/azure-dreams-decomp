#include "common.h"

#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228[];
extern s32 D_8008346C[];
extern u8 D_801710EC[];
extern u8 D_80175E88[];
extern u8 D_80175EB8[];

/* Updates the actor's directional motion and animation across three action states. */
void func_8017328C(void *action, void *motion, void *sprite, void *actor)
{
    s32 delta_x;
    s32 delta_y;
    s32 direction_offset;
    s32 facing_index;
    s32 object_type;
    register s32 frame ASM_REG("$5");
    s32 next_frame;
    u16 flags;
    s32 state;

    state = U8(action, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state >= 2) {
        goto state_two_test;
    }
    if (state == 0) {
        goto state_zero;
    }
    return;

state_two_test:
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
{
    u8 *anim_table;
    u8 *facing_ptr;

    flags = U16(sprite, 0x14);
    if (flags & 0x8000) {
        U16(sprite, 0x14) = flags | 0x6000;
        U8(action, 0x9B) = 2;
        func_8009C12C(actor, sprite, S16(actor, 0x2A), 1);
        return;
    }

    if ((flags & 0x6000) == 0) {
        goto done;
    }
    anim_table = (u8 *)0x80170000;
    if (S16(action, 0x92) != 0) {
        goto done;
    }
    ASM_KEEP_NV(anim_table);
    anim_table += 0x5E88;
    facing_ptr = (u8 *)0x80080000;
    ASM_KEEP(facing_ptr);
    PTR(sprite, 0x2C) = anim_table;
    facing_index = (*(s16 *)(facing_ptr + 0x3228) + S16(actor, 0x2A) + 0x100) >> 9;
    facing_index &= 7;
    facing_ptr = (u8 *)(facing_index + (s32)anim_table);
    func_80047784(sprite, *facing_ptr, 0);
    U16(action, 0x96) = 0;
    func_800A56E0(0x808);
    goto advance_state;
}

state_one:
{
    register u8 *direction_base ASM_REG("$2");
    register s32 next_x ASM_REG("$2");
    s32 next_y;
    s32 signed_frame;
    s32 step_y;

    direction_base = (u8 *)0x80070000;
    ASM_KEEP_NV(direction_base);
    frame = U16(action, 0x96);
    direction_base -= 0x3328;
    next_frame = frame + 1;
    frame -= 3;
    U16(action, 0x96) = next_frame;
    direction_offset = (U16(actor, 0x2A) >> 8) & 0xE;
    frame = (u32)frame < 8U;
    direction_base = (u8 *)(direction_offset + (s32)direction_base);
    ASM_KEEP_NV(direction_base);
    delta_x = *(s16 *)direction_base;
    direction_base = (u8 *)0x80070000;
    ASM_KEEP_NV(direction_base);
    direction_base -= 0x3318;
    direction_offset = direction_offset + (s32)direction_base;
    step_y = *(s16 *)direction_offset;
    delta_x = -delta_x;
    delta_x <<= 16;
    step_y = -step_y;
    delta_y = step_y << 16;
    if (frame) {
        next_x = S32(motion, 0xC) - delta_x;
        next_y = S32(motion, 0x10) - delta_y;
        goto store_motion;
    }
    signed_frame = (s16)next_frame;
    if (signed_frame < 0x12) {
        next_x = S32(motion, 0xC) + delta_x;
        next_y = S32(motion, 0x10) + delta_y;
store_motion:
        S32(motion, 0xC) = next_x;
        S32(motion, 0x10) = next_y;
    } else {
        ASM_CLOBBER("$5");
        S32(motion, 0x14) = 0;
        S32(motion, 0x10) = 0;
        S32(motion, 0xC) = 0;
    }
    object_type = S8(sprite, 4);
    if (object_type == 5) {
        if (U16(sprite, 0x14) & 0x1000) {
            goto call_c12c;
        }
    }
    if ((U16(sprite, 0x14) & 0x8000) == 0) {
        goto after_c12c;
    }
call_c12c:
    func_8009C12C(actor, sprite, S16(actor, 0x2A), 1);
after_c12c:
    {
        u8 *anim_table;
        u8 *facing_ptr;

        anim_table = (u8 *)0x80170000;
        if ((U16(sprite, 0x14) & 0xE000) == 0) {
            goto done;
        }
        ASM_KEEP_NV(anim_table);
        anim_table += 0x5EB8;
        facing_ptr = (u8 *)0x80080000;
        ASM_KEEP(facing_ptr);
        PTR(sprite, 0x2C) = anim_table;
        facing_index = (*(s16 *)(facing_ptr + 0x3228) + S16(actor, 0x2A) + 0x100) >> 9;
        facing_index &= 7;
        facing_ptr = (u8 *)(facing_index + (s32)anim_table);
        func_80047784(sprite, *facing_ptr, 0);
    }
    S32(motion, 0x14) = 0;
    S32(motion, 0x10) = 0;
    S32(motion, 0xC) = 0;
    func_800A2B04(motion, U8(sprite, 0x24), U8(sprite, 0x25));
advance_state:
    U8(action, 0x9B)++;
    return;
}

state_two:
{
    u8 *globals_base;

    if ((U16(sprite, 0x14) & 0xE000) == 0) {
        goto done;
    }
    func_800AD594(actor, 0x100);
    PTR(action, 0x8C) = D_801710EC;
    do {
        globals_base = (u8 *)0x80080000;
    } while (0);
    ASM_KEEP(globals_base);
    S32(globals_base, 0x346C) = 0;
    U16(actor, 0x46) &= 0x7FFF;
    func_800A4ACC(actor);
}

done:
    return;
}
