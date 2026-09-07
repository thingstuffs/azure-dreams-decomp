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
extern void func_80171344(void) __attribute__((noreturn));
extern void func_801713EC(void) __attribute__((noreturn));
extern void func_80171458(void) __attribute__((noreturn));
extern void func_801716F0(void) __attribute__((noreturn));
extern void func_80171704(void) __attribute__((noreturn));


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

void func_801711B0(void *arg0, void *arg1, void *arg2)
{
    register void *obj ASM_REG("$17") = arg0;   /* MATCH pin: retail register colouring depends on it */
    register void *motion ASM_REG("$21") = arg1;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *part ASM_REG("$20") = arg2;   /* MATCH pin: load-bearing for the whole function shape */
    S_801711B0_2 *base = obj;
    register s32 work ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 direction;
    register s32 state_load ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register void *call0 ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *call1 ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *call2 ASM_REG("$6");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *call3 ASM_REG("$7");   /* MATCH pin: retail schedule: same instructions, different order without it */
    u16 part_flags;
    Callback callback_high;
    Callback callback;
    s32 compare_new;
    s16 floor;
    s32 flags;
    s32 normal_flags;
    s32 special_flags;
    u16 new_part_flags;
    register u16 counter ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 effect_arg;

    if (D_80083462[0] & 0x2000) {
        callback_high = (*(Callback *)((u8 *)obj + 0x8C));
        if (callback_high == (Callback)D_80171A80) {
            void *entry0 = arg0;

            ASM_UNDEF(entry0);   /* MATCH pin: load-bearing for the whole function shape */
            callback_high(entry0, arg1, arg2, entry0);
            return;
        }
        (*(u8 *)((u8 *)obj + 0x71)) &= 0x7F;
        return;
    }

    ASM_KEEP(obj);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_KEEP(motion);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_KEEP(part);   /* MATCH pin: keeps a statement from moving across a call/branch */

    call0 = obj;
    call1 = motion;
    call2 = part;
    state_load = (*(u8 *)((u8 *)obj + 0x6D));
    ASM_KEEP(state_load);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    call3 = obj;
    work = (s8)state_load;
    if (func_800A9E70(call0, call1, call2, call3) != 0) {
        return;
    }

    callback = (*(Callback *)((u8 *)obj + 0x8C));
    if (callback != 0) {
        callback(obj, motion, part, obj);
    }
    D_80176374[(*(u8 *)((u8 *)obj + 0x9A))](obj, motion, part, obj);

    state_load = (s32)work << 16;
    compare_new = (*(s8 *)((u8 *)obj + 0x6D));
    state_load >>= 16;
    if (state_load != compare_new) {
        func_800AA36C(obj, motion, part, obj);
    }

    ((S_801711B0_0 *)motion)->unk_00.at00.v += ((S_801711B0_0 *)motion)->unk_0C;
    ((S_801711B0_0 *)motion)->unk_04.at00.v += ((S_801711B0_0 *)motion)->unk_10;

    if (!((*(u32 *)((u8 *)obj + 0x1C)) & 0x40000) &&
        !((*(u16 *)((u8 *)obj + 0x98)) & 8)) {
        ((S_801711B0_0 *)motion)->unk_14 += (*(s8 *)((u8 *)obj + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)obj + 0x9D))++;
        func_80171344();
    }

    (*(u8 *)((u8 *)obj + 0x9D)) = 0;
    ASM_KEEP(obj);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    (*(s32 *)((u8 *)obj + 0x90)) += ((S_801711B0_0 *)motion)->unk_14;
    part_flags = ((S_801711B0_1 *)part)->unk_14;

    if (!(part_flags & 0x8000)) {
        direction = ((D_80083228[0] + base->unk_2A + 0x100) >> 9) & 7;
        ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        state_load = (*(s16 *)((u8 *)obj + 0x94));
        work = direction;
        if (state_load != work) {
            func_80047738(part,
                (*(u8 *)((u8 *)(((S_801711B0_1 *)part)->unk_2C) + work)),
                ((S_801711B0_1 *)part)->unk_04);
            (*(s16 *)((u8 *)obj + 0x94)) = direction;
        }

        if (D_8006CCF8[work] != 0) {
            state_load = ((S_801711B0_1 *)part)->unk_14;
            state_load |= 1;
            ASM_TAILSLOT_PIN(state_load);   /* MATCH pin: retail delay-slot fill depends on it */
            func_801713EC();
        }
        ASM_KEEP(work);   /* MATCH pin: load-bearing for the whole function shape */
        ((S_801711B0_1 *)part)->unk_14 &= 0xFFFE;

        func_800A020C(base->unk_1C, (u8 *)part + 0xC);
        if (!(base->unk_1C & 0x20)) {
            if (!(((S_801711B0_1 *)part)->unk_14 & 0x40)) {
                func_800478B8(part);
                state_load = 0xF7FF0000;
                ASM_TAILSLOT_PIN(state_load);   /* MATCH pin: retail delay-slot fill depends on it */
                func_80171458();
            }
        } else {
            ((S_801711B0_1 *)part)->unk_14 |= 0x7000;
            base->unk_1C &= 0xFFFBFFFF;
        }

        normal_flags = base->unk_1C & 0xF7FFFFFF;
        base->unk_1C = normal_flags;
        if (normal_flags & 0x40000) {
            if (!(((S_801711B0_1 *)part)->unk_14 & 0x40) &&
                ((S_801711B0_1 *)part)->unk_2C == D_800E23E0) {
                counter = (*(u16 *)((u8 *)obj + 0x9E));
                state_load = (s32)counter << 16;
                state_load >>= 16;
                effect_arg = state_load * 0x55;
                ASM_KEEP_DEP_NV(counter, effect_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
                counter++;
                (*(u16 *)((u8 *)obj + 0x9E)) = counter;
                (*(s32 *)((u8 *)obj + 0xA0)) +=
                    func_800644B8(effect_arg) << 4;
            }

            floor = -0x20;
            if (!((*(u16 *)((u8 *)obj + 0x98)) & 8)) {
                if (floor < (*(s16 *)((u8 *)obj + 0x92))) {
                    (*(u16 *)((u8 *)obj + 0x92)) = (*(u16 *)((u8 *)obj + 0x92)) - 8;
                    func_80171704();
                }
                ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
                if ((*(s16 *)((u8 *)obj + 0x92)) < -0x28) {
                    (*(u16 *)((u8 *)obj + 0x92)) = (*(u16 *)((u8 *)obj + 0x92)) + 8;
                    func_80171704();
                }
            }
        } else {
            state_load = (*(s32 *)((u8 *)obj + 0xA0));
            (*(u16 *)((u8 *)obj + 0x9E)) = 0;
            (*(s32 *)((u8 *)obj + 0xA0)) = 0;
            (*(s32 *)((u8 *)obj + 0x90)) -= state_load;
            if (!((*(u16 *)((u8 *)obj + 0x98)) & 8)) {
                floor = func_800BCB04(((S_801711B0_0 *)motion)->unk_00.at02.v,
                                      ((S_801711B0_0 *)motion)->unk_04.at02.v,
                                      (s16)(base->unk_88 - 0x20)) -
                        base->unk_88;
                if (floor < (*(s16 *)((u8 *)obj + 0x92))) {
                    (*(s16 *)((u8 *)obj + 0x92)) = floor;
                    (*(u8 *)((u8 *)obj + 0x9D)) = 0;
                    ((S_801711B0_0 *)motion)->unk_14 = 0;
                    base->unk_1C |= 0x08000000;
                    func_80171704();
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
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */

        special_flags = base->unk_1C & 0xF7FFFFFF;
        base->unk_1C = special_flags;
        if (!(special_flags & 0x40000)) {
            state_load = (*(s32 *)((u8 *)obj + 0xA0));
            (*(u16 *)((u8 *)obj + 0x9E)) = 0;
            (*(s32 *)((u8 *)obj + 0xA0)) = 0;
            (*(s32 *)((u8 *)obj + 0x90)) -= state_load;
            if (!((*(u16 *)((u8 *)obj + 0x98)) & 8)) {
                floor = func_800BCB04(((S_801711B0_0 *)motion)->unk_00.at02.v,
                                      ((S_801711B0_0 *)motion)->unk_04.at02.v,
                                      (s16)(base->unk_88 - 0x20)) -
                        base->unk_88;
                if (floor < (*(s16 *)((u8 *)obj + 0x92))) {
                    (*(s16 *)((u8 *)obj + 0x92)) = floor;
                    (*(u8 *)((u8 *)obj + 0x9D)) = 0;
                    ((S_801711B0_0 *)motion)->unk_14 = 0;
                    base->unk_1C |= 0x08000000;
                    func_801716F0();
                }
            }
        } else {
            if (!(((S_801711B0_1 *)part)->unk_14 & 0x40) &&
                ((S_801711B0_1 *)part)->unk_2C == D_800E23E0) {
                counter = (*(u16 *)((u8 *)obj + 0x9E));
                state_load = (s32)counter << 16;
                state_load >>= 16;
                effect_arg = state_load * 0x55;
                ASM_KEEP_DEP_NV(counter, effect_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
                counter++;
                (*(u16 *)((u8 *)obj + 0x9E)) = counter;
                (*(s32 *)((u8 *)obj + 0xA0)) +=
                    func_800644B8(effect_arg) << 4;
            }

            floor = -0x20;
            if (!((*(u16 *)((u8 *)obj + 0x98)) & 8)) {
                if (floor < (*(s16 *)((u8 *)obj + 0x92))) {
                    (*(u16 *)((u8 *)obj + 0x92)) = (*(u16 *)((u8 *)obj + 0x92)) - 8;
                } else if ((*(s16 *)((u8 *)obj + 0x92)) < -0x28) {
                    (*(u16 *)((u8 *)obj + 0x92)) = (*(u16 *)((u8 *)obj + 0x92)) + 8;
                }
            }
        }

        if ((*(u8 *)((u8 *)obj + 0xB5)) != 0) {
            (*(u16 *)((u8 *)obj + 0x92)) = 0;
        }
    }

    flags = base->unk_1C;
    if (flags & 0x40000000) {
        base->unk_1C = flags & 0xBFFFFFFF;
        floor = func_800BCB04(
            (((S_801711B0_1 *)part)->unk_24 << 6) | 0x20,
            (((S_801711B0_1 *)part)->unk_25 << 6) | 0x20,
            (s16)(base->unk_88 - 0x20));
        if (floor < 0x200) {
            (*(u16 *)((u8 *)obj + 0x92)) += base->unk_88 - floor;
            base->unk_88 = floor;
        }
    }

    ((S_801711B0_0 *)motion)->unk_0A = base->unk_88 +
        (*(u16 *)((u8 *)obj + 0x92)) - (*(u16 *)((u8 *)obj + 0xA2));
    ((S_801711B0_1 *)part)->unk_14 |= 0x40;
}
