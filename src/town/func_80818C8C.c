#include "common.h"

typedef struct S_80022C8C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80022C8C_0;   /* (void *)state in func_80022C8C */

typedef struct S_80022C8C_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_80022C8C_1;   /* record in func_80022C8C */

typedef struct S_80022C8C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80022C8C_2;   /* ((S_80022C8C_0 *)((void *)state))->unk_08 in func_80022C8C */


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
    S_80022C8C_1 *record;
    void *held;
    void *tail_base;
    s32 even_value;
    s32 odd_value;
    s32 odd_half;
    s32 count;
    u8 *held_page;
    volatile u16 *count_page;
    s32 remat;
    void *call_work;
    s32 call_kind;
    void *call_table;

    link = NULL;
    held_page = (u8 *)0x80020000;
    ASM_KEEP_NV(held_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    count_page = (volatile u16 *)0x80010000;
    count = (s16)*(count_page + (0x35C2 / 2));
    held = held_page + 0x54;
    if (count < 20) {
        *(count_page + (0x35C2 / 2)) = 20;
    }

    state = (s32)func_8003FC64(2);
    if (state != 0) {
        link = (u8 *)state + 0x20;
        ((S_80022C8C_0 *)((void *)state))->unk_10 = &D_80022F60;
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
            ASM_KEEP(remat);   /* MATCH pin: retail immediate-load split depends on it */
            work[1] = remat;
        }

        call_work = work;
        ASM_KEEP(call_work);   /* MATCH pin: retail schedule: same instructions, different order without it */
        call_kind = 0x35;
        ASM_KEEP(call_kind);   /* MATCH pin: retail schedule: same instructions, different order without it */
        call_table = (void *)0x80020000;
        ASM_KEEP(call_table);   /* MATCH pin: load-bearing for the whole function shape */
        call_table = (u8 *)call_table + 0x3920;
        func_80022E64(call_work, call_kind, call_table, link);
        state--;
    } while (state >= 0);

    state = (s32)func_8003FC64(0x136);
    if (state != 0) {
        ((S_80022C8C_0 *)((void *)state))->unk_10 = &D_800240B0;
        func_8004491C((void *)state, &D_80045340);

        record = ((S_80022C8C_0 *)((void *)state))->unk_0C;
        record->unk_1E = 0x1000;
        record->unk_1C = 0x1000;
        record->unk_08 = &D_800F9B40;
        record->unk_04 = 0;
        record->unk_05 = 0;
        record->unk_0C = 0x00808080;
        tail_base = (u8 *)state + 0x20;
        (*(void * volatile *)((u8 *)tail_base + 0x4C)) = held;

        func_8008F104((u8 *)state + 0x24,
                      ((S_80022C8C_0 *)((void *)state))->unk_08,
                      &D_80026F0C);

        ((S_80022C8C_2 *)(((S_80022C8C_0 *)((void *)state))->unk_08))->unk_00 = 0x03800000;
        ((S_80022C8C_2 *)(((S_80022C8C_0 *)((void *)state))->unk_08))->unk_04 = 0x03C00000;
        ((S_80022C8C_2 *)(((S_80022C8C_0 *)((void *)state))->unk_08))->unk_08 = 0;
        ((S_80022C8C_0 *)((void *)state))->unk_20 = link;
    }

    return 0;
}

/* MECHANISM: A 24-byte escaping work record and local in-range joins establish the 0x48 frame/CFG.
   One s32 state web reuses s0 for both object pointers and the loop counter.
   Guarded v0/a2 rematerialization removes two false loop-invariant saved-register holds.
   Split page bases plus ASM_KEEP_NV place the prologue lui pair and delayed s5 addiu exactly. */
