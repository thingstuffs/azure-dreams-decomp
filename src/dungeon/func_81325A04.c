#include "common.h"

typedef struct S_func_81325A04_0 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0x06];
    union {
        s16 s;
        u16 u;
    } unk_96;
    u8 pad_98[0x03];
    u8 unk_9B;
    u8 pad_9C[0x17];
    u8 unk_B3;
    u8 unk_B4;
} S_func_81325A04_0;

typedef struct S_func_81325A04_1 {
    u8 pad_00[0x02];
    s16 unk_02;
    u8 pad_04[0x02];
    s16 unk_06;
    u8 pad_08[0x04];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_81325A04_1;

typedef struct S_func_81325A04_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x0E];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x06];
    s32 unk_2C;
} S_func_81325A04_2;

typedef struct S_func_81325A04_3 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x01];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
} S_func_81325A04_3;

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228[];
extern s32 D_80083460[];
extern u8 D_8016B778[];
extern u8 D_8017467C[];
extern u8 D_80174684[];
extern u8 D_801746C4[];
extern u8 D_801746CC[];

extern s32 func_800A2B04();
extern s32 func_800AAA54();
extern s32 func_800AD4D0();
extern s32 func_80047784();

u8 *func_8016D204(S_func_81325A04_0 *arg0, S_func_81325A04_1 *arg1, S_func_81325A04_2 *arg2, S_func_81325A04_3 *arg3) {
    s32 state;
    s16 timer;
    s16 next;
    u16 raw;
    s32 value;
    s32 current;
    s32 below2;
    s32 x;
    s32 y;
    s32 ax;
    s32 dy;
    s32 ax2;
    s32 dy2;
    s32 *shared;
    u8 *chosen;
    register u32 page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 *tail_a1;

    state = arg0->unk_9B;
    if (state == 1) {
        goto state1_body;
    }
    if (state < 2) {
        if (state == 0) {
            goto state0_body;
        }
        return;
    }
       /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (state == 2) {
        goto state2_body;
    }
    if (state == 3) {
        goto state3_body;
    }
    return;

state0_body:
    func_800AD4D0(arg3);
    arg0->unk_96.s = 12;
    arg0->unk_9B = (u8)(arg0->unk_9B + 1);
    if (arg3->unk_28 == 0) {
        arg1->unk_14 = 0;
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        if (arg0->unk_B4 != 0) {
            page = (u32)D_8016B778;
            ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            arg0->unk_9B = 0;
            goto store_chosen;
        }
        goto initialize;
    }
    chosen = (u8 *)3;
    if (!(arg2->unk_14 & 0x8000)) {
        return chosen;
    }
    arg0->unk_96.s = 0;
    arg0->unk_9B = (u32)chosen;
    return;

state1_body:
        raw = arg0->unk_96.u;
        raw--;
        arg0->unk_96.u = raw;
        timer = (s16)raw;
        if (timer >= 11) {
            arg1->unk_0C =
                *(s16 *)((u8 *)D_8006CCD8 + ((arg3->unk_6A >> 8) & 0xE)) << 20;
            arg1->unk_10 =
                *(s16 *)((u8 *)D_8006CCE8 + ((arg3->unk_6A >> 8) & 0xE)) << 20;
            arg2->unk_14 |= 0x800;
            return;
        }
        if (timer >= 7) {
            x = arg1->unk_0C;
            if (x < 0) {
                x += 3;
            }
            y = arg1->unk_10;
            arg1->unk_0C = x >> 2;
            if (y < 0) {
                y += 3;
            }
            arg1->unk_10 = y >> 2;
            return;
        }
        below2 = timer < 2;
        if (!below2) {
            arg1->unk_10 = 0;
            arg1->unk_0C = 0;
            return;
        }
        if (timer == state) {
            arg2->unk_14 &= 0xF7FF;
            return;
        }
        if (timer != 0) {
            return (u8 *)(u32)below2;
        }
        timer = 4;
        page = arg0->unk_9B;
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        arg0->unk_96.s = timer;
        goto increment_state;
state2_body:
    timer = arg0->unk_96.s;
    if (timer != 0) {
        ax = arg2->unk_24 << 6;
        dy = arg1->unk_02 - 32;
        arg1->unk_0C = ((ax - dy) << 16) / timer;
        ax2 = arg2->unk_25 << 6;
        dy2 = arg1->unk_06 - 32;
        arg1->unk_10 =
            ((ax2 - dy2) << 16) / arg0->unk_96.s;
    }
    page = arg0->unk_96.u;
    next = (s16)(page - 1);
    page <<= 16;
    arg0->unk_96.s = next;
    if ((s32)page > 0) {
            return (u8 *)page;
    }
    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    page = arg0->unk_9B;
increment_state:
    arg0->unk_9B = (u8)(page + 1);
    return;

state3_body:
    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    if (arg3->unk_28 != 0) {
        goto state3_continue;
    }
    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    if (arg0->unk_B4 != 0) {
        goto state3_tail;
    }
initialize:
    arg0->unk_9B = 0;
    func_800AAA54(arg0, arg1, arg2, D_801746CC);
    return;

state3_tail:
    page = (u32)D_8016B778;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    arg0->unk_9B = 0;
    goto store_chosen;

state3_continue:
    current = arg2->unk_2C;
    if (current == (s32)D_801746C4) {
        if (arg0->unk_B3 == 0) {
            page = 0x80170000;
            ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            tail_a1 = (u8 *)page + 18044;
        } else {
            page = (u32)D_80174684;
            tail_a1 = (u8 *)page;
        }
        if (current != (s32)tail_a1) {
            arg2->unk_2C = (s32)tail_a1;
            value = D_80083228[0] + arg3->unk_2A;
            func_80047784(arg2, *(u8 *)((u32)(((value + 0x100) >> 9) & 7) + (u32)tail_a1), 0);
        }
    }
    shared = D_80083460;
    if (shared[4] == (s32)((u8 *)arg3 - 0x20)) {
        shared[4] &= 0x7FFFFFFF;
    }
    page = (u32)D_8016B778;
store_chosen:
    arg0->unk_8C = (u8 *)page;
    return (u8 *)page;
}
