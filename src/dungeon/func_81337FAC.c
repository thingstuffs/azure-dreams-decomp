#include "common.h"

typedef struct {
    u8 pad[0x3714];
    u16 flags;        /* 0x3714 */
    s16 f3716;
    s16 f3718;
    s16 f371A;
    void *handler;    /* 0x371C */
} SysWork;

typedef struct {
    u8 pad[0xA];
    u16 counter;      /* 0x0A */
} DungeonCounters;

extern void func_8009A028(void *);
extern u16 func_800A0818(u8, u8, u8, u8, s32 *);
extern void func_80164BA4(void *);
extern void func_8017394C(void);

extern u16 D_80013714;
extern s16 D_80013716;
extern s16 D_80013718;
extern s16 D_8001371A;
extern void *D_8001371C;
extern u8 D_80082E80[];
extern DungeonCounters D_80083460;
extern u16 D_800834E2;
extern s32 D_800E296C;
extern u8 D_80173C8C[];
extern u8 D_80173D74[];
extern u8 *D_80175D50;
extern s32 D_80175DC4;
extern s16 D_80175DC8;

void func_8016EFAC(void)
{
    s32 stack_arg;
    s32 i;
    u16 result;
    u8 *page;
    SysWork *sys;
    u8 *object;
    u8 *target;
    u8 *nested;
    u8 *record;
    DungeonCounters *page83460;
    u32 idx;
    u8 *tbl;
    u32 high_bit;

    i = 0;
    page = (u8 *)0x800E0000;
    sys = (SysWork *)0x80010000;
    high_bit = 0x80000000;
    D_80175D50[0xCF] = 1;
    sys->f371A = 0;
    sys->f3718 = 0;
    sys->f3716 = 0;
    page83460 = &D_80083460;
    page83460->counter -= 1;
    object = D_80175D50;
    sys->flags = (sys->flags | 9) & 0xFFEF;
    idx = D_800834E2 >> 7;
    tbl = D_80173C8C;
    sys->handler = *(void **)(tbl + (idx & 0x1C));
    nested = *(u8 **)(object + 0xC);
    D_800E296C |= 0x200000;
    target = object + 0x20;
    result = func_800A0818(nested[0x24], nested[0x25],
                           D_80082E80[0x24], D_80082E80[0x25], &stack_arg);
    *(u16 *)(target + 0x2A) = result;
    result >>= 7;
    D_80175DC8 = 0;
    {
        u8 *table_base;

        table_base = D_80173D74;
        result &= 0x1C;
        D_80175DC4 = *(s32 *)(table_base + result);
    }

    do {
        record = *(u8 **)(*(u8 **)(page + 0x3D7C) + i * 4 + 0xAC);
        if (record != 0) {
            u8 *tail;
            func_80164BA4(record);
            func_8009A028(*(void **)(*(u8 **)(page + 0x3D7C) + i * 4 + 0xAC));
            tail = *(u8 **)(*(u8 **)(page + 0x3D7C) + i * 4 + 0xAC) - 0x20;
            *(u32 *)(tail + 0x10) |= high_bit;
        }
        i++;
    } while (i < 2);
    func_8017394C();
}

/* MECHANISM (stock 2.7.2-cdk -O2 -G0, no bridge):
   - D_80175D50 is a plain pointer variable (non-struct MEM) while every page
     store goes through a struct pointer (in-struct MEM): gcc 2.x's
     true/anti_dependence struct-vs-scalar rule then frees the second load
     of D_80175D50 from all page stores and sched2 floats it to retail's slot.
   - The table pointer is parked in `tbl` between the `>> 7` and the `& 0x1C`
     so its lui/addiu pair is scheduled inside the index chain; that lengthens
     the pair's qty (QTY_CMP_PRI 1.33 < 1.5) so the index chain is coloured
     first and takes $v0, the pair $v1 (retail's roles).
   - The 0x800e page is held across the loop while the high-bit literal stays
     live across calls; a five-argument call owns the 0x18 stack local. */
