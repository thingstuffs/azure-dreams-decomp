#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_8014C870_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8014C870_0;   /* obj in func_8014C870 */

typedef struct S_8014C870_1 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_8014C870_1;   /* work in func_8014C870 */

typedef struct S_8014C870_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8014C870_2;   /* part_a in func_8014C870 */

typedef struct S_8014C870_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8014C870_3;   /* part_b in func_8014C870 */

typedef struct S_8014C870_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8014C870_4;   /* actor in func_8014C870 */


typedef struct Work {
    u8 pad14[0x14];
    s32 flags14;
    u8 pad18[4];
    s32 flags1c;
} Work;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30(void *);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8014CA3C[];
extern u8 D_8014CE68;
extern u8 D_80150194[];
extern u8 D_801501DC[];

void *func_8014C870(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    S_8014C870_1 *work;
    void *obj;
    S_8014C870_2 *part_a;
    S_8014C870_3 *part_b;
    S_8014C870_4 *actor;
    void *call_a0;
    register s8 saved_arg1 ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s16 saved_arg3;
    s8 saved_arg2;
    s32 left;
    s32 right;

    work = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    ASM_KEEP_NV(saved_arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (void *)((Work *)((u8 *)obj + 0x20));
        ((S_8014C870_0 *)obj)->unk_10 = D_8014CA3C;
        work->unk_13 = 0x25;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_8014C870_0 *)obj)->unk_08;
        part_a->unk_0A = saved_arg3;
        part_b = ((S_8014C870_0 *)obj)->unk_0C;
        kind = arg0 & 3;
        part_b->unk_25 = saved_arg2;
        actor = work;
        part_b->unk_2C = D_80150194;
        part_b->unk_24 = saved_arg1;

        if (kind == 1) {
            left = ((Work *)work)->flags14 | 0x6000;
            right = ((Work *)work)->flags1c | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = ((Work *)work)->flags14 | 0x2000;
        right = ((Work *)work)->flags1c | 0x2000;
write_kind:
        ((Work *)work)->flags14 = left;
        ((Work *)work)->flags1c = right;
        goto post_kind;

normal_kind:
        call_a0 = obj;
        if (((arg0 & ~3) << 16) != 0) {
            goto join_kind;
        }
        if (!(((Work *)work)->flags14 & 0x200)) {
            ((Work *)work)->flags1c |= 0x200;
            func_800A48F0(work, 1,
                          (func_800A6D30(call_a0) & 0x3F) | 0x20);
            part_b->unk_2C = D_801501DC;
        }

post_kind:
        call_a0 = obj;
join_kind:
        func_800A9C18(call_a0, part_a, part_b, arg0);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8014CE68;
        part_b->unk_14 |= 0xC;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
