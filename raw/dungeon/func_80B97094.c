#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FD64(s32, const void *);
extern void func_8004491C(void *, const void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern void func_80170A98(void);
extern void func_80170E9C(void);
extern void func_80174ED8(void);
extern void func_80174F00(void);

extern s32 D_80045340;
extern u8 D_80083498[];

void *func_80170894(s32 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    register void *work ASM_REG("$16");
    register s16 saved_arg3 ASM_REG("$17");
    register s32 saved_arg0 ASM_REG("$18");
    register void *obj ASM_REG("$19");
    register s8 saved_arg2 ASM_REG("$20");
    register s8 saved_arg1 ASM_REG("$21");
    register void *part_a ASM_REG("$22");
    register s16 original_arg0 ASM_REG("$23");
    register s32 call_id ASM_REG("$4");
    register const void *call_target ASM_REG("$5");

    saved_arg0 = arg0;
    ASM_KEEP_NV(saved_arg0);
    work = 0;
    call_id = 0x112;
    saved_arg1 = arg1;
    call_target = D_80083498;
    ASM_USE2_NV(call_id, call_target);
    saved_arg3 = arg3;
    ASM_KEEP_NV(saved_arg3);
    saved_arg2 = arg2;
    obj = func_8003FD64(call_id, call_target);
    original_arg0 = saved_arg0;
    if (obj != 0) {
        register void *part_b;
        register void *actor ASM_REG("$20");

        work = (u8 *)obj + 0x20;
        ASM_KEEP_NV(work);
        FIELD(work, s8, 0x13) = 0xE;
        func_8004491C(obj, &D_80045340);

        part_a = FIELD(obj, void *, 8);
        FIELD(part_a, s16, 0xA) = saved_arg3;
        part_b = FIELD(obj, void *, 0xC);
        kind = saved_arg0 & 3;
        FIELD(part_b, s8, 0x25) = saved_arg2;
        actor = work;
        ASM_KEEP_NV(actor);
        FIELD(part_b, s8, 0x24) = saved_arg1;

        if (kind == 1) {
            s32 left_one;
            s32 right_one;

            FIELD(work, void *, 0x8C) = func_80170E9C;
            left_one = FIELD(work, s32, 0x14) | 0x6000;
            right_one = FIELD(work, s32, 0x1C) | 0x6000;
            FIELD(work, s32, 0x14) = left_one;
            FIELD(work, s32, 0x1C) = right_one;
            FIELD(part_b, void *, 0x2C) = func_80174ED8;
            goto callback_done;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        {
            s32 left_many;
            s32 right_many;

            FIELD(work, void *, 0x8C) = func_80170E9C;
            left_many = FIELD(work, s32, 0x14) | 0x2000;
            right_many = FIELD(work, s32, 0x1C) | 0x2000;
            FIELD(work, s32, 0x14) = left_many;
            FIELD(work, s32, 0x1C) = right_many;
        }
        FIELD(part_b, void *, 0x2C) = func_80174ED8;
        goto callback_done;

normal_kind:
        {
            register s32 test ASM_REG("$2");
            register u8 *callback_page ASM_REG("$2");

            test = saved_arg0 & ~3;
            ASM_KEEP_NV(test);
            test <<= 16;
            if (test != 0) {
                callback_page = (u8 *)0x80170000;
                goto work_callback;
            }
            if (FIELD(work, s32, 0x14) & 0x200) {
                callback_page = (u8 *)0x80170000;
                goto actor_callback;
            }
            if (!(func_800A6D30() & 1)) {
                callback_page = (u8 *)0x80170000;
                goto actor_callback;
            }
            func_800A48F0(work, 1,
                          (func_800A6D30() & 0x3F) | 0x20);
            FIELD(part_b, void *, 0x2C) = func_80174F00;
            callback_page = (u8 *)0x80170000;

actor_callback:
            FIELD(actor, void *, 0x8C) = callback_page + 0xE9C;
            FIELD(part_b, void *, 0x2C) = func_80174ED8;
            goto callback_done;
work_callback:
            FIELD(work, void *, 0x8C) = callback_page + 0xE9C;
            FIELD(part_b, void *, 0x2C) = func_80174ED8;
        }
callback_done:
        FIELD(obj, void *, 0x10) = func_80170A98;
        func_800A9C18(obj, part_a, part_b, original_arg0);
        FIELD(actor, u8, 0x9A) = 0xFF;
        FIELD(actor, s8, 0x9C) = -1;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
