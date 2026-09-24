#include "common.h"

typedef struct S_80171080_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80171080_0;   /* object in func_80171080 */

typedef struct S_80171080_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80171080_1;   /* result in func_80171080 */

typedef struct S_80171080_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80171080_2;   /* part0 in func_80171080 */

typedef struct S_80171080_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80171080_3;   /* part1 in func_80171080 */

typedef struct S_80171080_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80171080_4;   /* result_copy in func_80171080 */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80045340;
extern s32 D_80083498;
extern u8 D_80171248[];
extern s32 D_80171650;
extern u8 D_801742C8[];
extern u8 D_80174310[];

/* Spawn the overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
void *func_80171080(s16 flags, s16 kind_id, s16 variant, s32 spawn_value)
{
    s32 kind;
    s32 flags0;
    s32 flags1;
    void *result;
    void *object;
    S_80171080_2 *part0;
    S_80171080_3 *part1;
    S_80171080_4 *result_copy;

    result = 0;
    object = func_8003FD64(0x112, &D_80083498);
    if (object == 0) {
        goto done;
    }

    result = (u8 *)object;
    result += 0x20;
    ((S_80171080_0 *)object)->unk_10 = D_80171248;
    ((S_80171080_1 *)result)->unk_13 = 19;
    func_8004491C(object, &D_80045340);

    {
        void *handler;

        part0 = ((S_80171080_0 *)object)->unk_08;
        handler = D_801742C8;
        part0->unk_0A = spawn_value;
        part1 = ((S_80171080_0 *)object)->unk_0C;
        kind = flags & 3;
        part1->unk_25 = variant;
        result_copy = result;
        part1->unk_2C = handler;
    }
    part1->unk_24 = kind_id;

    if (kind == 1) {
        flags0 = ((S_80171080_1 *)result)->unk_14;
        flags1 = ((S_80171080_1 *)result)->unk_1C;
        flags0 |= 0x6000;
        flags1 |= 0x6000;
        ((S_80171080_1 *)result)->unk_14 = flags0;
        ((S_80171080_1 *)result)->unk_1C = flags1;
        goto common;
    }

    if (kind >= 2) {
        flags0 = ((S_80171080_1 *)result)->unk_14;
        flags1 = ((S_80171080_1 *)result)->unk_1C;
        flags0 |= 0x2000;
        flags1 |= 0x2000;
        ((S_80171080_1 *)result)->unk_14 = flags0;
        ((S_80171080_1 *)result)->unk_1C = flags1;
        goto common;
    }

    if (((flags & -4) << 16) != 0) {
        goto common;
    }
    if ((((S_80171080_1 *)result)->unk_14 & 0x200) != 0) {
        goto common;
    }
    if ((func_800A6D30() & 1) != 0) {
        func_800A48F0(result, 1, (func_800A6D30() & 0x3F) | 0x20);
        part1->unk_2C = D_80174310;
    }

common:
    func_800A9C18(object, part0, part1, flags);
    result_copy->unk_9A = 0xFF;
    result_copy->unk_9C = -1;
    result_copy->unk_8C = &D_80171650;
    func_800AA36C(result_copy, part0, part1, result);

done:
    return result;
}

/* MECHANISM: 2.8.0-G0 (retail shows the compiler's HIGH/LO_SUM address split: lui / lw / addiu).
   The two byte parameters arrive as s16: their narrowing copies survive cse, combine folds the a1/a2
   temps into them, so sched1 schedules the parameter copies and the entry order is retail's. */
