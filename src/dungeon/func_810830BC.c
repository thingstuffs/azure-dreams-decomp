#include "common.h"

typedef struct S_801708BC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_801708BC_0;   /* object in func_801708BC */

typedef struct S_801708BC_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_801708BC_1;   /* result in func_801708BC */

typedef struct S_801708BC_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_801708BC_2;   /* part0 in func_801708BC */

typedef struct S_801708BC_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_801708BC_3;   /* part1 in func_801708BC */

typedef struct S_801708BC_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_801708BC_4;   /* result_copy in func_801708BC */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80045340;
extern s32 D_80083498;
extern u8 D_80170A84[];
extern s32 D_80170E94;
extern u8 D_80175F10[];
extern u8 D_80175F28[];

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *func_801708BC(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c)
{
    void *result = 0;
    S_801708BC_0 *object;
    void *part0;
    S_801708BC_3 *part1;
    S_801708BC_4 *result_copy;
    s16 held_a;
    s32 held_c;
    s16 held_b;
    s16 flags_copy;
    s32 kind;

    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    object = func_8003FD64(0x112, &D_80083498);
    flags_copy = spawn_flags;
    if (object == 0) {
        goto done;
    }

    result = (u8 *)object + 0x20;
    object->unk_10 = D_80170A84;
    ((S_801708BC_1 *)result)->unk_13 = 44;
    func_8004491C(object, &D_80045340);

    part0 = object->unk_08;
    ((S_801708BC_2 *)part0)->unk_0A = held_c;
    part1 = object->unk_0C;
    kind = spawn_flags & 3;
    part1->unk_25 = held_b;
    result_copy = result;
    part1->unk_2C = D_80175F10;
    part1->unk_24 = held_a;

    if (kind == 1) {
        ((S_801708BC_1 *)result)->unk_14 |= 0x6000;
        ((S_801708BC_1 *)result)->unk_1C |= 0x6000;
        goto common;
    }
    if (kind >= 2) {
        ((S_801708BC_1 *)result)->unk_14 |= 0x2000;
        ((S_801708BC_1 *)result)->unk_1C |= 0x2000;
        goto common;
    }

    if (((spawn_flags & -4) << 16) != 0) {
        goto common;
    }
    if ((((S_801708BC_1 *)result)->unk_14 & 0x200) != 0) {
        goto common;
    }
    if ((func_800A6D30() & 1) != 0) {
        func_800A48F0(result, 1, (func_800A6D30() & 0x3F) | 0x20);
        part1->unk_2C = D_80175F28;
    }

common:
    func_800A9C18(object, part0, part1, (s16)flags_copy);
    result_copy->unk_9A = 0xFF;
    result_copy->unk_9C = -1;
    result_copy->unk_8C = &D_80170E94;
    func_800AA36C(result_copy, part0, part1, result);

done:
    return result;
}
