#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((s8 *)(expr) + (offset)))

extern s32 func_8002406C(s32);
extern void *func_8003FC64(s32);
extern M2C_UNK func_8004491C();
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand();
extern M2C_UNK D_80024670[];
extern M2C_UNK D_800246C4[];

void func_800247B8(void *arg0, void *arg1)
{
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 random;
    void *obj;
    void *work;
    void *part;
    void *dest;

    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        work = obj + 0x20;
        FIELD(work, s16, 0x5A) = 10;
        FIELD(work, s16, 0x5C) = 10;
        random = func_8002406C(8);
        FIELD(work, s32, 0x18) = 0x303030;
        if (random & 1) {
            FIELD(work, u8, 0x18) = 0x90;
        }
        if (random & 2) {
            FIELD(work, u8, 0x19) = 0x90;
        }
        if (random & 4) {
            FIELD(work, u8, 0x1A) = 0x90;
        }
        FIELD(work, s32, 0x10) = 0;
        FIELD(work, s32, 0x14) = 0;
        FIELD(work, s32, 0x1C) = FIELD(work, s32, 0x18);
        FIELD(obj, s32, 0x20) = FIELD(work, s32, 0x10);
        FIELD(work, s32, 4) = FIELD(work, s32, 0x14);
        FIELD(work, s32, 8) = FIELD(work, s32, 0x18);
        FIELD(work, s32, 0xC) = FIELD(work, s32, 0x1C);
        FIELD(obj, M2C_UNK *, 0x10) = D_800246C4;
        func_8004491C(obj, D_80024670);

        part = FIELD(obj, void *, 0xC);
        FIELD(part, s16, 0x10) = 0x20;
        FIELD(part, u16, 0x14) |= 0xC;
        temp_s0 = rand(part) & 0xFFF;
        temp_s0_2 = (FIELD(arg0, s16, 0x56) * func_80064584(temp_s0)) >> 12;
        FIELD(work, s16, 0x24) = (FIELD(arg0, s16, 0x56) * func_800644B8(temp_s0)) >> 12;
        temp_s1 = rand() & 0xFFF;
        FIELD(work, s16, 0x20) = ((s16)temp_s0_2 * func_80064584(temp_s1)) >> 12;
        FIELD(work, s16, 0x22) = ((s16)temp_s0_2 * func_800644B8(temp_s1)) >> 12;

        FIELD(work, s16, 0x26) = FIELD(work, u16, 0x20) + func_8002406C(0x10) - 8;
        FIELD(work, s16, 0x28) = FIELD(work, u16, 0x22) + func_8002406C(0x10) - 8;
        random = func_8002406C(0x10);
        FIELD(work, s16, 0x36) = 0;
        FIELD(work, s16, 0x34) = 0;
        FIELD(work, s16, 0x32) = 0;
        FIELD(work, s16, 0x30) = 0;
        FIELD(work, s16, 0x2E) = 0;
        FIELD(work, s16, 0x2C) = 0;
        FIELD(work, s16, 0x2A) = FIELD(work, u16, 0x24) + random - 8;

        dest = FIELD(obj, void *, 8);
        FIELD(dest, u16, 2) = FIELD(arg1, u16, 2);
        FIELD(dest, u16, 6) = FIELD(arg1, u16, 6);
        FIELD(dest, u16, 0xA) = FIELD(arg1, u16, 0xA);

        part = FIELD(obj, void *, 0xC);
        FIELD(part, s16, 0x1E) = 0x1000;
        FIELD(part, s16, 0x1C) = 0x1000;
        FIELD(part, u8, 0xE) = 0x80;
        FIELD(part, u8, 0xD) = 0x80;
        FIELD(part, u8, 0xC) = 0x80;
    }
}
