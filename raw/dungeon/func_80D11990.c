#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef s32 M2C_UNK;

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
extern u8 D_80171358[];
extern M2C_UNK D_80171760;
extern u8 D_80174E88[];
extern u8 D_80174EF0[];

void *func_80171190(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    register Work *work ASM_REG("$16");
    register void *obj ASM_REG("$17");
    void *part_a;
    void *part_b;
    void *resource;
    Work *actor;
    register s32 left ASM_REG("$2");
    register s32 right ASM_REG("$3");
    register s8 saved_arg1 ASM_REG("$22");
    register s16 saved_arg3 ASM_REG("$18");
    register s8 saved_arg2 ASM_REG("$21");
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");

    work = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (Work *)((u8 *)obj + 0x20);
        FIELD(obj, void *, 0x10) = D_80171358;
        work->byte13 = 0x17;
        func_8004491C(obj, &D_80045340);

        resource = D_80174E88;
        part_a = FIELD(obj, void *, 8);
        FIELD(part_a, s16, 0xA) = saved_arg3;
        part_b = FIELD(obj, void *, 0xC);
        kind = arg0 & 3;
        FIELD(part_b, s8, 0x25) = saved_arg2;
        actor = work;
        FIELD(part_b, void *, 0x2C) = resource;
        FIELD(part_b, s8, 0x24) = saved_arg1;

        if (kind == 1) {
            left = work->flags14 | 0x6000;
            right = work->flags1c | 0x6000;
            goto write_kind;
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
        call_a0 = obj;
        if (((arg0 & ~3) << 16) == 0) {
            if (!(work->flags14 & 0x200)) {
                call_a1 = part_a;
                ASM_KEEP(call_a0);
                ASM_KEEP(call_a1);
                left = func_800A6D30();
                call_a0 = obj;
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                FIELD(part_b, void *, 0x2C) = D_80174EF0;
                goto post_kind;
            }
        }
        goto call_a1_setup;

post_kind:
        call_a0 = obj;
call_a1_setup:
        func_800A9C18(call_a0, part_a, part_b, arg0);
        actor->byte9a = 0xFF;
        actor->byte9c = -1;
        actor->ptr8c = &D_80171760;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
