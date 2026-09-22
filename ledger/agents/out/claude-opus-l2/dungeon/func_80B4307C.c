#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_8017087C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8017087C_0;   /* obj in func_8017087C */

typedef struct S_8017087C_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8017087C_1;   /* part_a in func_8017087C */

typedef struct S_8017087C_2 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8017087C_2;   /* part_b in func_8017087C */


typedef struct Work {
    u8 pad0[0x13];
    s8 byte13;
    s32 flags14;
    u8 pad18[4];
    s32 flags1c;
    u8 pad20[0x6C];
    void *ptr8c;
    u8 pad90[0xA];
    u8 byte9a;
    u8 pad9b;
    s8 byte9c;
} Work;

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_80170A44[];
extern M2C_UNK D_80170E70;
extern u8 D_80175A54[];
extern u8 D_80175A9C[];

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *func_8017087C(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    s32 kind;
    Work *work;
    void *obj;
    S_8017087C_1 *part_a;
    S_8017087C_2 *part_b;
    void *resource;
    Work *actor;
    s32 left;
    s32 right;
    s8 held_a;
    s16 held_c;
    s8 held_b;
    void *call_a1;

    work = 0;
    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (Work *)((u8 *)obj + 0x20);
        ((S_8017087C_0 *)obj)->unk_10 = D_80170A44;
        work->byte13 = 0xC;
        func_8004491C(obj, &D_80045340);

        resource = D_80175A54;
        part_a = ((S_8017087C_0 *)obj)->unk_08;
        part_a->unk_0A = held_c;
        part_b = ((S_8017087C_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = held_b;
        actor = work;
        part_b->unk_2C = resource;
        part_b->unk_24 = held_a;

        if (kind == 1) {
            left = work->flags14 | 0x6000;
            right = work->flags1c | 0x6000;
            work->flags14 = left;
            work->flags1c = right;
            goto post_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = work->flags14 | 0x2000;
        right = work->flags1c | 0x2000;
write_kind:
        work->flags14 = left;
        work->flags1c = right;
        goto post_kind;

    normal_kind:
        call_a1 = obj;
        if (((spawn_flags & ~3) << 16) == 0) {
            if (!(work->flags14 & 0x200)) {
                call_a1 = part_a;
                left = func_800A6D30();
                call_a1 = obj;
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_80175A9C;
                goto post_kind;
            }
        }
        goto call_a1_setup;

post_kind:
        call_a1 = obj;
call_a1_setup:
        func_800A9C18(call_a1, part_a, part_b, spawn_flags);
        actor->byte9a = 0xFF;
        actor->byte9c = -1;
        actor->ptr8c = &D_80170E70;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
