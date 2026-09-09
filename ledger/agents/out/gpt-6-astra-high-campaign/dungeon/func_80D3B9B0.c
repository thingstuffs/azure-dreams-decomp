#include "common.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern u8 D_8006CCF8[];
extern s16 D_80083228[8];
extern u16 D_80083462[8];
extern u8 D_800E23E0[];
extern u8 D_80171A80[];
extern Callback D_80176374[];

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(u32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s16 func_800BCB04(u16, u16, s16);


typedef struct S_801711B0_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801711B0_0;   /* motion in func_801711B0 */

typedef struct S_801711B0_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801711B0_1;   /* part in func_801711B0 */

typedef struct S_801711B0_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_801711B0_2;   /* base in func_801711B0 */

/* Update object callbacks, motion, facing, and ground-relative height. */
void func_801711B0(void *object_arg, void *motion_arg, void *part_arg)
{
    register void *obj ASM_REG("$17") = object_arg;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *motion ASM_REG("$21") = motion_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *part ASM_REG("$20") = part_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *base = obj;
    register s32 state_or_dir ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 direction;
    register s32 update_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *check_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *check_motion ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *check_part ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *check_context ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u16 part_flags;
    Callback paused_callback;
    Callback callback;
    s32 new_state;
    s16 ground_height;
    s32 flags;
    s32 normal_flags;
    s32 special_flags;
    u16 new_part_flags;
    register u16 bob_step ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 bob_phase;

    if (D_80083462[0] & 0x2000) {
        paused_callback = (*(Callback *)((u8 *)obj + (0x8C)));
        if (paused_callback == (Callback)D_80171A80) {
            void *callback_obj = object_arg;

            ASM_UNDEF(callback_obj);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            paused_callback(callback_obj, motion_arg, part_arg, callback_obj);
            return;
        }
        (*(u8 *)((u8 *)obj + (0x71))) &= 0x7F;
        return;
    }

    ASM_KEEP(obj);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(part);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    check_obj = obj;
    check_motion = motion;
    check_part = part;
    update_value = (*(u8 *)((u8 *)obj + (0x6D)));
    ASM_KEEP(update_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    check_context = obj;
    state_or_dir = (s8)update_value;
    if (func_800A9E70(check_obj, check_motion, check_part, check_context) != 0) {
        return;
    }

    callback = (*(Callback *)((u8 *)obj + (0x8C)));
    if (callback != 0) {
        callback(obj, motion, part, obj);
    }
    D_80176374[(*(u8 *)((u8 *)obj + (0x9A)))](obj, motion, part, obj);

    update_value = (s32)state_or_dir << 16;
    new_state = (*(s8 *)((u8 *)obj + (0x6D)));
    update_value >>= 16;
    if (update_value != new_state) {
        func_800AA36C(obj, motion, part, obj);
    }

    ((S_801711B0_0 *)motion)->unk_00.at00.v += ((S_801711B0_0 *)motion)->unk_0C;
    ((S_801711B0_0 *)motion)->unk_04.at00.v += ((S_801711B0_0 *)motion)->unk_10;

    if (!((*(u32 *)((u8 *)obj + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)obj + (0x98))) & 8)) {
        ((S_801711B0_0 *)motion)->unk_14 += (*(s8 *)((u8 *)obj + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)obj + (0x9D)))++;
    } else {
        (*(u8 *)((u8 *)obj + (0x9D))) = 0;
    }
    (*(s32 *)((u8 *)obj + (0x90))) += ((S_801711B0_0 *)motion)->unk_14;
    part_flags = ((S_801711B0_1 *)part)->unk_14;

    if (!(part_flags & 0x8000)) {
        direction = ((D_80083228[0] + ((S_801711B0_2 *)base)->unk_2A + 0x100) >> 9) & 7;
        ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        update_value = (*(s16 *)((u8 *)obj + (0x94)));
        state_or_dir = direction;
        if (update_value != state_or_dir) {
            func_80047738(part,
                (*(u8 *)((u8 *)(((S_801711B0_1 *)part)->unk_2C) + (state_or_dir))),
                ((S_801711B0_1 *)part)->unk_04);
            (*(s16 *)((u8 *)obj + (0x94))) = direction;
        }

        if (D_8006CCF8[state_or_dir] != 0) {
            update_value = ((S_801711B0_1 *)part)->unk_14;
            update_value |= 1;
        } else {
            ASM_KEEP(state_or_dir);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            update_value = ((S_801711B0_1 *)part)->unk_14 & 0xFFFE;
        }
        ((S_801711B0_1 *)part)->unk_14 = update_value;

        func_800A020C(((S_801711B0_2 *)base)->unk_1C, (u8 *)part + 0xC);
        if (!(((S_801711B0_2 *)base)->unk_1C & 0x20)) {
            if (!(((S_801711B0_1 *)part)->unk_14 & 0x40)) {
                func_800478B8(part);
            }
        } else {
            ((S_801711B0_1 *)part)->unk_14 |= 0x7000;
            ((S_801711B0_2 *)base)->unk_1C &= 0xFFFBFFFF;
        }

        normal_flags = ((S_801711B0_2 *)base)->unk_1C & 0xF7FFFFFF;
        ((S_801711B0_2 *)base)->unk_1C = normal_flags;
        if (normal_flags & 0x40000) {
            if (!(((S_801711B0_1 *)part)->unk_14 & 0x40) &&
                ((S_801711B0_1 *)part)->unk_2C == D_800E23E0) {
                bob_step = (*(u16 *)((u8 *)obj + (0x9E)));
                update_value = (s32)bob_step << 16;
                update_value >>= 16;
                bob_phase = update_value * 0x55;
                ASM_KEEP_DEP_NV(bob_step, bob_phase);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                bob_step++;
                (*(u16 *)((u8 *)obj + (0x9E))) = bob_step;
                (*(s32 *)((u8 *)obj + (0xA0))) +=
                    func_800644B8(bob_phase) << 4;
            }

            ground_height = -0x20;
            if (!((*(u16 *)((u8 *)obj + (0x98))) & 8)) {
                if (ground_height < (*(s16 *)((u8 *)obj + (0x92)))) {
                    (*(u16 *)((u8 *)obj + (0x92))) = (*(u16 *)((u8 *)obj + (0x92))) - 8;
                } else {
                    if ((*(s16 *)((u8 *)obj + (0x92))) < -0x28) {
                        (*(u16 *)((u8 *)obj + (0x92))) = (*(u16 *)((u8 *)obj + (0x92))) + 8;
                    }
                }
            }
        } else {
            update_value = (*(s32 *)((u8 *)obj + (0xA0)));
            (*(u16 *)((u8 *)obj + (0x9E))) = 0;
            (*(s32 *)((u8 *)obj + (0xA0))) = 0;
            (*(s32 *)((u8 *)obj + (0x90))) -= update_value;
            if (!((*(u16 *)((u8 *)obj + (0x98))) & 8)) {
                ground_height = func_800BCB04(((S_801711B0_0 *)motion)->unk_00.at02.v,
                                      ((S_801711B0_0 *)motion)->unk_04.at02.v,
                                      (s16)(((S_801711B0_2 *)base)->unk_88 - 0x20)) -
                        ((S_801711B0_2 *)base)->unk_88;
                if (ground_height < (*(s16 *)((u8 *)obj + (0x92)))) {
                    (*(s16 *)((u8 *)obj + (0x92))) = ground_height;
                    (*(u8 *)((u8 *)obj + (0x9D))) = 0;
                    ((S_801711B0_0 *)motion)->unk_14 = 0;
                    ((S_801711B0_2 *)base)->unk_1C |= 0x08000000;
                }
            }
        }
    } else {
        new_part_flags = part_flags & 0x800;
        if (new_part_flags) {
            new_part_flags = part_flags & 0x8FFF;
        } else {
            new_part_flags = part_flags | 0x7000;
        }
        ((S_801711B0_1 *)part)->unk_14 = new_part_flags;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */

        special_flags = ((S_801711B0_2 *)base)->unk_1C & 0xF7FFFFFF;
        ((S_801711B0_2 *)base)->unk_1C = special_flags;
        if (!(special_flags & 0x40000)) {
            update_value = (*(s32 *)((u8 *)obj + (0xA0)));
            (*(u16 *)((u8 *)obj + (0x9E))) = 0;
            (*(s32 *)((u8 *)obj + (0xA0))) = 0;
            (*(s32 *)((u8 *)obj + (0x90))) -= update_value;
            if (!((*(u16 *)((u8 *)obj + (0x98))) & 8)) {
                ground_height = func_800BCB04(((S_801711B0_0 *)motion)->unk_00.at02.v,
                                      ((S_801711B0_0 *)motion)->unk_04.at02.v,
                                      (s16)(((S_801711B0_2 *)base)->unk_88 - 0x20)) -
                        ((S_801711B0_2 *)base)->unk_88;
                if (ground_height < (*(s16 *)((u8 *)obj + (0x92)))) {
                    (*(s16 *)((u8 *)obj + (0x92))) = ground_height;
                    (*(u8 *)((u8 *)obj + (0x9D))) = 0;
                    ((S_801711B0_0 *)motion)->unk_14 = 0;
                    ((S_801711B0_2 *)base)->unk_1C |= 0x08000000;
                }
            }
        } else {
            if (!(((S_801711B0_1 *)part)->unk_14 & 0x40) &&
                ((S_801711B0_1 *)part)->unk_2C == D_800E23E0) {
                bob_step = (*(u16 *)((u8 *)obj + (0x9E)));
                update_value = (s32)bob_step << 16;
                update_value >>= 16;
                bob_phase = update_value * 0x55;
                ASM_KEEP_DEP_NV(bob_step, bob_phase);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                bob_step++;
                (*(u16 *)((u8 *)obj + (0x9E))) = bob_step;
                (*(s32 *)((u8 *)obj + (0xA0))) +=
                    func_800644B8(bob_phase) << 4;
            }

            ground_height = -0x20;
            if (!((*(u16 *)((u8 *)obj + (0x98))) & 8)) {
                if (ground_height < (*(s16 *)((u8 *)obj + (0x92)))) {
                    (*(u16 *)((u8 *)obj + (0x92))) = (*(u16 *)((u8 *)obj + (0x92))) - 8;
                } else if ((*(s16 *)((u8 *)obj + (0x92))) < -0x28) {
                    (*(u16 *)((u8 *)obj + (0x92))) = (*(u16 *)((u8 *)obj + (0x92))) + 8;
                }
            }
        }

        if ((*(u8 *)((u8 *)obj + (0xB5))) != 0) {
            (*(u16 *)((u8 *)obj + (0x92))) = 0;
        }
    }

    flags = ((S_801711B0_2 *)base)->unk_1C;
    if (flags & 0x40000000) {
        ((S_801711B0_2 *)base)->unk_1C = flags & 0xBFFFFFFF;
        ground_height = func_800BCB04(
            (((S_801711B0_1 *)part)->unk_24 << 6) | 0x20,
            (((S_801711B0_1 *)part)->unk_25 << 6) | 0x20,
            (s16)(((S_801711B0_2 *)base)->unk_88 - 0x20));
        if (ground_height < 0x200) {
            (*(u16 *)((u8 *)obj + (0x92))) += ((S_801711B0_2 *)base)->unk_88 - ground_height;
            ((S_801711B0_2 *)base)->unk_88 = ground_height;
        }
    }

    ((S_801711B0_0 *)motion)->unk_0A = ((S_801711B0_2 *)base)->unk_88 +
        (*(u16 *)((u8 *)obj + (0x92))) - (*(u16 *)((u8 *)obj + (0xA2)));
    ((S_801711B0_1 *)part)->unk_14 |= 0x40;
}
