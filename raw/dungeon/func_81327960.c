#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef s32 M2C_UNK;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80045340;
extern s32 D_80083498;
extern u8 D_8016F2E0[];
extern M2C_UNK D_8016F78C;
extern u8 D_80174A2C[];
extern void *D_80174CD8;

void *func_8016F160(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    register void *obj ASM_REG("$16");
    void *part_a;
    void *part_b;
    register void *work ASM_REG("$17");
    register s16 mode_copy ASM_REG("$23");
    register s8 saved_arg1 ASM_REG("$22");
    register s16 saved_arg3 ASM_REG("$18");
    register s8 saved_arg2 ASM_REG("$21");
    void *actor;
    register void *tail_ptr ASM_REG("$4");

    work = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, &D_80083498);
    mode_copy = arg0;
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        D_80174CD8 = obj;
        FIELD(obj, void *, 0x10) = D_8016F2E0;
        FIELD(work, s8, 0x13) = 0x32;
        func_8004491C(obj, &D_80045340);

        part_a = FIELD(obj, void *, 8);
        FIELD(part_a, s16, 0xA) = saved_arg3;
        part_b = FIELD(obj, void *, 0xC);
        kind = arg0 & 3;
        FIELD(part_b, s8, 0x25) = saved_arg2;
        actor = work;
        FIELD(part_b, void *, 0x2C) = D_80174A2C;
        FIELD(part_b, s8, 0x24) = saved_arg1;

        if (kind == 1) {
            FIELD(work, s32, 0x14) |= 0x6000;
            FIELD(work, s32, 0x1C) |= 0x6000;
        } else if (kind >= 2) {
            FIELD(work, s32, 0x14) |= 0x2000;
            FIELD(work, s32, 0x1C) |= 0x2000;
        }

        func_800A9C18(obj, part_a, part_b, mode_copy);
        ASM_USE_NV(actor);
        tail_ptr = actor;
        ASM_KEEP_NV(tail_ptr);
        FIELD(tail_ptr, u8, 0x9A) = 0xFF;
        FIELD(tail_ptr, s8, 0x9C) = -1;
        FIELD(tail_ptr, void *, 0x8C) = &D_8016F78C;
        FIELD(tail_ptr, u8, 0x9B) = 0;
        FIELD(tail_ptr, s16, 0xB0) = 0;
        FIELD(part_b, u16, 0x14) |= 0x80;
        ASM_KEEP_NV(work);
        func_800AA36C(tail_ptr, part_a, part_b, work);
    }
    return work;
}
