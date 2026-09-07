#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef s32 M2C_UNK;

extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_80158A58[];
extern u8 D_80158E5C[];
extern u8 D_8015C510[];
extern u8 D_8015C538[];

extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern s32 func_800A6D30();
extern M2C_UNK func_800A48F0();
extern M2C_UNK func_800A9C18();
extern M2C_UNK func_800AA36C();

#ifdef NON_MATCHING
#define CALLBACK_PAGE ((u32)(D_80158E5C + 0x71A4))
#else
#define CALLBACK_PAGE 0x80160000U
#endif

void *func_80158854(s32 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    register s32 left ASM_REG("$2");
    register s32 right ASM_REG("$3");
    register void *work ASM_REG("$16");
    register s16 saved_arg3 ASM_REG("$17");
    register void *obj ASM_REG("$19");
    register s8 saved_arg2;
    register s8 saved_arg1 ASM_REG("$21");
    register void *part_a ASM_REG("$22");
    register s32 final_arg0 ASM_REG("$23");
    void *part_b;
    register void *actor ASM_REG("$20");
    register u32 callback_page ASM_REG("$2");

    work = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    ASM_KEEP_DEP_NV(saved_arg2, saved_arg3);
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        final_arg0 = arg0;
        ASM_KEEP(final_arg0);
        work = (u8 *)obj + 0x20;
        ASM_KEEP(work);
        FIELD(work, s8, 0x13) = 0x1C;
        func_8004491C(obj, D_80045340);

        part_a = FIELD(obj, void *, 8);
        FIELD(part_a, s16, 0xA) = saved_arg3;
        part_b = FIELD(obj, void *, 0xC);
        FIELD(part_b, s8, 0x25) = saved_arg2;
        actor = work;
        kind = arg0 & 3;
        FIELD(part_b, s8, 0x24) = saved_arg1;

        if (kind == 1) {
            FIELD(work, void *, 0x8C) = D_80158E5C;
            left = FIELD(work, s32, 0x14) | 0x6000;
            right = FIELD(work, s32, 0x1C) | 0x6000;
            FIELD(work, s32, 0x14) = left;
            FIELD(work, s32, 0x1C) = right;
            FIELD(part_b, void *, 0x2C) = D_8015C510;
            goto common_tail;
        }
        if (kind >= 2) {
            FIELD(work, void *, 0x8C) = D_80158E5C;
            left = FIELD(work, s32, 0x14) | 0x2000;
            right = FIELD(work, s32, 0x1C) | 0x2000;
            FIELD(work, s32, 0x14) = left;
            FIELD(work, s32, 0x1C) = right;
            FIELD(part_b, void *, 0x2C) = D_8015C510;
            goto common_tail;
        }

        if (((arg0 & ~3) << 16) != 0) {
            goto set_work_callback;
        }
        if (FIELD(work, s32, 0x14) & 0x200) {
            goto set_actor_callback;
        }
        if (!(func_800A6D30() & 1)) {
            goto set_actor_callback;
        }
        func_800A48F0(work, 1,
                      (func_800A6D30() & 0x3F) | 0x20);
        FIELD(part_b, void *, 0x2C) = D_8015C538;

set_actor_callback:
        callback_page = CALLBACK_PAGE;
        ASM_KEEP(callback_page);
        FIELD(actor, void *, 0x8C) = (void *)(callback_page - 0x71A4);
        goto normal_done;

set_work_callback:
        callback_page = CALLBACK_PAGE;
        ASM_KEEP(callback_page);
        FIELD(work, void *, 0x8C) = (void *)(callback_page - 0x71A4);

normal_done:
        FIELD(part_b, void *, 0x2C) = D_8015C510;

common_tail:
        ASM_KEEP(arg0);
        FIELD(obj, void *, 0x10) = D_80158A58;
        func_800A9C18(obj, part_a, part_b, (s16)final_arg0);
        FIELD(actor, u8, 0x9A) = 0xFF;
        FIELD(actor, s8, 0x9C) = -1;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
