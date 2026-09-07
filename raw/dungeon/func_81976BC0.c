#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FD64(s32, void *);
extern s32 rand(void);
extern u8 D_80024050[];
extern s32 D_800261E4[];
extern u8 D_80083498[];

void func_81976BC0(s32 arg0, s32 arg1)
{
    s32 value;
    void *child;
    void *object;
    void *fields;

    object = func_8003FD64(0x12, D_80083498);
    if (object != 0) {
        FIELD(object, void *, 0x10) = D_80024050;
        fields = (u8 *)object + 0x20;
        FIELD(fields, s16, 0xC) = 0;
        FIELD(fields, s16, 0xE) = 0;
        FIELD(fields, s16, 0x10) = 0;
        FIELD(object, s32, 0x20) = arg0;
        FIELD(fields, void *, 4) = D_80083498;
        FIELD(fields, s32, 8) = arg1;
        child = FIELD(object, void *, 0xC);
        FIELD(child, s32, 8) = D_800261E4[0];
        FIELD(child, s8, 0xE) = 0x40;
        FIELD(child, s8, 0xD) = 0x40;
        FIELD(child, s8, 0xC) = 0x40;
        FIELD(child, s16, 0x1E) = 0x1800;
        FIELD(child, s16, 0x1C) = 0x1800;
        value = rand();
        FIELD(child, s16, 0x1A) = value % 0x1000;
        FIELD(child, s16, 0x12) = 0x7DCF;
        FIELD(child, u16, 0x10) |= 0x20;
        FIELD(child, u16, 0x14) |= 0x10C;
    }
}
