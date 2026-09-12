#include "common.h"

typedef struct S_8017087C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8017087C_0;   /* obj in func_8017087C */

typedef struct S_8017087C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8017087C_1;   /* work in func_8017087C */

typedef struct S_8017087C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8017087C_2;   /* part_a in func_8017087C */

typedef struct S_8017087C_3 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x10];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
    void * unk_2C;
} S_8017087C_3;   /* part_b in func_8017087C */

typedef struct S_8017087C_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
    u8 pad_9B[0x9];
    void * unk_A4;
} S_8017087C_4;   /* slot in func_8017087C */

typedef struct S_8017087C_5 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x2];
    s8 unk_9C;
    u8 pad_9D[0x1];
    s16 unk_9E;
} S_8017087C_5;   /* slot_base in func_8017087C */

typedef struct S_8017087C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x90];
    void * unk_98;
} S_8017087C_6;   /* new_work in func_8017087C */

typedef struct S_8017087C_7 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x12];
    s32 unk_28;
} S_8017087C_7;   /* entry in func_8017087C */

typedef struct S_8017087C_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8017087C_8;   /* work_copy in func_8017087C */

typedef struct S_8017087C_9 {
    u8 pad_00[0x10];
    void * unk_10;
} S_8017087C_9;   /* callback_obj in func_8017087C */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30();
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_80047784(void *, s32, s32);
extern void func_800478E8(void *, void *, s32);
extern void func_800AA36C(void *, void *, void *, void *);
extern void func_800D78C0(void *, void *, void *, void *);
extern void *func_80170A7C(void);
extern void func_80170BB8(void *, void *, void *);
extern void func_8017140C(void *, void *, void *, void *);

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_800D71A8[];
extern u8 D_8017586C[];
extern u8 D_80175894[];

/* Create an object with kind-dependent flags and initialize its three child objects. */
void *func_8017087C(s16 kind_flags, s16 tile_x, s16 tile_y, s16 part_id)
{
    s32 kind;
    void *obj;
    S_8017087C_2 *part_a;
    S_8017087C_5 *slot_base;
    S_8017087C_8 *child_slot;
    s32 entry_id_fixed;
    void *part_b;
    register void *work ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s8 saved_x;
    s16 saved_part_id;
    s8 saved_y;
    s32 setup_value;
    register s32 work_flags;
    register void *alloc_or_entry ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 entry_id ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 entry_mode ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s32 child_index;
    u8 *slot;
    s32 entry_index;

    work = 0;
    alloc_or_entry = (void *)274;
    saved_x = tile_x;
    saved_part_id = part_id;
    saved_y = tile_y;
    obj = func_8003FD64((s32)alloc_or_entry, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8017087C_0 *)obj)->unk_10 = func_80170BB8;
        ((S_8017087C_1 *)work)->unk_13 = 6;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_8017087C_0 *)obj)->unk_08;
        part_a->unk_0A = saved_part_id;
        part_b = ((S_8017087C_0 *)obj)->unk_0C;
        slot_base = work;
        kind = kind_flags & 3;
        ((S_8017087C_3 *)part_b)->unk_2C = D_8017586C;
        ((S_8017087C_3 *)part_b)->unk_24 = saved_x;
        ((S_8017087C_3 *)part_b)->unk_25 = saved_y;

        if (kind == 1) {
            setup_value = ((S_8017087C_1 *)work)->unk_14 | 0x6000;
            work_flags = ((S_8017087C_1 *)work)->unk_1C | 0x6000;
            goto set_flags;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        setup_value = ((S_8017087C_1 *)work)->unk_14 | 0x2000;
        work_flags = ((S_8017087C_1 *)work)->unk_1C | 0x2000;

set_flags:
        ((S_8017087C_1 *)work)->unk_14 = setup_value;
        ((S_8017087C_1 *)work)->unk_1C = work_flags;
        goto post_kind;

normal_kind:
        if (((kind_flags & ~3) << 16) == 0) {
            if (!(((S_8017087C_1 *)work)->unk_14 & 0x200)) {
                setup_value = func_800A6D30();
                if (!(setup_value & 1)) {
                    goto init_parts;
                }
                ((S_8017087C_1 *)work)->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30() & 0x3F) | 0x20);
                ((S_8017087C_3 *)part_b)->unk_2C = D_80175894;
                goto post_kind;
            }
        }
        goto init_parts;

post_kind:
init_parts:
        func_800A9C18(obj, part_a, part_b, kind_flags);

        child_index = 0;
        entry_id_fixed = 0x00190000;
        slot = (u8 *)slot_base;
        ((S_8017087C_4 *)slot)->unk_9A = 0xFF;
        slot_base->unk_9C = -1;
        slot_base->unk_8C = func_8017140C;
        ((S_8017087C_1 *)work)->unk_1C |= 0x40000;
        slot_base->unk_92 = -24;
        slot_base->unk_9E = 3;
        do {
            void *child_obj;

            child_obj = func_8003FD64(274, D_80083498);
            ((S_8017087C_4 *)slot)->unk_A4 = child_obj;
            if (child_obj != 0) {
                void *child_work = (u8 *)child_obj + 0x20;

                if (child_index != 0) {
                    ((S_8017087C_6 *)child_work)->unk_02 = 1;
                } else {
                    ((S_8017087C_6 *)child_work)->unk_02 = 2;
                }
                entry_index = 0;
                if (((S_8017087C_6 *)child_work)->unk_02 > 0) {
                    register s32 entry_offset ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    s32 child_id_fixed;

                    child_slot = slot;
                    child_id_fixed = entry_id_fixed;
                    entry_offset = 8;
                    do {
                        u8 *entry = (u8 *)child_work + entry_offset;
                        S_8017087C_9 *callback_obj;
                        register u32 color ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

                        color = 0x00C0C0C0;
                        alloc_or_entry = entry;
                        setup_value = ((S_8017087C_3 *)part_b)->unk_28;
                        entry_id = child_id_fixed >> 16;
                        ((S_8017087C_7 *)entry)->unk_0C = color;
                        ((S_8017087C_7 *)entry)->unk_28 = setup_value;
                        entry_mode = 0;
                        callback_obj = child_slot->unk_A4;
                        ASM_USE(entry_mode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        entry_offset += 48;
                        callback_obj->unk_10 = func_800D78C0;
                        setup_value = ((S_8017087C_7 *)entry)->unk_14;
                        entry_index++;
                        setup_value |= 0xC;
                        ((S_8017087C_7 *)entry)->unk_14 = setup_value;
                        func_80047784(alloc_or_entry, entry_id, entry_mode);
                        ((S_8017087C_7 *)entry)->unk_10 = 96;
                        ((S_8017087C_7 *)entry)->unk_12 = ((S_8017087C_3 *)part_b)->unk_12 - 128;
                        ((S_8017087C_6 *)child_work)->unk_06 = child_index + 1;
                        func_800478E8(part_b, D_800D71A8, ((S_8017087C_6 *)child_work)->unk_06);
                        ((S_8017087C_6 *)child_work)->unk_98 = (u8 *)obj + 30;
                    } while (entry_index < ((S_8017087C_6 *)child_work)->unk_02);
                }
            }
            entry_id_fixed += 0x10000;
            slot += 4;
        } while (++child_index < slot_base->unk_9E);
        slot_base->unk_98 = slot_base->unk_98 | 0x2000;
        func_800AA36C(slot_base, part_a, part_b, work);
    }
    return work;
}
