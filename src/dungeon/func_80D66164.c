#include "common.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s16 func_800BCB04(u16, u16, s16);

extern u8 D_8006CCF8[];
extern s16 D_80083228[];
extern u16 D_80083462[];
extern u8 D_800E2348[];
extern void D_80171F1C(void *, void *, void *, void *);
extern Callback D_8017664C[];


typedef struct S_80171964_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80171964_0;   /* motion in func_80171964 */

typedef struct S_80171964_1 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171964_1;   /* part in func_80171964 */

typedef struct S_80171964_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80171964_2;   /* base in func_80171964 */

/* Updates object callbacks, motion, sprite direction, and ground-relative height. */
void func_80171964(void *object_arg, void *motion_arg, void *part_arg)
{
    register void *part ASM_REG("$20") = part_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *base = object_arg;
    Callback first_callback;
    Callback dispatch_callback;
    s32 flags;
    s32 bob_offset;
    s16 ground_height;
    s32 height_adjust;
    s32 height;
    register u32 raw_height ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u16 part_flags;

    if (D_80083462[0] & 0x2000) {
        first_callback = (*(Callback *)((u8 *)object_arg + (0x8C)));
        if (first_callback == (Callback)D_80171F1C) {
            {
                void *entry_obj = object_arg;

                first_callback(entry_obj, motion_arg, part_arg, entry_obj);
            }
            return;
        }
        (*(u8 *)((u8 *)object_arg + (0x71))) &= 0x7F;
        return;
    }

    ASM_KEEP(part);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    {
        s16 old_state = (s8)(*(u8 *)((u8 *)object_arg + (0x6D)));

        if (func_800A9E70(object_arg, motion_arg, part, object_arg) != 0) {
            return;
        }
        dispatch_callback = (*(Callback *)((u8 *)object_arg + (0x8C)));
        if (dispatch_callback != 0) {
            dispatch_callback(object_arg, motion_arg, part, object_arg);
        }
        D_8017664C[(*(u8 *)((u8 *)object_arg + (0x9A)))](object_arg, motion_arg, part, object_arg);
        if ((s16)old_state != (s8)(*(u8 *)((u8 *)object_arg + (0x6D)))) {
            func_800AA36C(object_arg, motion_arg, part, object_arg);
        }
    }

    ((S_80171964_0 *)motion_arg)->unk_00.at00.v += ((S_80171964_0 *)motion_arg)->unk_0C;
    ((S_80171964_0 *)motion_arg)->unk_04.at00.v += ((S_80171964_0 *)motion_arg)->unk_10;

    if (!((*(u32 *)((u8 *)object_arg + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
        ((S_80171964_0 *)motion_arg)->unk_14 += (*(s8 *)((u8 *)object_arg + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)object_arg + (0x9D)))++;
    } else {
        (*(u8 *)((u8 *)object_arg + (0x9D))) = 0;
    }

    (*(s32 *)((u8 *)object_arg + (0x90))) += ((S_80171964_0 *)motion_arg)->unk_14;
    part_flags = ((S_80171964_1 *)part)->unk_14;

    if (!(part_flags & 0x8000)) {
        s32 view_direction;
        s32 direction_index;
        s16 page_index;
        u8 *page_table;

        view_direction = (D_80083228[0] + ((S_80171964_2 *)base)->unk_2A + 0x100) >> 9;
        direction_index = view_direction & 7;
        page_index = direction_index;
        if ((*(s16 *)((u8 *)object_arg + (0x94))) != (s16)page_index) {
            func_80047738(part,
                (*(u8 *)((u8 *)(((S_80171964_1 *)part)->unk_2C) + (page_index))),
                ((S_80171964_1 *)part)->unk_04.s8);
            (*(s16 *)((u8 *)object_arg + (0x94))) = direction_index;
        }
        page_table = D_8006CCF8;
        if (page_table[page_index] != 0) {
            ((S_80171964_1 *)part)->unk_14 |= 1;
        } else {
            ((S_80171964_1 *)part)->unk_14 &= 0xFFFE;
        }
        func_800A020C(((S_80171964_2 *)base)->unk_1C.s, (u8 *)part + 0xC);

        if (!(((S_80171964_2 *)base)->unk_1C.u & 0x20)) {
            if (!(((S_80171964_1 *)part)->unk_14 & 0x40)) {
                func_800478B8(part);
            }
        } else {
            ((S_80171964_1 *)part)->unk_14 |= 0x7000;
            ((S_80171964_2 *)base)->unk_1C.u &= 0xFFFBFFFF;
        }

        flags = ((S_80171964_2 *)base)->unk_1C.u;
        flags &= 0xF7FFFFFF;
        ((S_80171964_2 *)base)->unk_1C.u = flags;
        flags &= 0x40000;
        if (!flags) {
            goto clear_velocity;
        }

        if (!(((S_80171964_1 *)part)->unk_14 & 0x40) &&
            ((S_80171964_1 *)part)->unk_2C == D_800E2348) {
            if (((S_80171964_1 *)part)->unk_04.u16 == 0x400) {
                (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
            }
            {
                u16 bob_frame = (*(u16 *)((u8 *)object_arg + (0x9E)));

                (*(u16 *)((u8 *)object_arg + (0x9E))) = bob_frame + 1;
                (*(s32 *)((u8 *)object_arg + (0xA0))) = -func_800644B8((s16)bob_frame * 0xC3) << 7;
            }
        }
        if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
            height_adjust = -0x20;
            height = *(s16 *)((u8 *)object_arg + 0x92);
            raw_height = *(volatile u16 *)((u8 *)object_arg + 0x92);
            if (height_adjust < height) {
                height_adjust = raw_height - 8;
                *(s16 *)((u8 *)object_arg + 0x92) = height_adjust;
                goto common_tail;
            }
            goto raise_floor;
        }
        goto common_tail;
    }

    if (part_flags & 0x800) {
        ((S_80171964_1 *)part)->unk_14 = part_flags & 0x8FFF;
    } else {
        ((S_80171964_1 *)part)->unk_14 = part_flags | 0x7000;
    }
    flags = ((S_80171964_2 *)base)->unk_1C.u;
    flags &= 0xF7FFFFFF;
    ((S_80171964_2 *)base)->unk_1C.u = flags;
    flags &= 0x40000;
    if (!flags) {
clear_velocity:
        bob_offset = (*(s32 *)((u8 *)object_arg + (0xA0)));
        (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
        (*(s32 *)((u8 *)object_arg + (0xA0))) = 0;
        (*(s32 *)((u8 *)object_arg + (0x90))) -= bob_offset;
        if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
            ground_height = func_800BCB04(((S_80171964_0 *)motion_arg)->unk_00.at02.v,
                                  ((S_80171964_0 *)motion_arg)->unk_04.at02.v,
                                  (s16)(((S_80171964_2 *)base)->unk_88 - 0x20)) -
                    ((S_80171964_2 *)base)->unk_88;
            if (ground_height < (*(s16 *)((u8 *)object_arg + (0x92)))) {
                (*(s16 *)((u8 *)object_arg + (0x92))) = ground_height;
                (*(u8 *)((u8 *)object_arg + (0x9D))) = 0;
                ((S_80171964_0 *)motion_arg)->unk_14 = 0;
                ((S_80171964_2 *)base)->unk_1C.u |= 0x08000000;
                goto common_tail;
            }
        }
        goto common_tail;
    }

    if (!(((S_80171964_1 *)part)->unk_14 & 0x40) &&
        ((S_80171964_1 *)part)->unk_2C == D_800E2348) {
        if (((S_80171964_1 *)part)->unk_04.u16 == 0x400) {
            (*(u16 *)((u8 *)object_arg + (0x9E))) = 0;
        }
        {
            u16 bob_frame = (*(u16 *)((u8 *)object_arg + (0x9E)));

            (*(u16 *)((u8 *)object_arg + (0x9E))) = bob_frame + 1;
            (*(s32 *)((u8 *)object_arg + (0xA0))) = -func_800644B8((s16)bob_frame * 0xC3) << 7;
        }
    }
    if (!((*(u16 *)((u8 *)object_arg + (0x98))) & 8)) {
        height_adjust = -0x20;
        height = *(s16 *)((u8 *)object_arg + 0x92);
        raw_height = *(volatile u16 *)((u8 *)object_arg + 0x92);
        if (height_adjust < height) {
            height_adjust = raw_height - 8;
            *(s16 *)((u8 *)object_arg + 0x92) = height_adjust;
        } else {
raise_floor:
            height_adjust = height < -0x28;
            if (height_adjust) {
                height_adjust = raw_height + 8;
                *(s16 *)((u8 *)object_arg + 0x92) = height_adjust;
            }
        }
    }

common_tail:
    flags = ((S_80171964_2 *)base)->unk_1C.u;
    if (flags & 0x40000000) {
        ((S_80171964_2 *)base)->unk_1C.u = flags & 0xBFFFFFFF;
        ground_height = func_800BCB04(
            (((S_80171964_1 *)part)->unk_24 << 6) | 0x20,
            (((S_80171964_1 *)part)->unk_25 << 6) | 0x20,
            (s16)(((S_80171964_2 *)base)->unk_88 - 0x20));
        if (ground_height < 0x200) {
            (*(u16 *)((u8 *)object_arg + (0x92))) += ((S_80171964_2 *)base)->unk_88 - ground_height;
            ((S_80171964_2 *)base)->unk_88 = ground_height;
        }
    }
    if ((*(u8 *)((u8 *)object_arg + (0x9A))) != 0x18) {
        ((S_80171964_0 *)motion_arg)->unk_0A =
            ((S_80171964_2 *)base)->unk_88 + (*(u16 *)((u8 *)object_arg + (0x92))) -
            (*(u16 *)((u8 *)object_arg + (0xA2)));
    } else {
        ((S_80171964_0 *)motion_arg)->unk_0A = (*(u16 *)((u8 *)object_arg + (0x92))) - (*(u16 *)((u8 *)object_arg + (0xA2)));
    }
    ((S_80171964_1 *)part)->unk_14 |= 0x40;
}
