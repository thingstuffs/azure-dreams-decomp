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
extern u8 D_80171FA4[];
extern u8 D_80175C78[];
extern u8 D_80175CA8[];
extern u8 D_80080000[];

/* Updates action movement and directional animation through three states. */
void func_80173DD4(void *action, void *motion, void *object, void *actor)
{
    s32 delta_x;
    s32 delta_y;
    s32 direction_off;
    s32 facing_idx;
    s32 object_type;
    s32 anim_table;
    s32 next_tick;
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
    u8 *facing_ptr;

    flags = U16(object, 0x14);
    if (flags & 0x8000) {
        U16(object, 0x14) = flags | 0x6000;
        U8(action, 0x9B) = 2;
        func_8009C12C(actor, object, S16(actor, 0x2A), 1);
        return;
    }
    if ((flags & 0x6000) == 0) {
        goto done;
    }
    anim_table = 0x80170000;
    if (S16(action, 0x92) != 0) {
        goto done;
    }
    ASM_KEEP_NV(anim_table);
    anim_table += 0x5C78;
    facing_ptr = (u8 *)D_80080000;
    PTR(object, 0x2C) = (void *)anim_table;
    facing_idx = (*(s16 *)(facing_ptr + 0x3228) + S16(actor, 0x2A) + 0x100) >> 9;
    facing_idx &= 7;
    facing_ptr = (u8 *)(facing_idx + anim_table);
    func_80047784(object, *facing_ptr, 0);
    U16(action, 0x96) = 0;
    func_800A56E0(0x808);
    goto advance_state;
}

state_one:
{
    u8 *direction_base;
    u8 *direction_base_2;
    s32 motion_x;
    s32 motion_y;
    s32 signed_value;

    anim_table = U16(action, 0x96);
    direction_base = (u8 *)&D_8006CCD8;
    next_tick = anim_table + 1;
    anim_table -= 3;
    U16(action, 0x96) = next_tick;
    direction_off = (U16(actor, 0x2A) >> 8) & 0xE;
    anim_table = (u32)anim_table < 8U;
    direction_base = (u8 *)(direction_off + (s32)direction_base);
    delta_x = *(s16 *)direction_base;
    direction_base_2 = (u8 *)&D_8006CCE8;
    signed_value = *(s16 *)((s32)(direction_off + (s32)direction_base_2));
    delta_x = -delta_x;
    delta_x <<= 16;
    signed_value = -signed_value;
    delta_y = signed_value << 16;
    if (anim_table) {
        motion_x = S32(motion, 0xC) - delta_x;
        motion_y = S32(motion, 0x10) - delta_y;
        goto store_movement;
    }
    signed_value = (s16)next_tick;
    if (signed_value < 0x12) {
        motion_x = S32(motion, 0xC) + delta_x;
        motion_y = S32(motion, 0x10) + delta_y;
store_movement:
        S32(motion, 0xC) = motion_x;
        S32(motion, 0x10) = motion_y;
    } else {
        S32(motion, 0x14) = 0;
        S32(motion, 0x10) = 0;
        S32(motion, 0xC) = 0;
    }
    object_type = S8(object, 4);
    if (object_type == 5 && (U16(object, 0x14) & 0x9000)) {
        func_8009C12C(actor, object, S16(actor, 0x2A), 1);
    }
    {
        u8 *facing_ptr;

        anim_table = 0x80170000;
        if ((U16(object, 0x14) & 0x6000) == 0) {
            goto done;
        }
        ASM_KEEP_NV(anim_table);
        anim_table += 0x5CA8;
        facing_ptr = (u8 *)D_80080000;
        PTR(object, 0x2C) = (void *)anim_table;
        facing_idx = (*(s16 *)(facing_ptr + 0x3228) + S16(actor, 0x2A) + 0x100) >> 9;
        facing_idx &= 7;
        facing_ptr = (u8 *)(facing_idx + anim_table);
        func_80047784(object, *facing_ptr, 0);
    }
    S32(motion, 0x14) = 0;
    S32(motion, 0x10) = 0;
    S32(motion, 0xC) = 0;
    func_800A2B04(motion, U8(object, 0x24), U8(object, 0x25));
advance_state:
    U8(action, 0x9B)++;
    return;
}

state_two:
{
    void *actor_arg;

    if ((U16(object, 0x14) & 0xE000) == 0) {
        goto done;
    }
    func_800AD594(actor, 0x100);
    actor_arg = actor;
    PTR(action, 0x8C) = D_80171FA4;
    S32(D_80080000, 0x346C) = 0;
    func_800A4ACC(actor_arg);
    U16(actor, 0x46) &= 0x7FFF;
}

done:
    return;
}
