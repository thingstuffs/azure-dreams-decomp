#include "common.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738(void *, u8, s8);
extern void func_80047784(void *, u8, s32);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s16 func_800BCB04(u16, u16, s16);


extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern void D_801534D4(void);
extern u8 D_801560E0[];
extern u8 D_801560E8[];
extern Callback D_80156168[];


typedef struct S_80152DA8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80152DA8_0;   /* arg1 in func_80152DA8 */

typedef struct S_80152DA8_1 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80152DA8_1;   /* arg2 in func_80152DA8 */

typedef struct S_80152DA8_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80152DA8_2;   /* state in func_80152DA8 */

/* Updates entity callbacks, movement, directional animation, and ground height. */
void func_80152DA8(void *entity_in, void *motion_in, void *sprite_in)
{
    register void *entity ASM_REG("$17") = entity_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *motion = motion_in;
    register void *sprite ASM_REG("$20") = sprite_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *entity_state ASM_REG("$19") = entity;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    u8 *anim_entry;
    s32 anim_direction;
    s32 facing_angle;
    void *anim_sprite;
    register u8 *anim_table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 prev_state;
    s16 direction;
    s16 sprite_direction;
    s32 height;
    s32 bob_step;
    register s32 bob_angle ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 height_bits ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 ground_height;
    s16 ground_delta;
    u16 sprite_flags;
    register u16 bob_tick ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u32 entity_flags;
    s32 bob_offset;
    Callback paused_callback;
    Callback update_callback;

    if (D_80083462 & 0x2000) {
        paused_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (paused_callback == (Callback)D_801534D4) {
            ASM_KEEP(entity_in);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            paused_callback(entity_in, motion_in, sprite_in, entity_in);
            return;
        }
        (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        do {
            return;
        } while (0);
    }

       /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    prev_state = (s8)(*(u8 *)((u8 *)entity + 0x6D));
    if (func_800A9E70(entity, motion, sprite, entity) != 0) {
        return;
    }

    update_callback = (*(Callback *)((u8 *)entity + 0x8C));
    if (update_callback != 0) {
        update_callback(entity, motion, sprite, entity);
    }
    D_80156168[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, sprite, entity);
    if ((s16)prev_state != (*(s8 *)((u8 *)entity + 0x6D))) {
        func_800AA36C(entity, motion, sprite, entity);
    }

    ((S_80152DA8_0 *)motion)->unk_00.at00.v += ((S_80152DA8_0 *)motion)->unk_0C;
    ((S_80152DA8_0 *)motion)->unk_04.at00.v += ((S_80152DA8_0 *)motion)->unk_10;

    if (!((*(u32 *)((u8 *)entity + 0x1C)) & 0x40000) &&
        !((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
        ((S_80152DA8_0 *)motion)->unk_14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity + 0x9D))++;
    } else {
        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
    }
    (*(s32 *)((u8 *)entity + 0x90)) += ((S_80152DA8_0 *)motion)->unk_14;
    sprite_flags = ((S_80152DA8_1 *)sprite)->unk_14;

    if (!(sprite_flags & 0x8000)) {
        direction = ((D_80083228 + ((S_80152DA8_2 *)entity_state)->unk_2A + 0x100) >> 9) & 7;
        sprite_direction = direction;
        if ((*(s16 *)((u8 *)entity + 0x94)) != sprite_direction) {
            func_80047738(sprite,
                (*(u8 *)((u8 *)(((S_80152DA8_1 *)sprite)->unk_2C) + sprite_direction)),
                ((S_80152DA8_1 *)sprite)->unk_04.s8);
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }
        {
            u32 flip_flags;
            if (D_8006CCF8[sprite_direction] != 0) {
                flip_flags = ((S_80152DA8_1 *)sprite)->unk_14 | 1;
            } else {
                flip_flags = ((S_80152DA8_1 *)sprite)->unk_14 & 0xFFFE;
            }
            ((S_80152DA8_1 *)sprite)->unk_14 = flip_flags;
        }
        func_800A020C(((S_80152DA8_2 *)entity_state)->unk_1C.s, (u8 *)sprite + 0xC);
        if (!(((S_80152DA8_2 *)entity_state)->unk_1C.u & 0x20)) {
            if (!(((S_80152DA8_1 *)sprite)->unk_14 & 0x40)) {
                func_800478B8(sprite);
            }
        } else {
            ((S_80152DA8_1 *)sprite)->unk_14 |= 0x7000;
            ((S_80152DA8_2 *)entity_state)->unk_1C.u &= 0xFFFBFFFF;
        }

        {
            u32 motion_flags;
            motion_flags = ((S_80152DA8_2 *)entity_state)->unk_1C.u & 0xF7FFFFFF;
            ((S_80152DA8_2 *)entity_state)->unk_1C.u = motion_flags;
            motion_flags &= 0x40000;
            if (!motion_flags) {
                goto reset_offset;
            }
        }

        if (!(((S_80152DA8_1 *)sprite)->unk_14 & 0x40)) {
            if (((S_80152DA8_1 *)sprite)->unk_2C == D_801560E0) {
                if (((S_80152DA8_1 *)sprite)->unk_04.u16 == 0x100) {
                    (*(u16 *)((u8 *)entity + 0x9E)) = 0;
                }
                bob_tick = (*(u16 *)((u8 *)entity + 0x9E));
                bob_step = (s32)((u32)bob_tick << 16) >> 16;
                bob_angle = bob_step * 0xE3;
                bob_tick++;
                (*(u16 *)((u8 *)entity + 0x9E)) = bob_tick;
                (*(s32 *)((u8 *)entity + 0xA0)) = func_800644B8(bob_angle) << 7;
                if (((S_80152DA8_1 *)sprite)->unk_04.u16 == 0x103) {
                    anim_table = D_801560E8;
                    (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
                    anim_direction = D_80083228;
                    facing_angle = ((S_80152DA8_2 *)entity_state)->unk_2A;
                    anim_sprite = sprite;
                    anim_direction = ((anim_direction + facing_angle + 0x100) >> 9) & 7;
                    anim_entry = &anim_table[anim_direction];
                    goto play_animation_1;
                }
            } else if (((S_80152DA8_1 *)sprite)->unk_2C == D_801560E8) {
                bob_tick = (*(u16 *)((u8 *)entity + 0x9E));
                bob_step = (s32)((u32)bob_tick << 16) >> 16;
                bob_angle = bob_step * 0xE3;
                bob_tick++;
                (*(u16 *)((u8 *)entity + 0x9E)) = bob_tick;
                (*(s32 *)((u8 *)entity + 0xA0)) = func_800644B8(bob_angle) << 7;
                if (((S_80152DA8_1 *)sprite)->unk_04.u16 == 0x103) {
                    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801560E0;
                    anim_direction = D_80083228;
                    facing_angle = ((S_80152DA8_2 *)entity_state)->unk_2A;
                    anim_sprite = sprite;
                    anim_direction = ((anim_direction + facing_angle + 0x100) >> 9) & 7;
                    anim_entry = &D_801560E0[anim_direction];
play_animation_1:
                    func_80047784(anim_sprite, *anim_entry, 0);
                }
            }
        }

        if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
            s32 height_adjust = -0x20;
            height = (*(s16 *)((u8 *)entity + 0x92));
            height_bits = (*(u16 *)((u8 *)entity + 0x92));
            if (height_adjust < height) {
                height_adjust = height_bits - 8;
                (*(s16 *)((u8 *)entity + 0x92)) = height_adjust;
                goto final_adjustment;
            }
            goto low_height_adjustment;
        }
        goto final_adjustment;
    }

    ((S_80152DA8_1 *)sprite)->unk_14 = (sprite_flags & 0x800)
        ? (sprite_flags & 0x8FFF)
        : (sprite_flags | 0x7000);
    ((S_80152DA8_2 *)entity_state)->unk_1C.u &= 0xF7FFFFFF;
    if (!(((S_80152DA8_2 *)entity_state)->unk_1C.u & 0x40000)) {
reset_offset:
        bob_offset = (*(s32 *)((u8 *)entity + 0xA0));
        (*(u16 *)((u8 *)entity + 0x9E)) = 0;
        (*(s32 *)((u8 *)entity + 0xA0)) = 0;
        (*(s32 *)((u8 *)entity + 0x90)) -= bob_offset;
        if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
            ground_height = func_800BCB04(((S_80152DA8_0 *)motion)->unk_00.at02.v,
                ((S_80152DA8_0 *)motion)->unk_04.at02.v,
                (s16)(((S_80152DA8_2 *)entity_state)->unk_88 - 0x20));
            ground_delta = ground_height - ((S_80152DA8_2 *)entity_state)->unk_88;
            if (ground_delta < (*(s16 *)((u8 *)entity + 0x92))) {
                (*(s16 *)((u8 *)entity + 0x92)) = ground_delta;
                (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                ((S_80152DA8_0 *)motion)->unk_14 = 0;
                ((S_80152DA8_2 *)entity_state)->unk_1C.u |= 0x08000000;
                goto final_adjustment;
            }
        }
        goto final_adjustment;
    }

    if (!(((S_80152DA8_1 *)sprite)->unk_14 & 0x40)) {
        if (((S_80152DA8_1 *)sprite)->unk_2C == D_801560E0) {
            if (((S_80152DA8_1 *)sprite)->unk_04.u16 == 0x100) {
                (*(u16 *)((u8 *)entity + 0x9E)) = 0;
            }
            bob_tick = (*(u16 *)((u8 *)entity + 0x9E));
            bob_step = (s32)((u32)bob_tick << 16) >> 16;
            bob_angle = bob_step * 0xE3;
            bob_tick++;
            (*(u16 *)((u8 *)entity + 0x9E)) = bob_tick;
            (*(s32 *)((u8 *)entity + 0xA0)) = func_800644B8(bob_angle) << 7;
            if (((S_80152DA8_1 *)sprite)->unk_04.u16 == 0x103) {
                anim_table = D_801560E8;
                (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
                anim_direction = D_80083228;
                facing_angle = ((S_80152DA8_2 *)entity_state)->unk_2A;
                anim_sprite = sprite;
                anim_direction = ((anim_direction + facing_angle + 0x100) >> 9) & 7;
                anim_entry = &anim_table[anim_direction];
                goto play_animation_2;
            }
        } else if (((S_80152DA8_1 *)sprite)->unk_2C == D_801560E8) {
            bob_tick = (*(u16 *)((u8 *)entity + 0x9E));
            bob_step = (s32)((u32)bob_tick << 16) >> 16;
            bob_angle = bob_step * 0xE3;
            bob_tick++;
            (*(u16 *)((u8 *)entity + 0x9E)) = bob_tick;
            (*(s32 *)((u8 *)entity + 0xA0)) = func_800644B8(bob_angle) << 7;
            if (((S_80152DA8_1 *)sprite)->unk_04.u16 == 0x103) {
                (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801560E0;
                anim_direction = D_80083228;
                facing_angle = ((S_80152DA8_2 *)entity_state)->unk_2A;
                anim_sprite = sprite;
                anim_direction = ((anim_direction + facing_angle + 0x100) >> 9) & 7;
                anim_entry = &D_801560E0[anim_direction];
play_animation_2:
                func_80047784(anim_sprite, *anim_entry, 0);
            }
        }
    }

    if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
        s32 height_adjust = -0x20;
        height = (*(s16 *)((u8 *)entity + 0x92));
        height_bits = (*(u16 *)((u8 *)entity + 0x92));
        if (height_adjust < height) {
            height_adjust = height_bits - 8;
            (*(s16 *)((u8 *)entity + 0x92)) = height_adjust;
        } else {
low_height_adjustment:
            height_adjust = height < -0x28;
            if (height_adjust) {
                height_adjust = height_bits + 8;
                (*(s16 *)((u8 *)entity + 0x92)) = height_adjust;
            }
        }
    }

final_adjustment:
    entity_flags = ((S_80152DA8_2 *)entity_state)->unk_1C.u;
    if (entity_flags & 0x40000000) {
        ((S_80152DA8_2 *)entity_state)->unk_1C.u = entity_flags & 0xBFFFFFFF;
        ground_height = func_800BCB04(
            (((S_80152DA8_1 *)sprite)->unk_24 << 6) | 0x20,
            (((S_80152DA8_1 *)sprite)->unk_25 << 6) | 0x20,
            (s16)(((S_80152DA8_2 *)entity_state)->unk_88 - 0x20));
        if (ground_height < 0x200) {
            (*(s16 *)((u8 *)entity + 0x92)) =
                (((S_80152DA8_2 *)entity_state)->unk_88 - ground_height) +
                (*(u16 *)((u8 *)entity + 0x92));
            ((S_80152DA8_2 *)entity_state)->unk_88 = ground_height;
        }
    }

    ((S_80152DA8_0 *)motion)->unk_0A = ((S_80152DA8_2 *)entity_state)->unk_88 +
        (*(u16 *)((u8 *)entity + 0x92)) - (*(u16 *)((u8 *)entity + 0xA2));
    ((S_80152DA8_1 *)sprite)->unk_14 |= 0x40;
}
