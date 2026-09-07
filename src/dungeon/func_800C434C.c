#include "common.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_8003DB94(void *, s32, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern s16 func_800BCB04(s32, s32, s16);
extern void func_800C9CA0(void);
extern void func_800C9D08(void);
extern void func_800C9E68();
extern void func_800C9F0C();

extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800C9F34;
extern Callback D_800E0354[];


typedef struct S_800C9AAC_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800C9AAC_0;   /* part in func_800C9AAC */

typedef struct S_800C9AAC_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800C9AAC_1;   /* motion in func_800C9AAC */

typedef struct S_800C9AAC_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_800C9AAC_2;   /* secondary in func_800C9AAC */

void func_800C9AAC(void *arg0, void *arg1, void *arg2)
{
    u32 entry_value = D_80083462;
    register void *state ASM_REG("$17") = arg0;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *motion ASM_REG("$21") = arg1;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *part ASM_REG("$19") = arg2;   /* MATCH pin: retail delay-slot fill depends on it */
    S_800C9AAC_2 *secondary = state;
    Callback callback;
    s16 direction;
    s16 direction_index;
    s32 flags;
    s32 adjusted_flags;
    s16 target;
    u16 old_height;

    if (entry_value & 0x2000) {
        Callback early_callback = (*(Callback *)((u8 *)state + 0x8C));
        if (early_callback == (Callback)&D_800C9F34) {
            register void *incoming_a0 ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */
            ASM_KEEP(incoming_a0);   /* MATCH pin: retail register colouring depends on it */
            early_callback(incoming_a0, motion, part, incoming_a0);
            func_800C9F0C(incoming_a0);
            return;
        } else {
            (*(u8 *)((u8 *)state + 0x71)) &= 0x7F;
        }
        return;
    }

    {
        register void *call_a0 ASM_REG("$4") = state;   /* MATCH pin: retail delay-slot fill depends on it */
        register void *call_a1 ASM_REG("$5") = motion;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        register void *call_a2 ASM_REG("$6") = part;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ASM_KEEP(call_a0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ASM_KEEP(call_a1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ASM_KEEP(call_a2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        call_a0 = state;
        call_a1 = motion;
        call_a2 = part;
        if (func_800A9E70(call_a0, call_a1, call_a2, state) != 0) {
            return;
        }
    }

    callback = (*(Callback *)((u8 *)state + 0x8C));
    if (callback != 0) {
        callback(state, motion, part, state);
    }
    D_800E0354[(*(u8 *)((u8 *)state + 0x9A))](state, motion, part, state);

    if ((*(s16 *)((u8 *)state + 0xB8)) == 0) {
        ((S_800C9AAC_0 *)part)->unk_0C += 4;
        ((S_800C9AAC_0 *)part)->unk_0D += 4;
        ((S_800C9AAC_0 *)part)->unk_0E += 4;
        if (((S_800C9AAC_0 *)part)->unk_0C >= 0x40) {
            (*(s16 *)((u8 *)state + 0xB8)) = 1;
        }
    }

    ((S_800C9AAC_1 *)motion)->unk_00.at00.v += ((S_800C9AAC_1 *)motion)->unk_0C;
    ((S_800C9AAC_1 *)motion)->unk_04.at00.v += ((S_800C9AAC_1 *)motion)->unk_10;
    (*(s32 *)((u8 *)state + 0x90)) += ((S_800C9AAC_1 *)motion)->unk_14;

    flags = ((S_800C9AAC_0 *)part)->unk_14;
    adjusted_flags = flags & 0x8000;
    if (!adjusted_flags) {
        direction = ((D_80083228 + secondary->unk_2A + 0x100) >> 9) & 7;
        direction_index = direction;
        if ((*(s16 *)((u8 *)state + 0x94)) != direction_index) {
            func_8003DB94(part,
                ((s32 *)(*(void * *)((u8 *)state + 0xA4)))[direction_index],
                ((S_800C9AAC_0 *)part)->unk_04);
            (*(s16 *)((u8 *)state + 0x94)) = direction;
        }

        if (D_8006CCF8[direction_index] != 0) {
            u32 tail_value;
            tail_value = ((S_800C9AAC_0 *)part)->unk_14 | 1;
            ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_800C9CA0();
            return;
        }

        ((S_800C9AAC_0 *)part)->unk_14 &= 0xFFFE;
        func_800A020C(secondary->unk_1C, (u8 *)part + 0xC);

        if (!(secondary->unk_1C & 0x20)) {
            if (!(((S_800C9AAC_0 *)part)->unk_14 & 0x40)) {
                func_800478B8(part);
                func_800C9D08();
                return;
            }
        } else {
            ((S_800C9AAC_0 *)part)->unk_14 |= 0x7000;
            secondary->unk_1C &= 0xFFFBFFFF;
        }

        if (secondary->unk_1C & 0x40000) {
            if (!(((S_800C9AAC_0 *)part)->unk_14 & 0x40)) {
                u16 phase = (*(u16 *)((u8 *)state + 0x9E));
                (*(u16 *)((u8 *)state + 0x9E)) = phase + 1;
                (*(s32 *)((u8 *)state + 0xA0)) += func_800644B8((s16)phase * 0xAA) << 5;
            }

            if (!((*(u16 *)((u8 *)state + 0x98)) & 8)) {
                s32 lower_bound = -0x20;
                s16 height;
                func_800BCB04(((S_800C9AAC_1 *)motion)->unk_00.at02.v, ((S_800C9AAC_1 *)motion)->unk_04.at02.v,
                    (s16)(secondary->unk_88 - 0x20));
                height = (*(s16 *)((u8 *)state + 0x92));
                if (lower_bound < height) {
                    (*(u16 *)((u8 *)state + 0x92)) -= 8;
                    func_800C9E68(height);
                    return;
                }
                if (height < -0x28) {
                    (*(u16 *)((u8 *)state + 0x92)) += 8;
                    func_800C9E68();
                    return;
                }
            }
        } else {
            register s32 accumulated ASM_REG("$2") = (*(s32 *)((u8 *)state + 0xA0));   /* MATCH pin: load-bearing for the whole function shape */
            s32 position = (*(s32 *)((u8 *)state + 0x90));
            register u32 motion_flags ASM_REG("$4") = (*(u16 *)((u8 *)state + 0x98));   /* MATCH pin: retail delay-slot fill depends on it */
            (*(u16 *)((u8 *)state + 0x9E)) = 0;
            (*(s32 *)((u8 *)state + 0xA0)) = 0;
            position -= accumulated;
            (*(s32 *)((u8 *)state + 0x90)) = position;

            if (!(motion_flags & 8)) {
                target = func_800BCB04(((S_800C9AAC_1 *)motion)->unk_00.at02.v, ((S_800C9AAC_1 *)motion)->unk_04.at02.v,
                    (s16)(secondary->unk_88 - 0x20)) -
                    secondary->unk_88;
                old_height = (*(u16 *)((u8 *)state + 0x92));
                if ((*(s16 *)((u8 *)state + 0x92)) < target) {
                    (*(u16 *)((u8 *)state + 0x92)) = old_height + 8;
                    if (target < (*(s16 *)((u8 *)state + 0x92))) {
                        (*(s16 *)((u8 *)state + 0x92)) = target;
                        func_800C9E68();
                        return;
                    }
                } else {
                    (*(s16 *)((u8 *)state + 0x92)) = target;
                    func_800C9E68();
                    return;
                }
            }
        }
    } else {
        adjusted_flags = flags & 0x800;
        if (adjusted_flags) {
            adjusted_flags = flags & 0x8FFF;
        } else {
            adjusted_flags = flags | 0x7000;
        }
        ((S_800C9AAC_0 *)part)->unk_14 = adjusted_flags;
    }

    {
        s32 object_flags;
        object_flags = secondary->unk_1C;
        if (object_flags & 0x40000000) {
        adjusted_flags = object_flags & 0xBFFFFFFF;
        secondary->unk_1C = adjusted_flags;
        target = func_800BCB04(
            (((S_800C9AAC_0 *)part)->unk_24 << 6) | 0x20,
            (((S_800C9AAC_0 *)part)->unk_25 << 6) | 0x20,
            (s16)(secondary->unk_88 - 0x20));
        if (target < 0x200) {
            (*(u16 *)((u8 *)state + 0x92)) += secondary->unk_88 - target;
            secondary->unk_88 = target;
        }
    }
    }

    ((S_800C9AAC_1 *)motion)->unk_0A = secondary->unk_88 +
        (*(u16 *)((u8 *)state + 0x92)) - (*(u16 *)((u8 *)state + 0xA2));
    ((S_800C9AAC_0 *)part)->unk_14 |= 0x40;
}

/* MECHANISM: A real D_80083462 halfword read emits the two-word pre-frame preamble;
   the 0x30 frame holds s1/s5/s3/s2/s4/s0 in retail order, with guarded base pins.
   Reusing the $v0 flags local preserves the retail mask/store destination pair. */
