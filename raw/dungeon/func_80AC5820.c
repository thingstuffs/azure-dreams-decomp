#include "common.h"

typedef long long s64;

#define FIELD(p, type, off) (*(type *)((s8 *)(p) + (off)))

extern void func_800478B8();
extern s32 func_80065420(void *, void *, void *, void *);

extern s32 D_800814A0 __attribute__((section(".data")));
extern s16 D_80083228 __attribute__((section(".data")));
extern s8 D_800DCECC[8];

typedef struct StackWork {
    u16 xyz[3];
    u16 pad;
    s64 out18;
    s32 out20;
    s32 out24;
} StackWork;

void func_80AC5820(void *arg0, void *arg1, void *arg2)
{
    StackWork work;
    s16 count;
    s32 first;
    s32 second;
    s8 *table_entry;
    u32 angle_page;
    void *other;

    work.xyz[0] = FIELD(arg1, u16, 2);
    work.xyz[1] = FIELD(arg1, u16, 6);
    work.xyz[2] = FIELD(arg1, u16, 0xA);
    first = func_80065420(work.xyz, &work.out18, &work.out20, &work.out24);

    other = FIELD(arg0, void *, 0xA8);
    work.xyz[0] = FIELD(other, u16, 2);
    work.xyz[1] = FIELD(other, u16, 6);
    work.xyz[2] = FIELD(other, u16, 0xA);
    second = func_80065420(work.xyz, &work.out18, &work.out20, &work.out24);
    angle_page = 0x80080000;
    ASM_KEEP(angle_page);
    table_entry = &D_800DCECC[
        ((*(s16 *)(angle_page + 0x3228) +
          FIELD(arg0, s16, 0x94) + 0x100) >> 9) & 7];
    FIELD(arg2, s16, 6) = first - second - *table_entry * 2;

    func_800478B8(arg2, table_entry);
    count = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = count;
    if ((count << 16) <= 0) {
        register u32 flags_page ASM_REG("$3");

        flags_page = 0x80080000;
        ASM_KEEP(flags_page);
        FIELD(arg0, u16, -2) |= 0x8000;
        *(s32 *)(flags_page + 0x14A0) |= 0x8000;
    }
}

/* MECHANISM: StackWork fixes the 0x40 frame and the s2/s1/s0 stack-output roles.
   A retained 0x80080000 page base yields the displaced angle/global accesses.
   The table pointer stays in a1; only the tail page live range is pinned to v1. */
