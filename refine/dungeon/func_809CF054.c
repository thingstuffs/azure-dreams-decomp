#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_8016A854_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8016A854_0;   /* obj in func_8016A854 */

typedef struct S_8016A854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8016A854_1;   /* work in func_8016A854 */

typedef struct S_8016A854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016A854_2;   /* part_a in func_8016A854 */

typedef struct S_8016A854_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8016A854_3;   /* part_b in func_8016A854 */

typedef struct S_8016A854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8016A854_4;   /* actor in func_8016A854 */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8016AA28[];
extern M2C_UNK D_8016AE54;
extern u8 D_8016DC7C[];
extern u8 D_8016DCDC[];

/* Allocates an actor object and initializes its parts and flags for the requested kind. */
void *func_8016A854(s16 kind_flags, s8 byte_24, s8 byte_25, s16 value_0a)
{
    s32 kind;
    void *obj;
    S_8016A854_2 *part_a;
    S_8016A854_3 *part_b;
    S_8016A854_1 *work;
    S_8016A854_4 *actor;
    s32 primary_bits;
    s32 secondary_flags;
    register s8 saved_byte_24 ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s16 saved_value_0a;
    register s8 saved_byte_25 ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *call_obj;
    register void *call_part ASM_REG("$5");   /* MATCH pin: retail delay-slot contents depend on it */
    /* fidelity ratchet PASSTHRU_NO_ARGS fix (decomp_issues.md 20-22): retail's
     * `jal 0x800A6D30` forwards whatever $a2/$a3 hold -- this row never writes
     * them, so m2c had no name to forward.  These pins ARE that name
     * (section 22); they emit no code because the values are already in their
     * registers.  `need` is a positional SET, so the call carries 0..3
     * (section 21). */
    register M2C_UNK forwarded_a2 ASM_REG("$6");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register M2C_UNK forwarded_a3 ASM_REG("$7");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

    work = 0;
    saved_byte_24 = byte_24;
    saved_value_0a = value_0a;
    saved_byte_25 = byte_25;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8016A854_0 *)obj)->unk_10 = D_8016AA28;
        work->unk_13 = 0x3;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_8016A854_0 *)obj)->unk_08;
        part_a->unk_0A = saved_value_0a;
        part_b = ((S_8016A854_0 *)obj)->unk_0C;
        kind = kind_flags & 3;
        part_b->unk_25 = saved_byte_25;
        actor = work;
        part_b->unk_2C = D_8016DC7C;
        part_b->unk_24 = saved_byte_24;

        if (kind == 1) {
            primary_bits = work->unk_14 | 0x6000;
            secondary_flags = work->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        primary_bits = work->unk_14 | 0x2000;
        secondary_flags = work->unk_1C | 0x2000;
write_kind:
        work->unk_14 = primary_bits;
        work->unk_1C = secondary_flags;
        goto post_kind;

normal_kind:
        call_obj = obj;
        if (((kind_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                call_part = part_a;
                ASM_KEEP(call_obj);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                primary_bits = func_800A6D30(call_obj, call_part, forwarded_a2, forwarded_a3);
                call_obj = obj;
                if (!(primary_bits & 1)) {
                    goto init_actor;
                }
                work->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_8016DCDC;
                goto post_kind;
            }
        }
        goto init_actor;

post_kind:
        call_obj = obj;
init_actor:
        func_800A9C18(call_obj, part_a, part_b, kind_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8016AE54;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
