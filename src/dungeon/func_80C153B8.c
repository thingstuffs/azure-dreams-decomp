#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*EntityCallback)(void *, void *, void *, void *);

extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801713A8[];
extern u8 D_80174494[];
extern u8 D_8017449C[];
extern EntityCallback D_80174504[];

extern void func_80047738();
extern void func_80047784();
extern void func_800478B8();
extern s32 func_800644B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s16 func_800BCB04();


typedef struct S_80170BB8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170BB8_0;   /* motion in func_80170BB8 */

typedef struct S_80170BB8_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80170BB8_1;   /* object in func_80170BB8 */

typedef struct S_80170BB8_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80170BB8_2;   /* actor2 in func_80170BB8 */

typedef struct S_if_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_if_0;   /* actor2 in if */

/* Update actor callbacks, motion, directional animation, and ground-relative height. */
void func_80170BB8(void *actor_arg, void *motion_arg, void *object_arg)
{
    u16 initial_flags = D_80083462;
    register void *actor ASM_REG("$17") = actor_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *motion = motion_arg;
    void *object = object_arg;
    s32 bob = 0;
    register void *actor_state ASM_REG("$18") = actor;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 previous_index;
    register s16 direction ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 ground;
    s32 ground_offset;
    s32 bob_wave;
    s32 height;
    EntityCallback callback;
    u8 *animation_table;
    u16 status_flags;
    u16 movement_flags;
    register u32 actor_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    if (initial_flags & 0x2000) {
        EntityCallback early_callback = (*(EntityCallback *)((u8 *)actor + (0x8C)));
        if ((void *)early_callback == (void *)D_801713A8) {
            register void *callback_actor ASM_REG("$4") = actor_arg;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            ASM_KEEP_NV(callback_actor);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            early_callback(actor_arg, motion_arg, object_arg, callback_actor);
            return;
        } else {
            (*(u8 *)((u8 *)actor + (0x71))) &= 0x7F;
            return;
        }
    }

    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(object);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    previous_index = (s8)(*(u8 *)((u8 *)actor + (0x6D)));
    if (func_800A9E70(actor, motion, object, actor) != 0) {
        return;
    }

    callback = (*(EntityCallback *)((u8 *)actor + (0x8C)));
    if (callback != 0) {
        callback(actor, motion, object, actor);
    }
    D_80174504[(*(u8 *)((u8 *)actor + (0x9A)))](actor, motion, object, actor);
    if ((s16)previous_index != (s8)(*(u8 *)((u8 *)actor + (0x6D)))) {
        func_800AA36C(actor, motion, object, actor);
    }

    ((S_80170BB8_0 *)motion)->unk_00.at00.v += ((S_80170BB8_0 *)motion)->unk_0C;
    ((S_80170BB8_0 *)motion)->unk_04.at00.v += ((S_80170BB8_0 *)motion)->unk_10;

    if (!((*(u32 *)((u8 *)actor + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
        ((S_80170BB8_0 *)motion)->unk_14 += (s8)(*(u8 *)((u8 *)actor + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)actor + (0x9D)))++;
    } else {
        (*(volatile u8 *)((u8 *)actor + (0x9D))) = 0;
    }
    (*(s32 *)((u8 *)actor + (0x90))) += ((S_80170BB8_0 *)motion)->unk_14;
    status_flags = ((S_80170BB8_1 *)object)->unk_14;

    if (!(status_flags & 0x8000)) {
        {
            ground_offset = (D_80083228 + ((S_80170BB8_2 *)actor_state)->unk_2A + 0x100) >> 9;
            direction = ground_offset & 7;
        }
        if ((*(s16 *)((u8 *)actor + (0x94))) != direction) {
            func_80047738(object, ((S_80170BB8_1 *)object)->unk_2C[direction],
                          ((S_80170BB8_1 *)object)->unk_04);
            (*(s16 *)((u8 *)actor + (0x94))) = direction;
        }
        {
            u32 flip_flags;
            if (D_8006CCF8[direction] != 0) {
                flip_flags = ((S_80170BB8_1 *)object)->unk_14 | 1;
            } else {
                flip_flags = ((S_80170BB8_1 *)object)->unk_14 & 0xFFFE;
            }
            ((S_80170BB8_1 *)object)->unk_14 = flip_flags;
        }
        if ((*(u8 *)((u8 *)actor + (0x9A))) != 8) {
            func_800A020C(((S_80170BB8_2 *)actor_state)->unk_1C.s, (u8 *)object + 0xC);
        }

        if (!(((S_80170BB8_2 *)actor_state)->unk_1C.u & 0x20)) {
            if (!(((S_80170BB8_1 *)object)->unk_14 & 0x40)) {
                func_800478B8(object);
            }
        } else {
            ((S_80170BB8_1 *)object)->unk_14 |= 0x7000;
            ((S_80170BB8_2 *)actor_state)->unk_1C.u &= 0xFFFBFFFF;
        }

        actor_flags = ((S_80170BB8_2 *)actor_state)->unk_1C.u & 0xF7FFFFFF;
        ((S_80170BB8_2 *)actor_state)->unk_1C.u = actor_flags;
        if (actor_flags & 0x40000) {
            if (!(((S_80170BB8_1 *)object)->unk_14 & 0x40)) {
                status_flags = (*(u16 *)((u8 *)actor + (0x98)));
                if (status_flags & 0x8000) {
                    (*(u16 *)((u8 *)actor + (0x98))) = status_flags & 0x7FFF;
                    animation_table = ((S_80170BB8_1 *)object)->unk_2C;
                    if (animation_table == D_8017449C) {
                        (*(u8 * *)((u8 *)object + (0x2C))) = D_80174494;
                        func_80047784(object,
                            D_80174494[((D_80083228 + ((S_if_0 *)actor_state)->unk_2A + 0x100) >> 9) & 7],
                            0);
                    }
                    else if (animation_table == D_80174494) {
                        (*(u8 * *)((u8 *)object + (0x2C))) = D_8017449C;
                        func_80047784(object,
                            D_8017449C[((D_80083228 + ((S_if_0 *)actor_state)->unk_2A + 0x100) >> 9) & 7],
                            0);
                    }
                }
                if (((S_80170BB8_1 *)object)->unk_14 & 0x6000) {
                    (*(u16 *)((u8 *)actor + (0x98))) |= 0x8000;
                    if (((S_80170BB8_1 *)object)->unk_2C == D_80174494) {
                        (*(s16 *)((u8 *)actor + (0xA8))) = 0;
                    }
                }
                bob_wave = func_800644B8(((*(s16 *)((u8 *)actor + (0xA8))) << 12) / 21);
                bob = bob_wave >> 8;
                if ((*(u8 *)((u8 *)actor + (0x9A))) == 0x12) {
                    bob = bob_wave >> 10;
                }
                (*(s16 *)((u8 *)actor + (0xA8)))++;
            }

            if (!((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
                ground = (s16)(func_800BCB04(((S_80170BB8_0 *)motion)->unk_00.at02.v,
                    ((S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(((S_80170BB8_2 *)actor_state)->unk_88.u - 0x20)) -
                    ((S_80170BB8_2 *)actor_state)->unk_88.u);
                if ((*(s16 *)((u8 *)actor + (0x92))) > ground - 0x30) {
                    (*(s16 *)((u8 *)actor + (0x92))) = (*(s16 *)((u8 *)actor + (0x92))) - 8;
                    goto common_tail;
                }
                if (ground - 0x3A > (*(s16 *)((u8 *)actor + (0x92)))) {
                    (*(s16 *)((u8 *)actor + (0x92))) = (*(s16 *)((u8 *)actor + (0x92))) + 8;
                    goto common_tail;
                }
            }
        } else {
            movement_flags = (*(u16 *)((u8 *)actor + (0x98)));
            (*(s16 *)((u8 *)actor + (0xA8))) = 0;
            (*(u16 *)((u8 *)actor + (0x98))) = movement_flags & 0x7FFF;
            if (!(movement_flags & 8)) {
                ground_offset = func_800BCB04(((S_80170BB8_0 *)motion)->unk_00.at02.v,
                    ((S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(((S_80170BB8_2 *)actor_state)->unk_88.u - 0x20)) -
                    ((S_80170BB8_2 *)actor_state)->unk_88.s;
                if (ground_offset < (*(s16 *)((u8 *)actor + (0x92)))) {
                    (*(s16 *)((u8 *)actor + (0x92))) = ground_offset;
                    (*(u8 *)((u8 *)actor + (0x9D))) = 0;
                    ((S_80170BB8_0 *)motion)->unk_14 = 0;
                    ((S_80170BB8_2 *)actor_state)->unk_1C.u |= 0x08000000;
                    goto common_tail;
                }
            }
        }
        goto common_tail;
    }

    if (!(status_flags & 0x800)) {
        ((S_80170BB8_1 *)object)->unk_14 = status_flags | 0x7000;
    } else {
        ((S_80170BB8_1 *)object)->unk_14 = status_flags & 0x8FFF;
    }
    actor_flags = ((S_80170BB8_2 *)actor_state)->unk_1C.u & 0xF7FFFFFF;
    ((S_80170BB8_2 *)actor_state)->unk_1C.u = actor_flags;

    if (!(actor_flags & 0x40000)) {
        (*(s16 *)((u8 *)actor + (0xA8))) = 0;
        (*(s16 *)((u8 *)actor + (0x92))) -= bob;
        bob = 0;
        if (!((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
            ground_offset = func_800BCB04(((S_80170BB8_0 *)motion)->unk_00.at02.v,
                ((S_80170BB8_0 *)motion)->unk_04.at02.v,
                (s16)(((S_80170BB8_2 *)actor_state)->unk_88.u - 0x20)) -
                ((S_80170BB8_2 *)actor_state)->unk_88.s;
            if (ground_offset < (*(s16 *)((u8 *)actor + (0x92)))) {
                (*(s16 *)((u8 *)actor + (0x92))) = ground_offset;
                (*(u8 *)((u8 *)actor + (0x9D))) = 0;
                ((S_80170BB8_0 *)motion)->unk_14 = 0;
                ((S_80170BB8_2 *)actor_state)->unk_1C.u |= 0x08000000;
            }
        }
    } else {
        if (!(((S_80170BB8_1 *)object)->unk_14 & 0x40)) {
            status_flags = (*(u16 *)((u8 *)actor + (0x98)));
            if (status_flags & 0x8000) {
                (*(u16 *)((u8 *)actor + (0x98))) = status_flags & 0x7FFF;
                animation_table = ((S_80170BB8_1 *)object)->unk_2C;
                if (animation_table == D_8017449C) {
                    (*(u8 * *)((u8 *)object + (0x2C))) = D_80174494;
                    func_80047784(object,
                        D_80174494[((D_80083228 + ((S_80170BB8_2 *)actor_state)->unk_2A + 0x100) >> 9) & 7],
                        0);
                } else if (animation_table == D_80174494) {
                    (*(u8 * *)((u8 *)object + (0x2C))) = D_8017449C;
                    func_80047784(object,
                        D_8017449C[((D_80083228 + ((S_80170BB8_2 *)actor_state)->unk_2A + 0x100) >> 9) & 7],
                        0);
                }
            }
            if (((S_80170BB8_1 *)object)->unk_14 & 0x6000) {
                (*(u16 *)((u8 *)actor + (0x98))) |= 0x8000;
                if (((S_80170BB8_1 *)object)->unk_2C == D_80174494) {
                    (*(s16 *)((u8 *)actor + (0xA8))) = 0;
                }
            }
            bob_wave = func_800644B8(((*(s16 *)((u8 *)actor + (0xA8))) << 12) / 21);
            bob = bob_wave >> 8;
            if ((*(u8 *)((u8 *)actor + (0x9A))) == 0x12) {
                bob = bob_wave >> 10;
            }
            (*(s16 *)((u8 *)actor + (0xA8)))++;
        }

        if (!((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
            ground = (s16)(func_800BCB04(((S_80170BB8_0 *)motion)->unk_00.at02.v,
                ((S_80170BB8_0 *)motion)->unk_04.at02.v,
                (s16)(((S_80170BB8_2 *)actor_state)->unk_88.u - 0x20)) -
                ((S_80170BB8_2 *)actor_state)->unk_88.u);
            if ((*(s16 *)((u8 *)actor + (0x92))) > ground - 0x30) {
                (*(s16 *)((u8 *)actor + (0x92))) = (*(s16 *)((u8 *)actor + (0x92))) - 8;
            } else if (ground - 0x3A > (*(s16 *)((u8 *)actor + (0x92)))) {
                (*(s16 *)((u8 *)actor + (0x92))) = (*(s16 *)((u8 *)actor + (0x92))) + 8;
            }
        }
    }

cleanup_tail:
    (*(s16 *)((u8 *)actor + (0xA8))) = 0;
    (*(u16 *)((u8 *)actor + (0x98))) &= 0x7FFF;

common_tail:
    if (((S_80170BB8_2 *)actor_state)->unk_1C.u & 0x40000000) {
        ((S_80170BB8_2 *)actor_state)->unk_1C.u = ((S_80170BB8_2 *)actor_state)->unk_1C.u & 0xBFFFFFFF;
        ground = func_800BCB04((((S_80170BB8_1 *)object)->unk_24 << 6) | 0x20,
            (((S_80170BB8_1 *)object)->unk_25 << 6) | 0x20,
            (s16)(((S_80170BB8_2 *)actor_state)->unk_88.u - 0x20));
        if (ground < 0x200) {
            (*(s16 *)((u8 *)actor + (0x92))) += ((S_80170BB8_2 *)actor_state)->unk_88.u - ground;
            ((S_80170BB8_2 *)actor_state)->unk_88.u = ground;
        }
    }
    height = ((S_80170BB8_2 *)actor_state)->unk_88.u +
        (u16)(*(s16 *)((u8 *)actor + (0x92)));
    height += bob;
    ((S_80170BB8_0 *)motion)->unk_0A = height;
    ((S_80170BB8_1 *)object)->unk_14 |= 0x40;
}
