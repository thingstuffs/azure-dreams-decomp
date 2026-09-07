#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u8 bytes[8];
} Unaligned8;

typedef struct {
    void *field0;
    void *field4;
    Unaligned8 field8;
    Unaligned8 field10;
    s16 field18;
    s16 field1A;
    u32 unused1C;
} CallRecord;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} OutputVector;

extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern s32 rand(void);
extern void func_800DBA90(void *);
extern u32 D_800814A0;

void func_818E0D94(void *arg0, void *arg1, void *arg2)
{
    CallRecord record;
    OutputVector output;
    void *inner;
    u16 temp;
    s8 value;

    inner = FIELD(arg0, void *, 0);
    FIELD(inner, u16, 0x52) |= 0x8000;
    FIELD(arg0, u16, 0x48)++;

    temp = FIELD(arg2, u16, 0x1E) - 0x50;
    FIELD(arg2, u16, 0x1E) = temp;
    FIELD(arg2, u16, 0x1C) = temp;

    {
        register s32 call_arg ASM_REG("$4");
        s32 random;
        s32 height;

        random = rand() & 0x3F;
        call_arg = FIELD(arg0, s16, 0x48) * 0x32;
        ASM_KEEP(call_arg);
        height = FIELD(arg0, u16, 0x18);
        call_arg += 0xC8;
        height += 0x200;
        height += random;
        FIELD(arg0, u16, 0x18) = height;
        output.x = func_800644B8(call_arg) / 80;
    }
    output.y = 0;
    {
        s32 random;
        s32 negative;

        random = rand() & 3;
        negative = 0 - FIELD(arg0, s16, 0x48);
        output.z = (negative * 4) + random - 1;
    }

    value = ((u8)output.x + 0x28) - FIELD(arg0, u8, 0x48);
    FIELD(arg2, s8, 0xD) = value;
    FIELD(arg2, s8, 0xC) = value;
    FIELD(arg2, s8, 0xE) = ((u8)output.x + 0x60) - FIELD(arg0, u8, 0x48);

    record.field0 = &output;
    record.field4 = &output;
    record.field8 = *(Unaligned8 *)((u8 *)arg0 + 0x14);
    record.field10 = *(Unaligned8 *)((u8 *)arg0 + 0x0C);
    record.field18 = 1;
    record.field1A = 0;
    func_800DBA90(&record);

    FIELD(arg1, u16, 2) = output.x;
    FIELD(arg1, u16, 6) = output.y;
    FIELD(arg1, u16, 0xA) = output.z;
    func_800478B8(arg2);

    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg2, s8, 4) = 0;
        FIELD(arg2, s8, 5) = 0;
    }

    if (FIELD(arg0, s16, 0x48) >= 0x20) {
        register u32 *page ASM_REG("$3");

        FIELD(arg0, u16, -2) |= 0x8000;
        page = (u32 *)0x80080000;
        ASM_KEEP(page);
        page[0x528] |= 0x8000;
    }
}
