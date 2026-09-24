#include "common.h"

typedef struct S_80171158_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80171158_0;   /* object in func_80171158 */

typedef struct S_80171158_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80171158_1;   /* result in func_80171158 */

typedef struct S_80171158_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80171158_2;   /* part0 in func_80171158 */

typedef struct S_80171158_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80171158_3;   /* part1 in func_80171158 */

typedef struct S_80171158_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80171158_4;   /* result_copy in func_80171158 */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80045340;
extern s32 D_80083498;
extern u8 D_80171320[];
extern s32 D_80171728;
extern u8 D_80174DEC[];
extern u8 D_80174E4C[];

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *func_80171158(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c)
{
    s32 kind;
    s32 flags0;
    s32 flags1;
    S_80171158_1 *result;
    void *object;
    S_80171158_2 *part0;
    S_80171158_3 *part1;
    S_80171158_4 *result_copy;

    result = 0;
    object = func_8003FD64(0x112, &D_80083498);
    if (object == 0) {
        goto done;
    }

    result = object;
    result = (u8 *)result + 0x20;
    ((S_80171158_0 *)object)->unk_10 = D_80171320;
    result->unk_13 = 9;
    func_8004491C(object, &D_80045340);

    {
        void *handler;

        part0 = ((S_80171158_0 *)object)->unk_08;
        handler = D_80174DEC;
        part0->unk_0A = attr_c;
        part1 = ((S_80171158_0 *)object)->unk_0C;
        kind = spawn_flags & 3;
        part1->unk_25 = attr_b;
        result_copy = result;
        part1->unk_2C = handler;
    }
    part1->unk_24 = attr_a;

    if (kind == 1) {
        flags0 = result->unk_14;
        flags1 = result->unk_1C;
        flags0 |= 0x6000;
        flags1 |= 0x6000;
        result->unk_14 = flags0;
        result->unk_1C = flags1;
        goto common;
    }

    if (kind >= 2) {
        flags0 = result->unk_14;
        flags1 = result->unk_1C;
        flags0 |= 0x2000;
        flags1 |= 0x2000;
        result->unk_14 = flags0;
        result->unk_1C = flags1;
        goto common;
    }

    if (((spawn_flags & -4) << 16) != 0) {
        goto common;
    }
    if ((result->unk_14 & 0x200) != 0) {
        goto common;
    }
    if ((func_800A6D30() & 1) != 0) {
        func_800A48F0(result, 1, (func_800A6D30() & 0x3F) | 0x20);
        part1->unk_2C = D_80174E4C;
    }

common:
    func_800A9C18(object, part0, part1, spawn_flags);
    result_copy->unk_9A = 0xFF;
    result_copy->unk_9C = -1;
    result_copy->unk_8C = &D_80171728;
    func_800AA36C(result_copy, part0, part1, result);

done:
    return result;
}

/* MECHANISM: 2.7.2-cdk-G0 (retail shows the compiler's HIGH/LO_SUM address split: lui / lw / addiu).
   The two byte parameters arrive as s16: their narrowing copies survive cse, combine folds the a1/a2
   temps into them, so sched1 schedules the parameter copies and the entry order is retail's. */
