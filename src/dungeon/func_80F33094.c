#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_80170894_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80170894_0;   /* obj in func_80170894 */

typedef struct S_80170894_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80170894_1;   /* work in func_80170894 */

typedef struct S_80170894_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170894_2;   /* part_a in func_80170894 */

typedef struct S_80170894_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80170894_3;   /* part_b in func_80170894 */

typedef struct S_80170894_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80170894_4;   /* actor in func_80170894 */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_80170A68[];
extern M2C_UNK D_80170E94;
extern u8 D_80174A7C[];
extern u8 D_80174AD4[];

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *func_80170894(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    s32 kind;
    void *obj;
    S_80170894_2 *part_a;
    S_80170894_3 *part_b;
    S_80170894_1 *work;
    S_80170894_4 *actor;
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
        work = (u8 *)obj + 0x20;
        ((S_80170894_0 *)obj)->unk_10 = D_80170A68;
        work->unk_13 = 0x24;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_80170894_0 *)obj)->unk_08;
        part_a->unk_0A = held_c;
        part_b = ((S_80170894_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = held_b;
        actor = work;
        part_b->unk_2C = D_80174A7C;
        part_b->unk_24 = held_a;

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
        if (((spawn_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                call_a1 = part_a;
                left = func_800A6D30();
                call_a1 = obj;
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                work->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_80174AD4;
                goto post_kind;
            }
        }
        goto call_a1_setup;

post_kind:
        call_a1 = obj;
call_a1_setup:
        func_800A9C18(call_a1, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80170E94;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
