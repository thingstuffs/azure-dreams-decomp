#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_80158E9C[];
extern u8 D_8015CED8[];
extern u8 D_8015CF00[];
extern void func_80158A98(void);

void *func_80158894(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    register void *result ASM_REG("$16");
    register void *created ASM_REG("$19");
    register void *position ASM_REG("$22");
    register s32 part_or_arg3 ASM_REG("$17");
    register s32 actor_or_arg2 ASM_REG("$20");
    register s32 saved_arg0 ASM_REG("$18");
    register s32 saved_arg1 ASM_REG("$21");
    register s32 original_arg0 ASM_REG("$23");
    register u32 callback_page ASM_REG("$2");
    register s32 create_kind ASM_REG("$4");
    register void *create_data ASM_REG("$5");
    s32 kind;

    saved_arg0 = arg0;
    result = 0;
    create_kind = 0x112;
    saved_arg1 = arg1;
    ASM_KEEP_DEP_NV(saved_arg1, create_kind);
    create_data = D_80083498;
    part_or_arg3 = arg3;
    ASM_KEEP_DEP_NV(part_or_arg3, create_data);
    actor_or_arg2 = arg2;
    created = func_8003FD64(create_kind, create_data);
    ASM_KEEP4_NV(saved_arg0, saved_arg1, part_or_arg3, actor_or_arg2);
    original_arg0 = saved_arg0;
    if (created == 0) {
        goto done;
    }
    result = (u8 *)created + 0x20;
    ASM_KEEP(result);
    FIELD(result, s8, 0x13) = 0xE;
    func_8004491C(created, D_80045340);

    position = FIELD(created, void *, 8);
    FIELD(position, s16, 0xA) = part_or_arg3;
    part_or_arg3 = (s32)FIELD(created, void *, 0xC);
    kind = saved_arg0 & 3;
    FIELD((void *)part_or_arg3, s8, 0x25) = actor_or_arg2;
    actor_or_arg2 = (s32)result;
    FIELD((void *)part_or_arg3, s8, 0x24) = saved_arg1;

    if (kind == 1) {
        FIELD(result, void *, 0x8C) = D_80158E9C;
        FIELD(result, u32, 0x14) |= 0x6000;
        FIELD(result, u32, 0x1C) |= 0x6000;
        FIELD((void *)part_or_arg3, void *, 0x2C) = D_8015CED8;
        goto setup;
    }
    if (kind >= 2) {
        FIELD(result, void *, 0x8C) = D_80158E9C;
        FIELD(result, u32, 0x14) |= 0x2000;
        FIELD(result, u32, 0x1C) |= 0x2000;
        FIELD((void *)part_or_arg3, void *, 0x2C) = D_8015CED8;
        goto setup;
    }

    if (((saved_arg0 & ~3) << 16) != 0) {
        goto set_actor;
    }
    if (!(FIELD(result, u32, 0x14) & 0x200)) {
        if (func_800A6D30() & 1) {
            func_800A48F0(result, 1,
                (func_800A6D30() & 0x3F) | 0x20);
            FIELD((void *)part_or_arg3, void *, 0x2C) = D_8015CF00;
        }
    }

#ifdef NON_MATCHING
    FIELD((void *)actor_or_arg2, void *, 0x8C) = D_80158E9C;
#else
    callback_page = 0x80160000;
    ASM_KEEP_NV(callback_page);
    FIELD((void *)actor_or_arg2, void *, 0x8C) =
        (void *)(callback_page - 0x7164);
#endif
    goto set_part;

set_actor:
#ifdef NON_MATCHING
    FIELD(result, void *, 0x8C) = D_80158E9C;
#else
    callback_page = 0x80160000;
    ASM_KEEP_NV(callback_page);
    FIELD(result, void *, 0x8C) = (void *)(callback_page - 0x7164);
#endif

set_part:
    FIELD((void *)part_or_arg3, void *, 0x2C) = D_8015CED8;

setup:
    ASM_KEEP(saved_arg0);
    FIELD(created, void *, 0x10) = func_80158A98;
    func_800A9C18(created, position, (void *)part_or_arg3,
        (s16)original_arg0);
    FIELD((void *)actor_or_arg2, u8, 0x9A) = 0xFF;
    FIELD((void *)actor_or_arg2, s8, 0x9C) = -1;
    func_800AA36C((void *)actor_or_arg2, position,
        (void *)part_or_arg3, result);

done:
    return result;
}
