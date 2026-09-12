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

/* Updates actor callbacks, motion, sprite effects, facing, and ground height. */
void func_80170BB8(void *actor_data, void *motion_data, void *entity_data)
{
    register u8 *actor ASM_REG("$18") = actor_data;   /* Byte-exact pin. */
    u8 *motion = motion_data;
    u8 *entity = entity_data;
    register u8 *subject ASM_REG("$19") = actor;   /* Byte-exact pin. */
    register u8 *part ASM_REG("$20");   /* Byte-exact pin. */
    register u8 *sprite ASM_REG("$16");   /* Byte-exact pin. */
    s32 state_index;
    u32 global_flags;
    u16 *global_flags_ptr = (u16 *)0x80080000;
    u8 *part_base;
    Callback callback;
    u16 entity_flags;
    s32 subject_flags;
    s32 ground_height;
    s32 bob_offset;
    s16 floor_offset;
    register s32 height_limit ASM_REG("$2");   /* Byte-exact pin. */
    register u32 height_raw ASM_REG("$3");   /* Byte-exact pin. */
    s32 height_offset;
    register s32 ground_offset ASM_REG("$5");   /* Byte-exact pin. */

    ASM_KEEP(global_flags_ptr);   /* Byte-exact pin. */
    part_base = (*(u8 * *)((u8 *)actor + 0xA4));
    ASM_KEEP(part_base);   /* Byte-exact pin. */
    global_flags = global_flags_ptr[0x1A31];
    ASM_SCHED_BARRIER();   /* Byte-exact pin. */
    part = part_base + 0x20;

    ASM_KEEP(actor);   /* Byte-exact pin. */
    ASM_KEEP(subject);   /* Byte-exact pin. */
    ASM_KEEP(sprite);   /* Byte-exact pin. */

    global_flags &= 0x2000;
    sprite = part_base + 0x28;
    if (global_flags) {
        callback = (*(Callback *)((u8 *)actor + 0x8C));
        if (callback == (Callback)D_8017140C) {
            callback(actor_data, motion_data, entity_data, actor_data);
            goto done;
        }
        (*(u8 *)((u8 *)actor + 0x71)) &= 0x7F;
        goto done;
    }


    {
        void *actor_arg = actor;
        register void *motion_arg ASM_REG("$5") = motion;   /* Byte-exact pin. */
        register void *entity_arg ASM_REG("$6") = entity;   /* Byte-exact pin. */
        void *actor_context;

        global_flags = (*(u8 *)((u8 *)actor + 0x6D));
        actor_context = actor;
        global_flags <<= 24;
        ASM_KEEP(actor_arg);   /* Byte-exact pin. */
        ASM_KEEP(actor_context);   /* Byte-exact pin. */
        state_index = (s32)global_flags >> 24;
        if (func_800A9E70(actor_arg, motion_arg, entity_arg, actor_context) != 0) {
            goto done;
        }
    }

    {
        Callback actor_callback;

        actor_callback = (*(Callback *)((u8 *)actor + 0x8C));
        if (actor_callback != 0) {
            actor_callback(actor, motion, entity, actor);
        }
    }
    D_8017589C[(*(u8 *)((u8 *)actor + 0x9A))](actor, motion, entity, actor);

    if ((s16)state_index != (*(s8 *)((u8 *)actor + 0x6D))) {
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
                u16 actor_flags = (*(u16 *)((u8 *)actor + 0x98));

                if (!(actor_flags & 0x8000)) {
                    (*(u16 *)((u8 *)actor + 0x98)) = actor_flags | 0xC000;
                    ((S_80170BB8_3 *)part)->unk_04 |= 0x8000;
                    (*(u16 *)((u8 *)actor + 0xA0)) =
                        (func_80069EF8() & 7) + 0x10;
                }
            }
        }

        state_index = 0;
        if (--(*(s16 *)((u8 *)actor + 0xA0)) == 0) {
            (*(u16 *)((u8 *)actor + 0x98)) &= 0x7FFF;
            ((S_80170BB8_3 *)part)->unk_04 &= 0x7FFF;
            if (((S_80170BB8_3 *)part)->unk_02 > 0) {
                do {
                    func_80047784(sprite, 0x1C, 0);
                    sprite += 0x30;
                    state_index++;
                } while (state_index < ((S_80170BB8_3 *)part)->unk_02);
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
            s32 view_angle;

            view_angle =
                D_80083228[0] + ((S_80170BB8_1 *)subject)->unk_2A + 0x100;
            state_index = (view_angle >> 9) & 7;
        }
        {
            register s32 direction ASM_REG("$16");   /* Byte-exact pin. */

            if ((*(s16 *)((u8 *)actor + 0x94)) != (direction = state_index)) {
                func_80047738(entity,
                              (*(u8 *)((u8 *)(((S_80170BB8_4 *)entity)->unk_2C) + direction)),
                              ((S_80170BB8_4 *)entity)->unk_04);
                (*(s16 *)((u8 *)actor + 0x94)) = state_index;
            }

            if (D_8006CCF8[direction] != 0) {
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
                u16 bob_frame = (*(u16 *)((u8 *)actor + 0xB8));

                (*(u16 *)((u8 *)actor + 0xB8)) = bob_frame + 1;
                (*(s32 *)((u8 *)actor + 0xB4)) +=
                    func_800644B8((s16)bob_frame * 0xAA) << 5;
            }

            if (!((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
                ground_offset = (s16)(func_800BCB04(
                    ((S_80170BB8_0 *)motion)->unk_00.at02.v, ((S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(((S_80170BB8_1 *)subject)->unk_88 - 0x20)) -
                                         ((S_80170BB8_1 *)subject)->unk_88);
                height_offset = (*(s16 *)((u8 *)actor + 0x92));
                height_raw = (*(volatile u16 *)((u8 *)actor + 0x92));
                height_limit = ground_offset - 0x18;
                if (height_limit < height_offset) {

                    global_flags = height_raw - 8;
                    (*(u16 *)((u8 *)actor + 0x92)) = global_flags;
                    goto final_collision;
                }
                goto adjust_height;
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
            bob_offset = (*(s32 *)((u8 *)actor + 0xB4));
            (*(u16 *)((u8 *)actor + 0xB8)) = 0;
            (*(s32 *)((u8 *)actor + 0xB4)) = 0;
            (*(s32 *)((u8 *)actor + 0x90)) -= bob_offset;
            if (!((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
                ground_height = func_800BCB04(
                    ((S_80170BB8_0 *)motion)->unk_00.at02.v, ((S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(((S_80170BB8_1 *)subject)->unk_88 - 0x20));
                floor_offset = (s16)(ground_height - ((S_80170BB8_1 *)subject)->unk_88);
                if (floor_offset < (*(s16 *)((u8 *)actor + 0x92))) {
                    (*(s16 *)((u8 *)actor + 0x92)) = floor_offset;
                    (*(u8 *)((u8 *)actor + 0x9D)) = 0;
                    ((S_80170BB8_0 *)motion)->unk_14 = 0;
                    ((S_80170BB8_1 *)subject)->unk_1C.u |= 0x08000000;
                }
            }
            goto final_collision;
        }

        if (!(((S_80170BB8_4 *)entity)->unk_14 & 0x40) &&
            ((S_80170BB8_4 *)entity)->unk_2C == D_8017586C) {
            u16 bob_frame = (*(u16 *)((u8 *)actor + 0xB8));

            (*(u16 *)((u8 *)actor + 0xB8)) = bob_frame + 1;
            (*(s32 *)((u8 *)actor + 0xB4)) +=
                func_800644B8((s16)bob_frame * 0xAA) << 5;
        }

        if (!((*(u16 *)((u8 *)actor + 0x98)) & 8)) {
            ground_offset = (s16)(func_800BCB04(
                ((S_80170BB8_0 *)motion)->unk_00.at02.v, ((S_80170BB8_0 *)motion)->unk_04.at02.v,
                (s16)(((S_80170BB8_1 *)subject)->unk_88 - 0x20)) -
                                     ((S_80170BB8_1 *)subject)->unk_88);
            height_offset = (*(s16 *)((u8 *)actor + 0x92));
            height_raw = (*(volatile u16 *)((u8 *)actor + 0x92));
            height_limit = ground_offset - 0x18;
            if (height_limit < height_offset) {

                global_flags = height_raw - 8;
                (*(u16 *)((u8 *)actor + 0x92)) = global_flags;
                goto final_collision;
            }
adjust_height:
            height_limit = height_offset < ground_offset - 0x20;
            if (!height_limit) {
                goto final_collision;
            }
            {

                global_flags = height_raw + 8;
                (*(u16 *)((u8 *)actor + 0x92)) = global_flags;
            }
        }
    }

final_collision:
    subject_flags = ((S_80170BB8_1 *)subject)->unk_1C.u;
    if (subject_flags & 0x40000000) {
        ((S_80170BB8_1 *)subject)->unk_1C.u = subject_flags & 0xBFFFFFFF;
        ground_height = func_800BCB04((((S_80170BB8_4 *)entity)->unk_24 << 6) | 0x20,
                               (((S_80170BB8_4 *)entity)->unk_25 << 6) | 0x20,
                               (s16)(((S_80170BB8_1 *)subject)->unk_88 - 0x20));
        if ((s16)ground_height < 0x200) {
            (*(u16 *)((u8 *)actor + 0x92)) +=
                ((S_80170BB8_1 *)subject)->unk_88 - ground_height;
            ((S_80170BB8_1 *)subject)->unk_88 = ground_height;
        }
    }

    ((S_80170BB8_0 *)motion)->unk_0A = ((S_80170BB8_1 *)subject)->unk_88 +
                              (*(u16 *)((u8 *)actor + 0x92)) -
                              (*(u16 *)((u8 *)actor + 0xB6));
    ((S_80170BB8_4 *)entity)->unk_14 |= 0x40;

done:
    ASM_KEEP(motion);   /* Byte-exact pin. */
    ASM_KEEP(entity);   /* Byte-exact pin. */
    ASM_KEEP(sprite);   /* Byte-exact pin. */
}
