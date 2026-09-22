#include "common.h"

typedef struct S_80171780_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80171780_0;   /* obj in func_80171780 */

typedef struct S_80171780_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x7E];
    s16 unk_9E;
} S_80171780_1;   /* work in func_80171780 */

typedef struct S_80171780_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80171780_2;   /* part_a in func_80171780 */

typedef struct S_80171780_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80171780_3;   /* part_b in func_80171780 */

typedef struct S_80171780_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80171780_4;   /* actor in func_80171780 */



extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern u8 D_80045340;
extern s32 D_80083498;
extern u8 D_800E2348[];
extern u8 D_800E23A8[];
extern u8 D_80171964[];
extern s32 D_80171F1C;

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
void *func_80171780(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    void *obj;
    S_80171780_2 *part_a;
    S_80171780_3 *part_b;
    S_80171780_1 *work;
    S_80171780_4 *actor;
    s32 left;
    s32 right;
    s8 saved_kind_id;
    s16 saved_spawn;
    s8 saved_variant;
    void *call_a1;

    work = 0;
    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    obj = func_8003FD64(0x112, &D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80171780_0 *)obj)->unk_10 = D_80171964;
        work->unk_13 = 0x19;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_80171780_0 *)obj)->unk_08;
        part_a->unk_0A = saved_spawn;
        part_b = ((S_80171780_0 *)obj)->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = saved_variant;
        actor = work;
        part_b->unk_2C = D_800E2348;
        part_b->unk_24 = saved_kind_id;
        work->unk_9E = 0;

        if (kind == 1) {
            left = work->unk_14 | 0x6000;
            right = work->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = work->unk_14 | 0x2000;
        right = work->unk_1C | 0x2000;
write_kind:
        work->unk_14 = left;
        work->unk_1C = right;
        goto post_kind;

normal_kind:
        call_a1 = obj;
        if (((flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                call_a1 = part_a;
                left = func_800A6D30();
                call_a1 = obj;
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_800E23A8;
                goto post_kind;
            }
        }
        goto call_a1_setup;

post_kind:
        call_a1 = obj;
call_a1_setup:
        func_800A9C18(call_a1, part_a, part_b, flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80171F1C;
        work->unk_1C |= 0x40000;
        actor->unk_92 = -0x20;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
/* MECHANISM: A matched sibling supplied the shared RMW/write and call-merge CFG.
   Narrow args stay in s6/s2/s5; guarded v0/v1 and a0/a1 pins preserve ABI lifetimes.
   Pointer locals naturally produce the 0x38 frame, held bases, joins, and delay slots. */
