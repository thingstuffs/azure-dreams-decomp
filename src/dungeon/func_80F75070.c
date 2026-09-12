#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_80158870_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80158870_0;   /* obj in func_80158870 */

typedef struct S_80158870_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80158870_1;   /* work in func_80158870 */

typedef struct S_80158870_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80158870_2;   /* part_a in func_80158870 */

typedef struct S_80158870_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80158870_3;   /* part_b in func_80158870 */

typedef struct S_80158870_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80158870_4;   /* actor in func_80158870 */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_80158A3C[];
extern M2C_UNK D_80158E68;
extern u8 D_8015C194[];
extern u8 D_8015C1DC[];

/* Allocate an actor and initialize its parts and behavior from the kind flags. */
void *func_80158870(s16 kind_flags, s16 part_value_24, s16 part_value_25, s16 part_value_0a)
{
    s32 kind;
    void *obj;
    S_80158870_2 *part_a;
    S_80158870_3 *part_b;
    S_80158870_1 *work;
    S_80158870_4 *actor;
    register s32 flags_14;
    register s32 flags_1c;
    register s8 saved_value_24;
    register s16 saved_value_0a;
    register s8 saved_value_25;
    register void *init_obj;
    register void *query_part;

    work = 0;
    saved_value_24 = part_value_24;
    saved_value_0a = part_value_0a;
    saved_value_25 = part_value_25;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80158870_0 *)obj)->unk_10 = D_80158A3C;
        work->unk_13 = 0x25;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_80158870_0 *)obj)->unk_08;
        part_a->unk_0A = saved_value_0a;
        part_b = ((S_80158870_0 *)obj)->unk_0C;
        kind = kind_flags & 3;
        part_b->unk_25 = saved_value_25;
        actor = work;
        part_b->unk_2C = D_8015C194;
        part_b->unk_24 = saved_value_24;

        if (kind == 1) {
            flags_14 = work->unk_14 | 0x6000;
            flags_1c = work->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        flags_14 = work->unk_14 | 0x2000;
        flags_1c = work->unk_1C | 0x2000;
write_kind:
        work->unk_14 = flags_14;
        work->unk_1C = flags_1c;
        goto post_kind;

normal_kind:
        init_obj = obj;
        if (((kind_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                query_part = part_a;
                work->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(init_obj, query_part) & 0x3F) | 0x20);
                part_b->unk_2C = D_8015C1DC;
                goto post_kind;
            }
        }
        goto init_actor;

post_kind:
        init_obj = obj;
init_actor:
        func_800A9C18(init_obj, part_a, part_b, kind_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80158E68;
        part_b->unk_14 |= 0xC;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
