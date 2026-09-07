#include "common.h"

#define FIELD(base, type, off) (*(type *)((u8 *)(base) + (off)))
#define NULL ((void *)0)

extern volatile u16 D_800135C2;
extern s32 D_80020054;
extern s32 D_80022F60;
extern s32 D_8002390C;
extern s32 D_80023920;
extern s32 D_800240B0;
extern s32 D_80026F0C;
extern s32 D_80045340;
extern s32 D_800F9B40;

extern void *func_8003FC64(s32);
extern void func_80022E64(void *, s32, void *, void *);
extern void func_8004491C(void *, void *);
extern void func_8008F104(void *, void *, void *);

s32 func_80022C8C(void)
{
    s32 work[6];
    s32 state;
    void *link;
    void *record;
    void *held;
    void *tail_base;
    s32 even_value;
    s32 odd_value;
    s32 odd_half;
    s32 count;
    register u8 *held_page ASM_REG("$3");
    register volatile u16 *count_page ASM_REG("$4");
    register s32 remat ASM_REG("$2");
    register void *call_work ASM_REG("$4");
    register s32 call_kind ASM_REG("$5");
    register void *call_table ASM_REG("$6");

    link = NULL;
    held_page = (u8 *)0x80020000;
    ASM_KEEP_NV(held_page);
    count_page = (volatile u16 *)0x80010000;
    ASM_KEEP(count_page);
    ASM_SCHED_BARRIER();
    count = (s16)*(count_page + (0x35C2 / 2));
    held = held_page + 0x54;
    if (count < 20) {
        *(count_page + (0x35C2 / 2)) = 20;
    }

    state = (s32)func_8003FC64(2);
    if (state != 0) {
        link = (u8 *)state + 0x20;
        FIELD((void *)state, void *, 0x10) = &D_80022F60;
    }

    work[0] = 0x03800000;
    work[1] = 0x02600000;
    work[2] = (s32)0xFFA00000;
    func_80022E64(work, 0x34, &D_8002390C, link);

    state = 3;
    even_value = 0x02700000;
    odd_value = 0x04900000;
    odd_half = 0x02E00000;
    work[2] = (s32)0xFFE00000;
    do {
        if ((state >> 1) != 0) {
            work[0] = even_value;
        } else {
            work[0] = odd_value;
        }

        if (state & 1) {
            work[1] = odd_half;
        } else {
            remat = 0x03E00000;
            ASM_KEEP(remat);
            work[1] = remat;
        }

        call_work = work;
        ASM_KEEP(call_work);
        call_kind = 0x35;
        ASM_KEEP(call_kind);
        call_table = (void *)0x80020000;
        ASM_KEEP(call_table);
        call_table = (u8 *)call_table + 0x3920;
        ASM_KEEP(call_table);
        func_80022E64(call_work, call_kind, call_table, link);
        state--;
    } while (state >= 0);

    state = (s32)func_8003FC64(0x136);
    if (state != 0) {
        FIELD((void *)state, void *, 0x10) = &D_800240B0;
        func_8004491C((void *)state, &D_80045340);

        record = FIELD((void *)state, void *, 0x0C);
        FIELD(record, s16, 0x1E) = 0x1000;
        FIELD(record, s16, 0x1C) = 0x1000;
        FIELD(record, void *, 0x08) = &D_800F9B40;
        FIELD(record, s8, 0x04) = 0;
        FIELD(record, s8, 0x05) = 0;
        FIELD(record, s32, 0x0C) = 0x00808080;
        tail_base = (u8 *)state + 0x20;
        FIELD(tail_base, void * volatile, 0x4C) = held;

        func_8008F104((u8 *)state + 0x24,
                      FIELD((void *)state, void *, 0x08),
                      &D_80026F0C);

        FIELD(FIELD((void *)state, void *, 0x08), s32, 0x00) = 0x03800000;
        FIELD(FIELD((void *)state, void *, 0x08), s32, 0x04) = 0x03C00000;
        FIELD(FIELD((void *)state, void *, 0x08), s32, 0x08) = 0;
        FIELD((void *)state, void *, 0x20) = link;
    }

    return 0;
}

/* MECHANISM: A 24-byte escaping work record and local in-range joins establish the 0x48 frame/CFG.
   One s32 state web reuses s0 for both object pointers and the loop counter.
   Guarded v0/a2 rematerialization removes two false loop-invariant saved-register holds.
   Split page bases plus ASM_KEEP_NV place the prologue lui pair and delayed s5 addiu exactly. */
