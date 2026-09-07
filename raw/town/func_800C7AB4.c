#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_8003FC64(s32);
extern s32 func_8004491C();
extern s32 func_800C52B8(s32);
extern u8 D_800345B8[];
extern u8 D_800C52D0[];
extern u8 D_800F148C[];

void *func_800C5214(s32 arg0)
{
    void *part;
    void *object;

    object = func_8003FC64(0x136);
    if (object == NULL) {
        return NULL;
    }

    {
        register void *result ASM_REG("$2");
        register u16 flags ASM_REG("$3");
        register s32 value ASM_REG("$4");

        FIELD(object, void *, 0x10) = D_800C52D0;
        FIELD(object, s32, 0xBC) = arg0;
        part = FIELD(object, void *, 0xC);
        FIELD(part, s16, 0x1E) = 0x1800;
        FIELD(part, s16, 0x1C) = 0x1800;
        FIELD(part, s8, 0xE) = 0x4C;
        FIELD(part, s8, 0xD) = 0x4C;
        FIELD(part, s8, 0xC) = 0x4C;
        FIELD(part, void *, 8) = D_800F148C;
        FIELD(part, s32, 0) = 0;
        FIELD(part, s8, 4) = 0;
        FIELD(part, s8, 5) = 0;
        FIELD(part, s16, 6) = -0x10;
        func_8004491C(object, D_800345B8);
        result = object;
        ASM_KEEP(result);
        flags = FIELD(part, u16, 0x14);
        value = 0x20;
        FIELD(part, s16, 0x10) = value;
        FIELD(part, u16, 0x14) = flags | 0x1C;
        return func_800C52B8(value);
    }
}

/* MECHANISM: The NULL guard preserves retail's beqz into a trailing literal-zero return.
   Returning the s32 func_800C52B8 result exposes LEAD-22's tail shape, converting jal to j
   while retaining the flags store in its delay slot; v0/v1/a0 pins preserve the live roles. */
