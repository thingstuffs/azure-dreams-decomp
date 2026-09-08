#include "common.h"


typedef s32 M2C_UNK;

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
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8017087C_3;   /* part_b in func_8017087C */

typedef struct S_8017087C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8017087C_4;   /* actor in func_8017087C */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_80170A50[];
extern M2C_UNK D_80170E7C;
extern u8 D_80174C3C[];
extern u8 D_80174C8C[];

/* Creates an actor and initializes its parts, position, and flags. */
void *func_8017087C(s16 kind_flags, s8 tile_x, s8 tile_y, s16 part_id)
{
    s32 kind;
    void *obj;
    S_8017087C_2 *part_a;
    S_8017087C_3 *part_b;
    S_8017087C_1 *work;
    S_8017087C_4 *actor;
    s32 flags_or_roll;
    s32 secondary_flags;
    register s8 saved_tile_x ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 saved_part_id;
    register s8 saved_tile_y ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *object_arg;
    register void *part_arg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    /* fidelity ratchet PASSTHRU_NO_ARGS fix (decomp_issues.md 20-22): retail's
     * `jal 0x800A6D30` at 0x8017098C forwards whatever $a2/$a3 hold -- this row
     * never writes them, so m2c had no name to forward.  These pins ARE that
     * name (section 22); they emit no code because the values are already in
     * their registers.  `need` is a positional SET, so the call carries 0..3
     * (section 21). */
    register M2C_UNK passthru_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register M2C_UNK passthru_a3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    work = 0;
    saved_tile_x = tile_x;
    saved_part_id = part_id;
    saved_tile_y = tile_y;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8017087C_0 *)obj)->unk_10 = D_80170A50;
        work->unk_13 = 0x8;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_8017087C_0 *)obj)->unk_08;
        part_a->unk_0A = saved_part_id;
        part_b = ((S_8017087C_0 *)obj)->unk_0C;
        kind = kind_flags & 3;
        part_b->unk_25 = saved_tile_y;
        actor = work;
        part_b->unk_2C = D_80174C3C;
        part_b->unk_24 = saved_tile_x;

        if (kind == 1) {
            flags_or_roll = work->unk_14 | 0x6000;
            secondary_flags = work->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        flags_or_roll = work->unk_14 | 0x2000;
        secondary_flags = work->unk_1C | 0x2000;
write_kind:
        work->unk_14 = flags_or_roll;
        work->unk_1C = secondary_flags;
        goto post_kind;

normal_kind:
        object_arg = obj;
        if (((kind_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                part_arg = part_a;
                ASM_KEEP(object_arg);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                flags_or_roll = func_800A6D30(object_arg, part_arg, passthru_a2, passthru_a3);
                object_arg = obj;
                if (!(flags_or_roll & 1)) {
                    goto init_actor;
                }
                work->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_80174C8C;
                goto post_kind;
            }
        }
        goto init_actor;

post_kind:
        object_arg = obj;
init_actor:
        func_800A9C18(object_arg, part_a, part_b, kind_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80170E7C;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
