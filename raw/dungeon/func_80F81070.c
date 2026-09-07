#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef s32 M2C_UNK;

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
    register void *work ASM_REG("$16");
    register void *obj ASM_REG("$17");
    register void *part_a ASM_REG("$20");
    register void *part_b ASM_REG("$18");
    register void *actor ASM_REG("$21");
    register void *call_a0 ASM_REG("$4");
    register s8 saved_arg1 ASM_REG("$22");
    s16 saved_arg3;
    s8 saved_arg2;
    register s32 left ASM_REG("$2");
    register s32 right ASM_REG("$3");

    work = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    ASM_KEEP_NV(saved_arg2);
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (void *)((Work *)((u8 *)obj + 0x20));
        FIELD(obj, void *, 0x10) = D_8014CA3C;
        FIELD(work, s8, 0x13) = 0x25;
        func_8004491C(obj, &D_80045340);

        part_a = FIELD(obj, void *, 8);
        FIELD(part_a, s16, 0xA) = saved_arg3;
        part_b = FIELD(obj, void *, 0xC);
        kind = arg0 & 3;
        FIELD(part_b, s8, 0x25) = saved_arg2;
        actor = work;
        FIELD(part_b, void *, 0x2C) = D_80150194;
        FIELD(part_b, s8, 0x24) = saved_arg1;

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
            FIELD(part_b, void *, 0x2C) = D_801501DC;
        }

post_kind:
        call_a0 = obj;
join_kind:
        func_800A9C18(call_a0, part_a, part_b, arg0);
        FIELD(actor, u8, 0x9A) = 0xFF;
        FIELD(actor, s8, 0x9C) = -1;
        FIELD(actor, void *, 0x8C) = &D_8014CE68;
        FIELD(part_b, u16, 0x14) |= 0xC;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
