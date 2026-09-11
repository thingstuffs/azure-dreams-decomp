#include "common.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_8003DB94(void *, s32, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern s16 func_800BCB04(s32, s32, s16);

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

/* Updates object callbacks, motion, sprite direction, and height. */
void func_800C9AAC(void *object_state, void *object_motion, void *object_part)
{
    u32 update_flags = D_80083462;
    register void *state ASM_REG("$17") = object_state;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *motion ASM_REG("$21") = object_motion;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *part ASM_REG("$19") = object_part;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    void *secondary = state;
    Callback callback;
    s16 direction;
    s16 direction_index;
    s32 part_flags;
    s32 adjusted_flags;
    s16 target_height;
    u16 old_height;

    if (update_flags & 0x2000) {
        Callback early_callback = (*(Callback *)((u8 *)state + (0x8C)));
        if (early_callback == (Callback)&D_800C9F34) {
            register void *callback_state ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(callback_state);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            early_callback(callback_state, motion, part, callback_state);
            return;
        } else {
            (*(u8 *)((u8 *)state + (0x71))) &= 0x7F;
        }
        return;
    }

    {
        register void *check_state ASM_REG("$4") = state;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        register void *check_motion ASM_REG("$5") = motion;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        register void *check_part ASM_REG("$6") = part;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(check_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(check_motion);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(check_part);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        check_state = state;
        check_motion = motion;
        check_part = part;
        if (func_800A9E70(check_state, check_motion, check_part, state) != 0) {
            return;
        }
    }

    callback = (*(Callback *)((u8 *)state + (0x8C)));
    if (callback != 0) {
        callback(state, motion, part, state);
    }
    D_800E0354[(*(u8 *)((u8 *)state + (0x9A)))](state, motion, part, state);

    if ((*(s16 *)((u8 *)state + (0xB8))) == 0) {
        ((S_800C9AAC_0 *)part)->unk_0C += 4;
        ((S_800C9AAC_0 *)part)->unk_0D += 4;
        ((S_800C9AAC_0 *)part)->unk_0E += 4;
        if (((S_800C9AAC_0 *)part)->unk_0C >= 0x40) {
            (*(s16 *)((u8 *)state + (0xB8))) = 1;
        }
    }

    ((S_800C9AAC_1 *)motion)->unk_00.at00.v += ((S_800C9AAC_1 *)motion)->unk_0C;
    ((S_800C9AAC_1 *)motion)->unk_04.at00.v += ((S_800C9AAC_1 *)motion)->unk_10;
    (*(s32 *)((u8 *)state + (0x90))) += ((S_800C9AAC_1 *)motion)->unk_14;

    part_flags = ((S_800C9AAC_0 *)part)->unk_14;
    adjusted_flags = part_flags & 0x8000;
    if (!adjusted_flags) {
        direction = ((D_80083228 + ((S_800C9AAC_2 *)secondary)->unk_2A + 0x100) >> 9) & 7;
        direction_index = direction;
        if ((*(s16 *)((u8 *)state + (0x94))) != direction_index) {
            func_8003DB94(part,
                ((s32 *)(*(void * *)((u8 *)state + (0xA4))))[direction_index],
                ((S_800C9AAC_0 *)part)->unk_04);
            (*(s16 *)((u8 *)state + (0x94))) = direction;
        }

        if (D_8006CCF8[direction_index] != 0) {
            adjusted_flags = ((S_800C9AAC_0 *)part)->unk_14 | 1;
        } else {
            adjusted_flags = ((S_800C9AAC_0 *)part)->unk_14 & 0xFFFE;
        }
        ((S_800C9AAC_0 *)part)->unk_14 = adjusted_flags;
        func_800A020C(((S_800C9AAC_2 *)secondary)->unk_1C, (u8 *)part + 0xC);

        if (!(((S_800C9AAC_2 *)secondary)->unk_1C & 0x20)) {
            if (!(((S_800C9AAC_0 *)part)->unk_14 & 0x40)) {
                func_800478B8(part);
            }
        } else {
            ((S_800C9AAC_0 *)part)->unk_14 |= 0x7000;
            ((S_800C9AAC_2 *)secondary)->unk_1C &= 0xFFFBFFFF;
        }

        if (((S_800C9AAC_2 *)secondary)->unk_1C & 0x40000) {
            if (!(((S_800C9AAC_0 *)part)->unk_14 & 0x40)) {
                u16 phase = (*(u16 *)((u8 *)state + (0x9E)));
                (*(u16 *)((u8 *)state + (0x9E))) = phase + 1;
                (*(s32 *)((u8 *)state + (0xA0))) += func_800644B8((s16)phase * 0xAA) << 5;
            }

            if (!((*(u16 *)((u8 *)state + (0x98))) & 8)) {
                s32 min_height = -0x20;
                s16 height;
                func_800BCB04(((S_800C9AAC_1 *)motion)->unk_00.at02.v, ((S_800C9AAC_1 *)motion)->unk_04.at02.v,
                    (s16)(((S_800C9AAC_2 *)secondary)->unk_88 - 0x20));
                height = (*(s16 *)((u8 *)state + (0x92)));
                if (min_height < height) {
                    (*(u16 *)((u8 *)state + (0x92))) -= 8;
                }
                else if (height < -0x28) {
                    (*(u16 *)((u8 *)state + (0x92))) += 8;
                }
            }
        } else {
            register s32 height_adjustment ASM_REG("$2") = (*(s32 *)((u8 *)state + (0xA0)));   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 height_position = (*(s32 *)((u8 *)state + (0x90)));
            u32 motion_flags = (*(u16 *)((u8 *)state + (0x98)));
            do {
                (*(u16 *)((u8 *)state + (0x9E))) = 0;
            } while (0);
            (*(s32 *)((u8 *)state + (0xA0))) = 0;
            height_position -= height_adjustment;
            (*(s32 *)((u8 *)state + (0x90))) = height_position;

            if (!(motion_flags & 8)) {
                target_height = func_800BCB04(((S_800C9AAC_1 *)motion)->unk_00.at02.v, ((S_800C9AAC_1 *)motion)->unk_04.at02.v,
                    (s16)(((S_800C9AAC_2 *)secondary)->unk_88 - 0x20)) -
                    ((S_800C9AAC_2 *)secondary)->unk_88;
                old_height = (*(u16 *)((u8 *)state + (0x92)));
                if ((*(s16 *)((u8 *)state + (0x92))) < target_height) {
                    (*(u16 *)((u8 *)state + (0x92))) = old_height + 8;
                    if (target_height < (*(s16 *)((u8 *)state + (0x92)))) {
                        (*(s16 *)((u8 *)state + (0x92))) = target_height;
                    }
                } else {
                    (*(s16 *)((u8 *)state + (0x92))) = target_height;
                }
            }
        }
    } else {
        adjusted_flags = part_flags & 0x800;
        if (adjusted_flags) {
            adjusted_flags = part_flags & 0x8FFF;
        } else {
            adjusted_flags = part_flags | 0x7000;
        }
        ((S_800C9AAC_0 *)part)->unk_14 = adjusted_flags;
    }

    {
        s32 object_flags;
        object_flags = ((S_800C9AAC_2 *)secondary)->unk_1C;
        if (object_flags & 0x40000000) {
            adjusted_flags = object_flags & 0xBFFFFFFF;
            ((S_800C9AAC_2 *)secondary)->unk_1C = adjusted_flags;
            target_height = func_800BCB04(
                (((S_800C9AAC_0 *)part)->unk_24 << 6) | 0x20,
                (((S_800C9AAC_0 *)part)->unk_25 << 6) | 0x20,
                (s16)(((S_800C9AAC_2 *)secondary)->unk_88 - 0x20));
            if (target_height < 0x200) {
                (*(u16 *)((u8 *)state + (0x92))) += ((S_800C9AAC_2 *)secondary)->unk_88 - target_height;
                ((S_800C9AAC_2 *)secondary)->unk_88 = target_height;
            }
        }
    }

    ((S_800C9AAC_1 *)motion)->unk_0A = ((S_800C9AAC_2 *)secondary)->unk_88 +
        (*(u16 *)((u8 *)state + (0x92))) - (*(u16 *)((u8 *)state + (0xA2)));
    ((S_800C9AAC_0 *)part)->unk_14 |= 0x40;
}
