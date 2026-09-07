#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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

void func_80170BB8(void *input0, void *input1, void *input2)
{
    register u8 *actor ASM_REG("$18") = input0;
    register u8 *motion ASM_REG("$22") = input1;
    register u8 *entity ASM_REG("$21") = input2;
    register u8 *subject ASM_REG("$19") = actor;
    register u8 *part ASM_REG("$20");
    register u8 *sprite ASM_REG("$16");
    register s32 work ASM_REG("$17");
    register u32 global_flags ASM_REG("$2");
    register u16 *global_flags_ptr ASM_REG("$2") = (u16 *)0x80080000;
    register u8 *part_base ASM_REG("$3");
    Callback callback;
    u16 entity_flags;
    s32 subject_flags;
    s32 ground;
    s32 correction;
    s16 reset_offset;
    register s32 velocity_limit ASM_REG("$2");
    register u32 velocity_raw ASM_REG("$3");
    register s32 velocity_current ASM_REG("$4");
    register s32 velocity_ground ASM_REG("$5");

    ASM_KEEP(subject);
    ASM_KEEP(global_flags_ptr);
    part_base = FIELD(actor, u8 *, 0xA4);
    ASM_KEEP(part_base);
    global_flags = global_flags_ptr[0x1A31];
    ASM_SCHED_BARRIER();
    part = part_base + 0x20;

    ASM_KEEP(actor);
    ASM_KEEP(motion);
    ASM_KEEP(entity);
    ASM_KEEP(subject);
    ASM_KEEP(part);
    ASM_KEEP(sprite);

    global_flags &= 0x2000;
    sprite = part_base + 0x28;
    if (global_flags) {
        callback = FIELD(actor, Callback, 0x8C);
        if (callback == (Callback)D_8017140C) {
            callback(input0, input1, input2, input0);
            goto done;
        }
        FIELD(actor, u8, 0x71) &= 0x7F;
        goto done;
    }


    {
        register void *call0 ASM_REG("$4") = actor;
        register void *call1 ASM_REG("$5") = motion;
        register void *call2 ASM_REG("$6") = entity;
        register void *call3 ASM_REG("$7");
        register u32 old_state ASM_REG("$2");

        old_state = FIELD(actor, u8, 0x6D);
        call3 = actor;
        old_state <<= 24;
        ASM_KEEP(old_state);
        ASM_KEEP(call0);
        ASM_KEEP(call1);
        ASM_KEEP(call2);
        ASM_KEEP(call3);
        work = (s32)old_state >> 24;
        if (func_800A9E70(call0, call1, call2, call3) != 0) {
            goto done;
        }
    }

    {
        register Callback callback2 ASM_REG("$2");

        callback2 = FIELD(actor, Callback, 0x8C);
        if (callback2 != 0) {
            callback2(actor, motion, entity, actor);
        }
    }
    D_8017589C[FIELD(actor, u8, 0x9A)](actor, motion, entity, actor);

    if ((s16)work != FIELD(actor, s8, 0x6D)) {
        func_800AA36C(actor, motion, entity, actor);
    }

    FIELD(motion, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);

    if (!(FIELD(actor, u32, 0x1C) & 0x00040000) &&
        !(FIELD(actor, u16, 0x98) & 8)) {
        FIELD(motion, s32, 0x14) += FIELD(actor, s8, 0x9D) * 0x14000;
        FIELD(actor, u8, 0x9D)++;
    } else {
        FIELD(actor, u8, 0x9D) = 0;
    }
    FIELD(actor, s32, 0x90) += FIELD(motion, s32, 0x14);

    if (FIELD(subject, u32, 0x1C) & 0x200) {
        if (FIELD(actor, u16, 0x98) & 0x4000) {
            FIELD(sprite, u32, 0x3C) = 0x00808080;
            FIELD(sprite, u32, 0xC) = 0x00808080;
        } else if (FIELD(sprite, u8, 0xC) >= 8) {
            FIELD(sprite, u32, 0x3C) += 0xFFF7F7F8;
            FIELD(sprite, u32, 0xC) = FIELD(sprite, u32, 0x3C);
        }

        if (FIELD(sprite, u16, 0x14) & 0x6000) {
            if (FIELD(sprite, u8, 0xC) < 8 ||
                (FIELD(actor, u16, 0x98) & 0x4000)) {
                u16 state = FIELD(actor, u16, 0x98);

                if (!(state & 0x8000)) {
                    FIELD(actor, u16, 0x98) = state | 0xC000;
                    FIELD(part, u16, 4) |= 0x8000;
                    FIELD(actor, u16, 0xA0) =
                        (func_80069EF8() & 7) + 0x10;
                }
            }
        }

        work = 0;
        if (--FIELD(actor, s16, 0xA0) == 0) {
            FIELD(actor, u16, 0x98) &= 0x7FFF;
            FIELD(part, u16, 4) &= 0x7FFF;
            if (FIELD(part, s16, 2) > 0) {
                do {
                    func_80047784(sprite, 0x1C, 0);
                    sprite += 0x30;
                    work++;
                } while (work < FIELD(part, s16, 2));
            }
        }
    } else {
        if (FIELD(sprite, u8, 0xC) >= 0x80) {
            FIELD(sprite, u32, 0x3C) = 0x00808080;
            FIELD(sprite, u32, 0xC) = 0x00808080;
        } else {
            FIELD(sprite, u32, 0x3C) += 0x00080808;
            FIELD(sprite, u32, 0xC) = FIELD(sprite, u32, 0x3C);
        }

        if (FIELD(actor, u16, 0x98) & 0x4000) {
            FIELD(actor, u16, 0x98) &= 0x3FFF;
            FIELD(part, u16, 4) &= 0x7FFF;
        }

        if (FIELD(actor, u16, 0x98) & 0x1000) {
            func_80047784(sprite, 0x1D, 0);
            func_80047784(sprite + 0x30, 0x1D, 0);
            FIELD(actor, u16, 0x98) &= 0xEFFF;
        } else if ((FIELD(actor, u16, 0x98) & 0x2000) &&
                   (FIELD(sprite, u16, 0x14) & 0x6000)) {
            register s32 effect_mode ASM_REG("$5");

            if (FIELD(actor, u8, 0x9A) == 7) {
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
                ASM_KEEP(effect_mode);
                func_80047784(sprite + 0x30, effect_mode, 0);
            }
        }
    }

    entity_flags = FIELD(entity, u16, 0x14);
    if (!(entity_flags & 0x8000)) {
        {
            register s32 direction_value ASM_REG("$2");

            direction_value =
                D_80083228[0] + FIELD(subject, s16, 0x2A) + 0x100;
            ASM_KEEP(direction_value);
            work = (direction_value >> 9) & 7;
        }
        {
            register s32 direction_copy ASM_REG("$16");

            if (FIELD(actor, s16, 0x94) != (direction_copy = work)) {
                func_80047738(entity,
                              FIELD(FIELD(entity, u8 *, 0x2C), u8,
                                    direction_copy),
                              FIELD(entity, s8, 4));
                FIELD(actor, s16, 0x94) = work;
            }

            if (D_8006CCF8[direction_copy] != 0) {
                FIELD(entity, u16, 0x14) |= 1;
            } else {
                FIELD(entity, u16, 0x14) &= 0xFFFE;
            }
        }

        if (FIELD(actor, u8, 0x9A) != 8) {
            func_800A020C(FIELD(subject, s32, 0x1C), entity + 0xC);
        }

        if (!(FIELD(subject, s32, 0x1C) & 0x20)) {
            if (!(FIELD(entity, u16, 0x14) & 0x40)) {
                func_800478B8(entity);
            }
        } else {
            FIELD(entity, u16, 0x14) |= 0x7000;
            FIELD(subject, u32, 0x1C) &= 0xFFFBFFFF;
        }

        FIELD(subject, u32, 0x1C) &= 0xF7FFFFFF;
        subject_flags = FIELD(subject, u32, 0x1C);

        if (subject_flags & 0x00040000) {
            if (!(FIELD(entity, u16, 0x14) & 0x40) &&
                FIELD(entity, u8 *, 0x2C) == D_8017586C) {
                u16 count = FIELD(actor, u16, 0xB8);

                FIELD(actor, u16, 0xB8) = count + 1;
                FIELD(actor, s32, 0xB4) +=
                    func_800644B8((s16)count * 0xAA) << 5;
            }

            if (!(FIELD(actor, u16, 0x98) & 8)) {
                velocity_ground = (s16)(func_800BCB04(
                    FIELD(motion, u16, 2), FIELD(motion, u16, 6),
                    (s16)(FIELD(subject, u16, 0x88) - 0x20)) -
                                         FIELD(subject, u16, 0x88));
                velocity_current = FIELD(actor, s16, 0x92);
                velocity_raw = FIELD(actor, volatile u16, 0x92);
                velocity_limit = velocity_ground - 0x18;
                if (velocity_limit < velocity_current) {
                    register u32 adjusted ASM_REG("$2");

                    adjusted = velocity_raw - 8;
                    FIELD(actor, u16, 0x92) = adjusted;
                    goto final_collision;
                }
                goto adjust_velocity;
            }
            goto final_collision;
        }
        goto ground_reset;
    } else {
        if (entity_flags & 0x800) {
            FIELD(entity, u16, 0x14) = entity_flags & 0x8FFF;
        } else {
            FIELD(entity, u16, 0x14) = entity_flags | 0x7000;
        }

        FIELD(subject, u32, 0x1C) &= 0xF7FFFFFF;
        subject_flags = FIELD(subject, u32, 0x1C);

        if (!(subject_flags & 0x00040000)) {
ground_reset:
        correction = FIELD(actor, s32, 0xB4);
        FIELD(actor, u16, 0xB8) = 0;
        FIELD(actor, s32, 0xB4) = 0;
        FIELD(actor, s32, 0x90) -= correction;
        if (!(FIELD(actor, u16, 0x98) & 8)) {
            ground = func_800BCB04(
                FIELD(motion, u16, 2), FIELD(motion, u16, 6),
                (s16)(FIELD(subject, u16, 0x88) - 0x20));
            reset_offset = (s16)(ground - FIELD(subject, u16, 0x88));
            if (reset_offset < FIELD(actor, s16, 0x92)) {
                FIELD(actor, s16, 0x92) = reset_offset;
                FIELD(actor, u8, 0x9D) = 0;
                FIELD(motion, s32, 0x14) = 0;
                FIELD(subject, u32, 0x1C) |= 0x08000000;
            }
        }
            goto final_collision;
        }

        if (!(FIELD(entity, u16, 0x14) & 0x40) &&
            FIELD(entity, u8 *, 0x2C) == D_8017586C) {
            u16 count = FIELD(actor, u16, 0xB8);

            FIELD(actor, u16, 0xB8) = count + 1;
            FIELD(actor, s32, 0xB4) +=
                func_800644B8((s16)count * 0xAA) << 5;
        }

        if (!(FIELD(actor, u16, 0x98) & 8)) {
            velocity_ground = (s16)(func_800BCB04(
                FIELD(motion, u16, 2), FIELD(motion, u16, 6),
                (s16)(FIELD(subject, u16, 0x88) - 0x20)) -
                                     FIELD(subject, u16, 0x88));
            velocity_current = FIELD(actor, s16, 0x92);
            velocity_raw = FIELD(actor, volatile u16, 0x92);
            velocity_limit = velocity_ground - 0x18;
            if (velocity_limit < velocity_current) {
                register u32 adjusted ASM_REG("$2");

                adjusted = velocity_raw - 8;
                FIELD(actor, u16, 0x92) = adjusted;
                goto final_collision;
            }
adjust_velocity:
            velocity_limit = velocity_current < velocity_ground - 0x20;
            if (!velocity_limit) {
                goto final_collision;
            }
            {
                register u32 adjusted ASM_REG("$2");

                adjusted = velocity_raw + 8;
                FIELD(actor, u16, 0x92) = adjusted;
            }
        }
    }

final_collision:
    subject_flags = FIELD(subject, u32, 0x1C);
    if (subject_flags & 0x40000000) {
        FIELD(subject, u32, 0x1C) = subject_flags & 0xBFFFFFFF;
        ground = func_800BCB04((FIELD(entity, u8, 0x24) << 6) | 0x20,
                               (FIELD(entity, u8, 0x25) << 6) | 0x20,
                               (s16)(FIELD(subject, u16, 0x88) - 0x20));
        if ((s16)ground < 0x200) {
            FIELD(actor, u16, 0x92) +=
                FIELD(subject, u16, 0x88) - ground;
            FIELD(subject, u16, 0x88) = ground;
        }
    }

    FIELD(motion, u16, 0xA) = FIELD(subject, u16, 0x88) +
                              FIELD(actor, u16, 0x92) -
                              FIELD(actor, u16, 0xB6);
    FIELD(entity, u16, 0x14) |= 0x40;

done:
    ASM_KEEP(actor);
    ASM_KEEP(motion);
    ASM_KEEP(entity);
    ASM_KEEP(subject);
    ASM_KEEP(part);
    ASM_KEEP(sprite);
    ASM_KEEP(work);
}
