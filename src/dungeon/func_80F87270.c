#include "common.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s32 func_800BCB04(u16, u16, s16);

extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80171138[];
extern Callback D_80174B1C[];


typedef struct S_80170A70_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170A70_0;   /* arg1 in func_80170A70 */

typedef struct S_80170A70_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80170A70_1;   /* arg2 in func_80170A70 */

typedef struct S_80170A70_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80170A70_2;   /* object in func_80170A70 */

/* Update entity behavior, movement, sprite facing, and ground-relative height. */
void func_80170A70(void *entity, void *motion_arg, void *sprite_arg)
{
    static void *const phase_entries[] = {
        &&phase_update_a,
        &&phase_update_b,
    };
    S_80170A70_2 *object = entity;
    register void *motion ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *sprite ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    Callback paused_callback;
    Callback update_callback;
    s16 state_or_facing;
    s16 ground_height;
    register s32 ground_delta ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 facing;
    s32 bob_offset;
    u16 sprite_flags;
    u16 visibility_flags;

    motion = motion_arg;
    sprite = sprite_arg;
    bob_offset = 0;
    if (D_80083462 & 0x2000) {
        paused_callback = (*(Callback *)((u8 *)entity + (0x8C)));
        if (paused_callback == (Callback)D_80171138) {
            paused_callback(entity, motion_arg, sprite_arg, entity);
            return;
        }
        (*(u8 *)((u8 *)entity + (0x71))) &= 0x7F;
        return;
    }

    ASM_KEEP_NV(motion);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(sprite);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    state_or_facing = (s8)(*(u8 *)((u8 *)entity + (0x6D)));
    if (func_800A9E70(entity, motion, sprite, entity) != 0) {
        return;
    }

    update_callback = (*(Callback *)((u8 *)entity + (0x8C)));
    if (update_callback != 0) {
        update_callback(entity, motion, sprite, entity);
    }
    D_80174B1C[(*(u8 *)((u8 *)entity + (0x9A)))](entity, motion, sprite, entity);
    if ((s16)state_or_facing != (*(s8 *)((u8 *)entity + (0x6D)))) {
        func_800AA36C(entity, motion, sprite, entity);
    }

    ((S_80170A70_0 *)motion)->unk_00.at00.v += ((S_80170A70_0 *)motion)->unk_0C;
    ((S_80170A70_0 *)motion)->unk_04.at00.v += ((S_80170A70_0 *)motion)->unk_10;

    if (!((*(s32 *)((u8 *)entity + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)entity + (0x98))) & 8)) {
        ((S_80170A70_0 *)motion)->unk_14 += (*(s8 *)((u8 *)entity + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)entity + (0x9D)))++;
    } else {
        (*(u8 *)((u8 *)entity + (0x9D))) = 0;
    }
    (*(s32 *)((u8 *)entity + (0x90))) += ((S_80170A70_0 *)motion)->unk_14;
    sprite_flags = ((S_80170A70_1 *)sprite)->unk_14;

    if (!(sprite_flags & 0x8000)) {
        facing = ((D_80083228 + object->unk_2A + 0x100) >> 9) & 7;
        state_or_facing = facing;
        if ((*(s16 *)((u8 *)entity + (0x94))) != state_or_facing) {
            func_80047738(sprite,
                ((u8 *)((S_80170A70_1 *)sprite)->unk_2C)[state_or_facing],
                ((S_80170A70_1 *)sprite)->unk_04);
            (*(s16 *)((u8 *)entity + (0x94))) = facing;
        }

        {
            u16 facing_flags;

            if (D_8006CCF8[state_or_facing] != 0) {
                facing_flags = ((S_80170A70_1 *)sprite)->unk_14 | 1;
            } else {
                facing_flags = ((S_80170A70_1 *)sprite)->unk_14 & 0xFFFE;
            }
            ((S_80170A70_1 *)sprite)->unk_14 = facing_flags;
        }

        if ((*(u8 *)((u8 *)entity + (0x9A))) != 8) {
            func_800A020C(object->unk_1C, (u8 *)sprite + 0xC);
        }

        if (!(object->unk_1C & 0x20)) {
            if (!(((S_80170A70_1 *)sprite)->unk_14 & 0x40)) {
                func_800478B8(sprite);
            }
            goto clear_motion_flag;
        }

        ((S_80170A70_1 *)sprite)->unk_14 |= 0x7000;
        object->unk_1C &= 0xFFFBFFFF;

clear_motion_flag:
        object->unk_1C &= 0xF7FFFFFF;
        if (object->unk_1C & 0x40000) {
            if (!(((S_80170A70_1 *)sprite)->unk_14 & 0x40)) {
                {
                    s32 bob_wave = func_800644B8(
                        ((*(s16 *)((u8 *)entity + (0xA0))) << 12) / 40);
                    bob_offset = bob_wave >> 9;
                    if ((*(u8 *)((u8 *)entity + (0x9A))) == 0x12) {
                        bob_offset = bob_wave >> 10;
                    }
                }
phase_update_a:
                (*(s16 *)((u8 *)entity + (0xA0))) = ((*(s16 *)((u8 *)entity + (0xA0))) + 1) % 40;
            }

            if (!((*(u16 *)((u8 *)entity + (0x98))) & 8)) {
                ground_height = (s16)(func_800BCB04(
                    ((S_80170A70_0 *)motion)->unk_00.at02.v, ((S_80170A70_0 *)motion)->unk_04.at02.v,
                    (s16)(object->unk_88.u - 0x20)) -
                    object->unk_88.u);
                if ((*(s16 *)((u8 *)entity + (0x92))) > ground_height - 0x30) {
                    (*(s16 *)((u8 *)entity + (0x92))) =
                        (u16)(*(s16 *)((u8 *)entity + (0x92))) - 8;
                    goto reset_bob;
                }
                if (ground_height - 0x3A > (*(s16 *)((u8 *)entity + (0x92)))) {
                    (*(s16 *)((u8 *)entity + (0x92))) =
                        (u16)(*(s16 *)((u8 *)entity + (0x92))) + 8;
                    goto reset_bob;
                }
            }
            goto reset_bob;
        }

        (*(s16 *)((u8 *)entity + (0xA0))) = 0;
        if (!((*(u16 *)((u8 *)entity + (0x98))) & 8)) {
            register s32 object_height ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            ground_delta = (s16)func_800BCB04(
                ((S_80170A70_0 *)motion)->unk_00.at02.v, ((S_80170A70_0 *)motion)->unk_04.at02.v,
                (s16)(object->unk_88.u - 0x20));
            object_height = object->unk_88.s;
            ground_delta -= object_height;
            if ((*(s16 *)((u8 *)entity + (0x92))) > ground_delta) {
                (*(s16 *)((u8 *)entity + (0x92))) = ground_delta;
                (*(u8 *)((u8 *)entity + (0x9D))) = 0;
                ((S_80170A70_0 *)motion)->unk_14 = 0;
                object->unk_1C |= 0x08000000;
                goto reset_bob;
            }
        }
        goto reset_bob;
    }

    {
        if (sprite_flags & 0x800) {
            visibility_flags = sprite_flags & 0x8FFF;
        } else {
            visibility_flags = sprite_flags | 0x7000;
        }
        ((S_80170A70_1 *)sprite)->unk_14 = visibility_flags;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    }
    object->unk_1C &= 0xF7FFFFFF;

    if (!(object->unk_1C & 0x40000)) {
        (*(s16 *)((u8 *)entity + (0xA0))) = 0;
        (*(s16 *)((u8 *)entity + (0x92))) = (u16)(*(s16 *)((u8 *)entity + (0x92))) - bob_offset;
        bob_offset = 0;
        if (!((*(u16 *)((u8 *)entity + (0x98))) & 8)) {
            register s32 object_height ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            ground_delta = (s16)func_800BCB04(
                ((S_80170A70_0 *)motion)->unk_00.at02.v, ((S_80170A70_0 *)motion)->unk_04.at02.v,
                (s16)(object->unk_88.u - 0x20));
            object_height = object->unk_88.s;
            ground_delta -= object_height;
            if ((*(s16 *)((u8 *)entity + (0x92))) > ground_delta) {
                (*(s16 *)((u8 *)entity + (0x92))) = ground_delta;
                (*(u8 *)((u8 *)entity + (0x9D))) = 0;
                ((S_80170A70_0 *)motion)->unk_14 = 0;
                object->unk_1C |= 0x08000000;
                goto finish_height;
            }
        }
        goto finish_height;
    }

    if (!(((S_80170A70_1 *)sprite)->unk_14 & 0x40)) {
        {
            s32 bob_wave = func_800644B8(
                ((*(s16 *)((u8 *)entity + (0xA0))) << 12) / 40);
            bob_offset = bob_wave >> 9;
            if ((*(u8 *)((u8 *)entity + (0x9A))) == 0x12) {
                bob_offset = bob_wave >> 10;
            }
        }
phase_update_b:
        (*(s16 *)((u8 *)entity + (0xA0))) = ((*(s16 *)((u8 *)entity + (0xA0))) + 1) % 40;
    }

    if (!((*(u16 *)((u8 *)entity + (0x98))) & 8)) {
        ground_height = (s16)(func_800BCB04(
            ((S_80170A70_0 *)motion)->unk_00.at02.v, ((S_80170A70_0 *)motion)->unk_04.at02.v,
            (s16)(object->unk_88.u - 0x20)) -
            object->unk_88.u);
        if ((*(s16 *)((u8 *)entity + (0x92))) > ground_height - 0x30) {
            (*(s16 *)((u8 *)entity + (0x92))) =
                (u16)(*(s16 *)((u8 *)entity + (0x92))) - 8;
        } else if (ground_height - 0x3A > (*(s16 *)((u8 *)entity + (0x92)))) {
            (*(s16 *)((u8 *)entity + (0x92))) =
                (u16)(*(s16 *)((u8 *)entity + (0x92))) + 8;
        } else {
            goto finish_height;
        }
    }

finish_height:
    (*(s16 *)((u8 *)entity + (0xA0))) = 0;

reset_bob:
    if (object->unk_1C & 0x40000000) {
        object->unk_1C &= 0xBFFFFFFF;
        ground_height = func_800BCB04(
            (((S_80170A70_1 *)sprite)->unk_24 << 6) | 0x20,
            (((S_80170A70_1 *)sprite)->unk_25 << 6) | 0x20,
            (s16)(object->unk_88.u - 0x20));
        if (ground_height < 0x200) {
            (*(s16 *)((u8 *)entity + (0x92))) =
                (u16)(*(s16 *)((u8 *)entity + (0x92))) +
                (object->unk_88.u - ground_height);
            object->unk_88.u = ground_height;
        }
    }

    ((S_80170A70_0 *)motion)->unk_0A =
        object->unk_88.u + (u16)(*(s16 *)((u8 *)entity + (0x92))) + bob_offset;
    ((S_80170A70_1 *)sprite)->unk_14 |= 0x40;
}
