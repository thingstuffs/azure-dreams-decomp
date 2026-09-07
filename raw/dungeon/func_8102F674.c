#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80045340;
extern s32 D_80083498;
extern u8 D_8017103C[];
extern s32 D_801714B8;
extern u8 D_8017609C[];
extern u8 D_801760EC[];

void *func_80170E74(s16 arg0, s8 arg1, s8 arg2, s32 arg3)
{
    s32 kind;
    register s32 flags0 ASM_REG("$2");
    register s32 flags1 ASM_REG("$3");
    void *result;
    void *object;
    void *part0;
    void *part1;
    void *result_copy;

    result = 0;
    object = func_8003FD64(0x112, &D_80083498);
    if (object == 0) {
        goto done;
    }

    result = (u8 *)object + 0x20;
    ASM_KEEP(result);
    FIELD(object, void *, 0x10) = D_8017103C;
    FIELD(result, s8, 0x13) = 42;
    func_8004491C(object, &D_80045340);

    {
        register void *page ASM_REG("$2");
        void *handler;

        page = (void *)0x80170000;
        ASM_KEEP(page);
        do {
            part0 = FIELD(object, void *, 8);
        } while (0);
        handler = (u8 *)page + 0x609C;
        FIELD(part0, s16, 0xA) = arg3;
        part1 = FIELD(object, void *, 0xC);
        kind = arg0 & 3;
        FIELD(part1, s8, 0x25) = arg2;
        result_copy = result;
        FIELD(part1, void *, 0x2C) = handler;
    }
    FIELD(part1, s8, 0x24) = arg1;

    if (kind == 1) {
        flags0 = FIELD(result, s32, 0x14);
        flags1 = FIELD(result, s32, 0x1C);
        flags0 |= 0x6000;
        flags1 |= 0x6000;
        goto store_flags;
    }

    if (kind >= 2) {
        flags0 = FIELD(result, s32, 0x14);
        flags1 = FIELD(result, s32, 0x1C);
        flags0 |= 0x2000;
        flags1 |= 0x2000;
store_flags:
        ASM_KEEP(flags0);
        ASM_KEEP(flags1);
        FIELD(result, s32, 0x14) = flags0;
        FIELD(result, s32, 0x1C) = flags1;
        goto common;
    }

    if (((arg0 & -4) << 16) != 0) {
        goto common;
    }
    if ((FIELD(result, s32, 0x14) & 0x200) != 0) {
        goto common;
    }
    if ((func_800A6D30() & 1) != 0) {
        func_800A48F0(result, 1, (func_800A6D30() & 0x3F) | 0x20);
        FIELD(part1, void *, 0x2C) = D_801760EC;
    }

common:
    func_800A9C18(object, part0, part1, arg0);
    ASM_KEEP(object);
    FIELD(result_copy, u8, 0x9A) = 0xFF;
    FIELD(result_copy, s8, 0x9C) = -1;
    FIELD(result_copy, void *, 0x8C) = &D_801714B8;
    func_800AA36C(result_copy, part0, part1, result);

done:
    ASM_KEEP(result);
    return result;
}
