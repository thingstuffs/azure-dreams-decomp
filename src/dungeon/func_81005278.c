#include "common.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern u8 D_8006CCF8[9];
extern s16 D_80083228[5];
extern u8 D_80083460[9];
extern u8 D_80171058[];
extern u8 D_80174880[9];
extern Callback D_80174900[];

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s32 func_800BCB04(s32, s32, s32);


typedef struct S_80170A78_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170A78_0;   /* arg1 in func_80170A78 */

typedef struct S_80170A78_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    union { u8 * p; void * p2; } unk_2C;   /* accessed as both */
} S_80170A78_1;   /* arg2 in func_80170A78 */

typedef struct S_80170A78_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80170A78_2;   /* state in func_80170A78 */

/* Updates object callbacks, movement, facing, and terrain-relative height. */
void func_80170A78(void *input_obj, void *input_motion, void *input_part)
{
    void *obj = input_obj;
    void *motion = input_motion;
    void *part = input_part;
    register void *state ASM_REG("$18") = input_obj;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 mode_or_dir ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 value_bits;
    Callback callback;
    s32 height_offset;
    s16 floor_delta;
    u16 part_flags;
    u16 bob_phase;
    register s32 state_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 bob_offset;
    u8 direction_flag;

    if (*(u16 *)(D_80083460 + 2) & 0x2000) {
        callback = (*(Callback *)((u8 *)input_obj + 0x8C));
        if (callback == (Callback)D_80171058) {
            void *entry_obj = input_obj;
            ASM_KEEP(entry_obj);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            callback(entry_obj, input_motion, input_part, entry_obj);
            return;
        } else {
            (*(u8 *)((u8 *)input_obj + 0x71)) &= 0x7F;
            return;
        }
    }

    ASM_KEEP(obj);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    value_bits = *(volatile u8 *)((u8 *)obj + 0x6D);
    value_bits <<= 24;
    mode_or_dir = (s32)value_bits >> 24;
    if (func_800A9E70(obj, motion, part, obj) != 0) {
        return;
    }

    {
        Callback update_callback;
        update_callback = (*(Callback *)((u8 *)obj + 0x8C));
        if (update_callback != 0) {
            update_callback(obj, motion, part, obj);
        }
    }
    D_80174900[(*(u8 *)((u8 *)obj + 0x9A))](obj, motion, part, obj);
    value_bits = (u32)mode_or_dir << 16;
    if (((s32)value_bits >> 16) != (*(s8 *)((u8 *)obj + 0x6D))) {
        func_800AA36C(obj, motion, part, obj);
    }

    {
        s32 old_x = ((S_80170A78_0 *)motion)->unk_00.at00.v;
        s32 velocity_x = ((S_80170A78_0 *)motion)->unk_0C;
        s32 old_y = ((S_80170A78_0 *)motion)->unk_04.at00.v;
        s32 velocity_y = ((S_80170A78_0 *)motion)->unk_10;
        ((S_80170A78_0 *)motion)->unk_00.at00.v = old_x + velocity_x;
        ((S_80170A78_0 *)motion)->unk_04.at00.v = old_y + velocity_y;

        if (!((*(s32 *)((u8 *)obj + 0x1C)) & 0x40000) &&
            !((*(u16 *)((u8 *)obj + 0x98)) & 8)) {
            ((S_80170A78_0 *)motion)->unk_14 += (*(s8 *)((u8 *)obj + 0x9D)) * 0x14000;
            (*(u8 *)((u8 *)obj + 0x9D)) += 1;
        } else {
            (*(u8 *)((u8 *)obj + 0x9D)) = 0;
        }
    }

    (*(s32 *)((u8 *)obj + 0x90)) += ((S_80170A78_0 *)motion)->unk_14;
    part_flags = ((S_80170A78_1 *)part)->unk_14;
    if (!(part_flags & 0x8000)) {
        value_bits = *(s16 *)((u8 *)D_80083460 - 0x238) +
            ((S_80170A78_2 *)state)->unk_2A + 0x100;
        input_motion = ((s32)value_bits >> 9) & 7;
        mode_or_dir = input_motion;
        if ((*(s16 *)((u8 *)obj + 0x94)) != mode_or_dir) {
            func_80047738(part,
                *(u8 *)(((S_80170A78_1 *)part)->unk_2C.p + mode_or_dir),
                ((S_80170A78_1 *)part)->unk_04);
            (*(s16 *)((u8 *)obj + 0x94)) = input_motion;
        }
        direction_flag = D_8006CCF8[mode_or_dir];
        ASM_KEEP(mode_or_dir);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (direction_flag != 0) {
            value_bits = *(volatile u16 *)((u8 *)part + 0x14) | 1;
        } else {
            value_bits = ((S_80170A78_1 *)part)->unk_14 & 0xFFFE;
        }

        ((S_80170A78_1 *)part)->unk_14 = value_bits;

        func_800A020C(((S_80170A78_2 *)state)->unk_1C, (u8 *)part + 0xC);
        if (!(((S_80170A78_2 *)state)->unk_1C & 0x20)) {
            if (!(((S_80170A78_1 *)part)->unk_14 & 0x40)) {
                func_800478B8(part);
            }
        } else {
            ((S_80170A78_1 *)part)->unk_14 |= 0x7000;
            ((S_80170A78_2 *)state)->unk_1C &= 0xFFFBFFFF;
        }
        value_bits = 0xF7FFFFFF;
        state_flags = ((S_80170A78_2 *)state)->unk_1C & value_bits;
        ((S_80170A78_2 *)state)->unk_1C = state_flags;
        if (!(state_flags & 0x40000)) {
            goto reset_height;
        }

        if (!(((S_80170A78_1 *)part)->unk_14 & 0x40) &&
            ((S_80170A78_1 *)part)->unk_2C.p2 == D_80174880) {
            bob_phase = (*(u16 *)((u8 *)obj + 0xB2));
            (*(u16 *)((u8 *)obj + 0xB2)) = bob_phase + 1;
            (*(s32 *)((u8 *)obj + 0xA4)) += func_800644B8((s16)bob_phase * 0xAA) << 5;
        }
        if (!((*(u16 *)((u8 *)obj + 0x98)) & 8)) {
            floor_delta = func_800BCB04(((S_80170A78_0 *)motion)->unk_00.at02.v, ((S_80170A78_0 *)motion)->unk_04.at02.v,
                        (s16)(((S_80170A78_2 *)state)->unk_88 - 0x20)) -
                    ((S_80170A78_2 *)state)->unk_88;
            height_offset = (*(s16 *)((u8 *)obj + 0x92));
            if (height_offset > floor_delta - 0x18) {
                (*(s16 *)((u8 *)obj + 0x92)) = (*(s16 *)((u8 *)obj + 0x92)) - 8;
                goto finish_height;
            }
            if (height_offset < floor_delta - 0x20) {
                (*(s16 *)((u8 *)obj + 0x92)) = (*(u16 *)((u8 *)obj + 0x92)) + 8;
            }
        }
        goto finish_height;
    }

    if (part_flags & 0x800) {
        ((S_80170A78_1 *)part)->unk_14 = part_flags & 0x8FFF;
    } else {
        ((S_80170A78_1 *)part)->unk_14 = part_flags | 0x7000;
    }
    value_bits = 0xF7FFFFFF;
    state_flags = ((S_80170A78_2 *)state)->unk_1C & value_bits;
    ((S_80170A78_2 *)state)->unk_1C = state_flags;
    if (!(state_flags & 0x40000)) {
reset_height:
        bob_offset = (*(s32 *)((u8 *)obj + 0xA4));
        (*(u16 *)((u8 *)obj + 0xB2)) = 0;
        (*(s32 *)((u8 *)obj + 0xA4)) = 0;
        (*(s32 *)((u8 *)obj + 0x90)) -= bob_offset;
        if (!((*(u16 *)((u8 *)obj + 0x98)) & 8)) {
            floor_delta = func_800BCB04(((S_80170A78_0 *)motion)->unk_00.at02.v, ((S_80170A78_0 *)motion)->unk_04.at02.v,
                        (s16)(((S_80170A78_2 *)state)->unk_88 - 0x20)) -
                    ((S_80170A78_2 *)state)->unk_88;
            if (floor_delta < (*(s16 *)((u8 *)obj + 0x92))) {
                (*(s16 *)((u8 *)obj + 0x92)) = floor_delta;
                (*(u8 *)((u8 *)obj + 0x9D)) = 0;
                ((S_80170A78_0 *)motion)->unk_14 = 0;
                ((S_80170A78_2 *)state)->unk_1C |= 0x08000000;
                goto finish_height;
            }
        }
        goto finish_height;
    }

    if (!(((S_80170A78_1 *)part)->unk_14 & 0x40) &&
        ((S_80170A78_1 *)part)->unk_2C.p2 == D_80174880) {
        u16 bob_phase;
        bob_phase = (*(u16 *)((u8 *)obj + 0xB2));
        (*(u16 *)((u8 *)obj + 0xB2)) = bob_phase + 1;
        (*(s32 *)((u8 *)obj + 0xA4)) += func_800644B8((s16)bob_phase * 0xAA) << 5;
    }
    if (!((*(u16 *)((u8 *)obj + 0x98)) & 8)) {
        floor_delta = func_800BCB04(((S_80170A78_0 *)motion)->unk_00.at02.v, ((S_80170A78_0 *)motion)->unk_04.at02.v,
                    (s16)(((S_80170A78_2 *)state)->unk_88 - 0x20)) -
                ((S_80170A78_2 *)state)->unk_88;
        height_offset = (*(s16 *)((u8 *)obj + 0x92));
        if (height_offset > floor_delta - 0x18) {
            (*(s16 *)((u8 *)obj + 0x92)) = (*(s16 *)((u8 *)obj + 0x92)) - 8;
            goto finish_height;
        }
        if (height_offset < floor_delta - 0x20) {
            (*(s16 *)((u8 *)obj + 0x92)) = (*(u16 *)((u8 *)obj + 0x92)) + 8;
        }
    }

finish_height:
    if (((S_80170A78_2 *)state)->unk_1C & 0x40000000) {
        ((S_80170A78_2 *)state)->unk_1C &= 0xBFFFFFFF;
        floor_delta = func_800BCB04((((S_80170A78_1 *)part)->unk_24 << 6) | 0x20,
            (((S_80170A78_1 *)part)->unk_25 << 6) | 0x20,
            (s16)(((S_80170A78_2 *)state)->unk_88 - 0x20));
        if ((s16)floor_delta < 0x200) {
            (*(s16 *)((u8 *)obj + 0x92)) += ((S_80170A78_2 *)state)->unk_88 - floor_delta;
            ((S_80170A78_2 *)state)->unk_88 = floor_delta;
        }
    }
    ((S_80170A78_0 *)motion)->unk_0A = ((S_80170A78_2 *)state)->unk_88 +
        (*(u16 *)((u8 *)obj + 0x92)) - (*(u16 *)((u8 *)obj + 0xA6));
    ((S_80170A78_1 *)part)->unk_14 |= 0x40;
}
