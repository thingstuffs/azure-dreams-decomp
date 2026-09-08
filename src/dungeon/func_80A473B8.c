#include "common.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738();
extern void func_80047784();
extern void func_800478B8();
extern s32 func_800644B8();
extern s32 func_80069EF8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s32 func_800BCB04();

extern u8 D_8006CCF8[];
extern s16 D_80083228[5];
extern u16 D_80083462[5];
extern u8 D_8017140C[];
extern u8 D_8017586C[];
extern Callback D_8017589C[];


typedef struct S_80170BB8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170BB8_0;   /* motion in func_80170BB8 */

typedef struct S_80170BB8_1 {
    u8 pad_00[0x1C];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80170BB8_1;   /* subject in func_80170BB8 */

typedef struct S_80170BB8_2 {
    u8 pad_00[0xC];
    union { u32 u32; u8 u8; } unk_0C;   /* accessed as both */
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x26];
    u32 unk_3C;
} S_80170BB8_2;   /* sprite in func_80170BB8 */

typedef struct S_80170BB8_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
} S_80170BB8_3;   /* part in func_80170BB8 */

typedef struct S_80170BB8_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80170BB8_4;   /* entity in func_80170BB8 */

void func_80170BB8(void *input0, void *input1, void *input2)
{
    register u8 *actor ASM_REG("$18") = input0;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u8 *motion = input1;
    u8 *entity = input2;
    register u8 *subject ASM_REG("$19") = actor;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *part ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *sprite ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 work ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 global_flags;
    u16 *global_flags_ptr = (u16 *)0x80080000;
    u8 *part_base;
    Callback callback;
    u16 entity_flags;
    s32 subject_flags;
    s32 ground;
    s32 correction;
    s16 reset_offset;
    register s32 velocity_limit ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 velocity_raw ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 velocity_current;
    register s32 velocity_ground ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    ASM_KEEP(global_flags_ptr);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    part_base = (*(u8 * *)((u8 *)actor + 0xA4));
    ASM_KEEP(part_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    global_flags = global_flags_ptr[0x1A31];
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    part = part_base + 0x20;

    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(subject);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(sprite);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    global_flags &= 0x2000;
    sprite = part_base + 0x28;
    if (global_flags) {
        callback = (*(Callback *)((u8 *)actor + 0x8C));
        if (callback == (Callback)D_8017140C) {
            callback(input0, input1, input2, input0);
            goto done;
        }
        (*(u8 *)((u8 *)actor + 0x71)) &= 0x7F;
        goto done;
    }


    {
        void *call0 = actor;
        register void *call1 ASM_REG("$5") = motion;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register void *call2 ASM_REG("$6") = entity;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        void *call3;
        register u32 old_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        old_state = (*(u8 *)((u8 *)actor + 0x6D));
        call3 = actor;
        old_state <<= 24;
        ASM_KEEP(call0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(call3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        work = (s32)old_state >> 24;
        if (func_800A9E70(call0, call1, call2, call3) != 0) {
            goto done;
        }
    }

    {
        Callback callback2;

        callback2 = (*(Callback *)((u8 *)actor + 0x8C));
        if (callback2 != 0) {
            callback2(actor, motion, entity, actor);
        }
    }
    D_8017589C[(*(u8 *)((u8 *)actor + 0x9A))](actor, motion, entity, actor);

    if ((s16)work != (*(s8 *)((u8 *)actor + 0x6D))) {
        func_800AA36C(actor, motion, entity, actor);
    }

    ((S_80170BB8_0 *)motion)->unk_00.at00.v += ((S_80170BB8_0 *)motion)->unk_0C;
    ((S_80170BB8_0 *)motion)->unk_04.at00.v += ((S_80170BB8_0 *)motion)->unk_10;

    if (!((*(u32 *)((u8 *)actor + 0x1C)) & 0x00040000) &&
        !((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
        ((S_80170BB8_0 *)motion)->unk_14 += (*(s8 *)((u8 *)actor + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)actor + 0x9D))++;
    } else {
        (*(u8 *)((u8 *)actor + 0x9D)) = 0;
    }
    (*(s32 *)((u8 *)actor + 0x90)) += ((S_80170BB8_0 *)motion)->unk_14;

    if (((S_80170BB8_1 *)subject)->unk_1C.u & 0x200) {
        if ((*(u16 *)((u8 *)actor + 0x98)) & 0x4000) {
            ((S_80170BB8_2 *)sprite)->unk_3C = 0x00808080;
            ((S_80170BB8_2 *)sprite)->unk_0C.u32 = 0x00808080;
        } else if (((S_80170BB8_2 *)sprite)->unk_0C.u8 >= 8) {
            ((S_80170BB8_2 *)sprite)->unk_3C += 0xFFF7F7F8;
            ((S_80170BB8_2 *)sprite)->unk_0C.u32 = ((S_80170BB8_2 *)sprite)->unk_3C;
        }

        if (((S_80170BB8_2 *)sprite)->unk_14 & 0x6000) {
            if (((S_80170BB8_2 *)sprite)->unk_0C.u8 < 8 ||
                ((*(u16 *)((u8 *)actor + 0x98)) & 0x4000)) {
                u16 state = (*(u16 *)((u8 *)actor + 0x98));

                if (!(state & 0x8000)) {
                    (*(u16 *)((u8 *)actor + 0x98)) = state | 0xC000;
                    ((S_80170BB8_3 *)part)->unk_04 |= 0x8000;
                    (*(u16 *)((u8 *)actor + 0xA0)) =
                        (func_80069EF8() & 7) + 0x10;
                }
            }
        }

        work = 0;
        if (--(*(s16 *)((u8 *)actor + 0xA0)) == 0) {
            (*(u16 *)((u8 *)actor + 0x98)) &= 0x7FFF;
            ((S_80170BB8_3 *)part)->unk_04 &= 0x7FFF;
            if (((S_80170BB8_3 *)part)->unk_02 > 0) {
                do {
                    func_80047784(sprite, 0x1C, 0);
                    sprite += 0x30;
                    work++;
                } while (work < ((S_80170BB8_3 *)part)->unk_02);
            }
        }
    } else {
        if (((S_80170BB8_2 *)sprite)->unk_0C.u8 >= 0x80) {
            ((S_80170BB8_2 *)sprite)->unk_3C = 0x00808080;
            ((S_80170BB8_2 *)sprite)->unk_0C.u32 = 0x00808080;
        } else {
            ((S_80170BB8_2 *)sprite)->unk_3C += 0x00080808;
            ((S_80170BB8_2 *)sprite)->unk_0C.u32 = ((S_80170BB8_2 *)sprite)->unk_3C;
        }

        if ((*(u16 *)((u8 *)actor + 0x98)) & 0x4000) {
            (*(u16 *)((u8 *)actor + 0x98)) &= 0x3FFF;
            ((S_80170BB8_3 *)part)->unk_04 &= 0x7FFF;
        }

        if ((*(u16 *)((u8 *)actor + 0x98)) & 0x1000) {
            func_80047784(sprite, 0x1D, 0);
            func_80047784(sprite + 0x30, 0x1D, 0);
            (*(u16 *)((u8 *)actor + 0x98)) &= 0xEFFF;
        } else if (((*(u16 *)((u8 *)actor + 0x98)) & 0x2000) &&
                   (((S_80170BB8_2 *)sprite)->unk_14 & 0x6000)) {
            s32 effect_mode;

            if ((*(u8 *)((u8 *)actor + 0x9A)) == 7) {
                func_80047784(sprite, 0x19, 0);
                func_80047784(sprite + 0x30, 0x24, 0);
            } else {
                s32 random_value;

                func_80047784(sprite, 0x19, 0);
                random_value = func_80069EF8();
                effect_mode = 0x24;
                if (random_value & 3) {
                    effect_mode = 0x19;
                }
                func_80047784(sprite + 0x30, effect_mode, 0);
            }
        }
    }

    entity_flags = ((S_80170BB8_4 *)entity)->unk_14;
    if (!(entity_flags & 0x8000)) {
        {
            register s32 direction_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            direction_value =
                D_80083228[0] + ((S_80170BB8_1 *)subject)->unk_2A + 0x100;
            work = (direction_value >> 9) & 7;
        }
        {
            register s32 direction_copy ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

            if ((*(s16 *)((u8 *)actor + 0x94)) != (direction_copy = work)) {
                func_80047738(entity,
                              (*(u8 *)((u8 *)(((S_80170BB8_4 *)entity)->unk_2C) + direction_copy)),
                              ((S_80170BB8_4 *)entity)->unk_04);
                (*(s16 *)((u8 *)actor + 0x94)) = work;
            }

            if (D_8006CCF8[direction_copy] != 0) {
                ((S_80170BB8_4 *)entity)->unk_14 |= 1;
            } else {
                ((S_80170BB8_4 *)entity)->unk_14 &= 0xFFFE;
            }
        }

        if ((*(u8 *)((u8 *)actor + 0x9A)) != 8) {
            func_800A020C(((S_80170BB8_1 *)subject)->unk_1C.s, entity + 0xC);
        }

        if (!(((S_80170BB8_1 *)subject)->unk_1C.s & 0x20)) {
            if (!(((S_80170BB8_4 *)entity)->unk_14 & 0x40)) {
                func_800478B8(entity);
            }
        } else {
            ((S_80170BB8_4 *)entity)->unk_14 |= 0x7000;
            ((S_80170BB8_1 *)subject)->unk_1C.u &= 0xFFFBFFFF;
        }

        ((S_80170BB8_1 *)subject)->unk_1C.u &= 0xF7FFFFFF;
        subject_flags = ((S_80170BB8_1 *)subject)->unk_1C.u;

        if (subject_flags & 0x00040000) {
            if (!(((S_80170BB8_4 *)entity)->unk_14 & 0x40) &&
                ((S_80170BB8_4 *)entity)->unk_2C == D_8017586C) {
                u16 count = (*(u16 *)((u8 *)actor + 0xB8));

                (*(u16 *)((u8 *)actor + 0xB8)) = count + 1;
                (*(s32 *)((u8 *)actor + 0xB4)) +=
                    func_800644B8((s16)count * 0xAA) << 5;
            }

            if (!((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
                velocity_ground = (s16)(func_800BCB04(
                    ((S_80170BB8_0 *)motion)->unk_00.at02.v, ((S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(((S_80170BB8_1 *)subject)->unk_88 - 0x20)) -
                                         ((S_80170BB8_1 *)subject)->unk_88);
                velocity_current = (*(s16 *)((u8 *)actor + 0x92));
                velocity_raw = (*(volatile u16 *)((u8 *)actor + 0x92));
                velocity_limit = velocity_ground - 0x18;
                if (velocity_limit < velocity_current) {
                    register u32 adjusted ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                    adjusted = velocity_raw - 8;
                    (*(u16 *)((u8 *)actor + 0x92)) = adjusted;
                    goto final_collision;
                }
                goto adjust_velocity;
            }
            goto final_collision;
        }
        goto ground_reset;
    } else {
        if (entity_flags & 0x800) {
            ((S_80170BB8_4 *)entity)->unk_14 = entity_flags & 0x8FFF;
        } else {
            ((S_80170BB8_4 *)entity)->unk_14 = entity_flags | 0x7000;
        }

        ((S_80170BB8_1 *)subject)->unk_1C.u &= 0xF7FFFFFF;
        subject_flags = ((S_80170BB8_1 *)subject)->unk_1C.u;

        if (!(subject_flags & 0x00040000)) {
ground_reset:
        correction = (*(s32 *)((u8 *)actor + 0xB4));
        (*(u16 *)((u8 *)actor + 0xB8)) = 0;
        (*(s32 *)((u8 *)actor + 0xB4)) = 0;
        (*(s32 *)((u8 *)actor + 0x90)) -= correction;
        if (!((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
            ground = func_800BCB04(
                ((S_80170BB8_0 *)motion)->unk_00.at02.v, ((S_80170BB8_0 *)motion)->unk_04.at02.v,
                (s16)(((S_80170BB8_1 *)subject)->unk_88 - 0x20));
            reset_offset = (s16)(ground - ((S_80170BB8_1 *)subject)->unk_88);
            if (reset_offset < (*(s16 *)((u8 *)actor + 0x92))) {
                (*(s16 *)((u8 *)actor + 0x92)) = reset_offset;
                (*(u8 *)((u8 *)actor + 0x9D)) = 0;
                ((S_80170BB8_0 *)motion)->unk_14 = 0;
                ((S_80170BB8_1 *)subject)->unk_1C.u |= 0x08000000;
            }
        }
            goto final_collision;
        }

        if (!(((S_80170BB8_4 *)entity)->unk_14 & 0x40) &&
            ((S_80170BB8_4 *)entity)->unk_2C == D_8017586C) {
            u16 count = (*(u16 *)((u8 *)actor + 0xB8));

            (*(u16 *)((u8 *)actor + 0xB8)) = count + 1;
            (*(s32 *)((u8 *)actor + 0xB4)) +=
                func_800644B8((s16)count * 0xAA) << 5;
        }

        if (!((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
            velocity_ground = (s16)(func_800BCB04(
                ((S_80170BB8_0 *)motion)->unk_00.at02.v, ((S_80170BB8_0 *)motion)->unk_04.at02.v,
                (s16)(((S_80170BB8_1 *)subject)->unk_88 - 0x20)) -
                                     ((S_80170BB8_1 *)subject)->unk_88);
            velocity_current = (*(s16 *)((u8 *)actor + 0x92));
            velocity_raw = (*(volatile u16 *)((u8 *)actor + 0x92));
            velocity_limit = velocity_ground - 0x18;
            if (velocity_limit < velocity_current) {
                register u32 adjusted ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                adjusted = velocity_raw - 8;
                (*(u16 *)((u8 *)actor + 0x92)) = adjusted;
                goto final_collision;
            }
adjust_velocity:
            velocity_limit = velocity_current < velocity_ground - 0x20;
            if (!velocity_limit) {
                goto final_collision;
            }
            {
                register u32 adjusted ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                adjusted = velocity_raw + 8;
                (*(u16 *)((u8 *)actor + 0x92)) = adjusted;
            }
        }
    }

final_collision:
    subject_flags = ((S_80170BB8_1 *)subject)->unk_1C.u;
    if (subject_flags & 0x40000000) {
        ((S_80170BB8_1 *)subject)->unk_1C.u = subject_flags & 0xBFFFFFFF;
        ground = func_800BCB04((((S_80170BB8_4 *)entity)->unk_24 << 6) | 0x20,
                               (((S_80170BB8_4 *)entity)->unk_25 << 6) | 0x20,
                               (s16)(((S_80170BB8_1 *)subject)->unk_88 - 0x20));
        if ((s16)ground < 0x200) {
            (*(u16 *)((u8 *)actor + 0x92)) +=
                ((S_80170BB8_1 *)subject)->unk_88 - ground;
            ((S_80170BB8_1 *)subject)->unk_88 = ground;
        }
    }

    ((S_80170BB8_0 *)motion)->unk_0A = ((S_80170BB8_1 *)subject)->unk_88 +
                              (*(u16 *)((u8 *)actor + 0x92)) -
                              (*(u16 *)((u8 *)actor + 0xB6));
    ((S_80170BB8_4 *)entity)->unk_14 |= 0x40;

done:
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(sprite);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(work);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
}
