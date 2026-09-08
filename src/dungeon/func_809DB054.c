#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_8015E854_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8015E854_0;   /* obj in func_8015E854 */

typedef struct S_8015E854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8015E854_1;   /* work in func_8015E854 */

typedef struct S_8015E854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8015E854_2;   /* part_a in func_8015E854 */

typedef struct S_8015E854_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8015E854_3;   /* part_b in func_8015E854 */

typedef struct S_8015E854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8015E854_4;   /* actor in func_8015E854 */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8015EA28[];
extern M2C_UNK D_8015EE54;
extern u8 D_80161C7C[];
extern u8 D_80161CDC[];

/* Creates an actor, configures its parts and flags, and returns its work data. */
void *func_8015E854(s16 flags, s8 x, s8 y, s16 part_id)
{
    s32 kind;
    void *obj;
    S_8015E854_2 *part_a;
    S_8015E854_3 *part_b;
    S_8015E854_1 *work;
    S_8015E854_4 *actor;
    s32 flag_bits;
    s32 secondary_flags;
    register s8 saved_x ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 saved_part_id;
    register s8 saved_y ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *init_obj;
    register void *query_part ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    /* fidelity ratchet PASSTHRU_NO_ARGS fix (decomp_issues.md 20-22): retail's
     * `jal 0x800A6D30` forwards whatever $a2/$a3 hold -- this row never writes
     * them, so m2c had no name to forward.  These pins ARE that name
     * (section 22); they emit no code because the values are already in their
     * registers.  `need` is a positional SET, so the call carries 0..3
     * (section 21). */
    register M2C_UNK passthru_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register M2C_UNK passthru_a3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    work = 0;
    saved_x = x;
    saved_part_id = part_id;
    saved_y = y;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8015E854_0 *)obj)->unk_10 = D_8015EA28;
        work->unk_13 = 0x3;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_8015E854_0 *)obj)->unk_08;
        part_a->unk_0A = saved_part_id;
        part_b = ((S_8015E854_0 *)obj)->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = saved_y;
        actor = work;
        part_b->unk_2C = D_80161C7C;
        part_b->unk_24 = saved_x;

        if (kind == 1) {
            flag_bits = work->unk_14 | 0x6000;
            secondary_flags = work->unk_1C | 0x6000;
            goto apply_kind_flags;
        }
        if (kind < 2) {
            goto default_kind;
        }

        flag_bits = work->unk_14 | 0x2000;
        secondary_flags = work->unk_1C | 0x2000;
apply_kind_flags:
        work->unk_14 = flag_bits;
        work->unk_1C = secondary_flags;
        goto kind_ready;

default_kind:
        init_obj = obj;
        if (((flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                query_part = part_a;
                ASM_KEEP(init_obj);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                flag_bits = func_800A6D30(init_obj, query_part, passthru_a2, passthru_a3);
                init_obj = obj;
                if (!(flag_bits & 1)) {
                    goto init_parts;
                }
                work->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_80161CDC;
                goto kind_ready;
            }
        }
        goto init_parts;

kind_ready:
        init_obj = obj;
init_parts:
        func_800A9C18(init_obj, part_a, part_b, flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8015EE54;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}

/* MECHANISM: Preserve the seed's exact 0x38 frame, s0-s7 holds, CFG, and true-base name.
   The sole residue was part_b's saved_x byte field at 0x20 versus retail offset 0x24.
   part_b->unk_24 closes the substitution at emitted word 32. */
