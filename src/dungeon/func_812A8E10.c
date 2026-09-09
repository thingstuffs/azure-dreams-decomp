#include "common.h"

typedef struct { u8 pad0[0x8C]; void *field8c; u8 pad90[6]; s16 count96; u8 pad98[3]; u8 state9b; } S_A;
typedef struct { u8 pad0[2]; s16 x2; u8 pad4[2]; s16 y6; u8 pad8[4]; s32 dxC; s32 dy10; s32 dz14; } S_B;
typedef struct { u8 pad0[0x14]; u16 flags14; u8 pad16[0x0E]; u8 x24; u8 y25; } S_C;
typedef struct { u8 pad0[0x28]; u8 flag28; u8 pad29[0x41]; u16 index6A; } S_D;

extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_80083460[3];
extern u8 D_80171FA4[];
extern void func_800A2B04(S_B *, u8, u8);
extern void func_800AD4D0(S_D *);

void func_80174610(S_A *a0, S_B *a1, S_C *a2, S_D *a3) {
    s16 divisor;
    s32 temp_x;
    s32 temp_y;
    u16 next_count;
    s32 *global83460;
    s32 one;
    s32 state;

    state = a0->state9b;
    one = 1;
    switch (state) {
    case 0:
        goto state_zero;
    case 1:
        goto state_one;
    case 2:
        goto state_two;
    default:
        goto done;
    }

state_zero:
        func_800AD4D0(a3);
        a0->state9b = (u8)(a0->state9b + 1);
        if (a3->flag28 == 0) {
            a3->flag28 = (u8)one;
        }
        if (a2->flags14 & 0x8000) {
            a0->count96 = 0;
            a0->state9b = 2;
            goto done;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        a1->dxC = (-(*(s16 *)(D_8006CCD8 + (((u16)a3->index6A >> 8) & 0xE)))) << 0xF;
        a1->dy10 = (-(*(s16 *)(D_8006CCE8 + (((u16)a3->index6A >> 8) & 0xE)))) << 0xF;
        a0->count96 = 8;
state_one:
        a1->dxC += (*(s16 *)(D_8006CCD8 + (((u16)a3->index6A >> 8) & 0xE))) << 0xA;
        a1->dy10 += (*(s16 *)(D_8006CCE8 + (((u16)a3->index6A >> 8) & 0xE))) << 0xA;
        next_count = (u16)a0->count96 - 1;
        a0->count96 = (s16)next_count;
        if ((next_count << 0x10) <= 0) {
            if (a3->flag28 == 0) {
                a3->flag28 = 1;
            }
            a0->count96 = 8;
            a0->state9b = (u8)(a0->state9b + 1);
            goto done;
        }
        goto done;
state_two:
        divisor = a0->count96;
        if (divisor != 0) {
            temp_x = (s32)a2->x24 << 6;
            temp_y = a1->x2;
            temp_y -= 0x20;
            a1->dxC = ((temp_x - temp_y) << 0xF) / divisor;
            temp_x = (s32)a2->y25 << 6;
            temp_y = a1->y6;
            temp_y -= 0x20;
            a1->dy10 = ((temp_x - temp_y) << 0xF) / a0->count96;
        }
        next_count = (u16)a0->count96 - 1;
        a0->count96 = (s16)next_count;
        if ((next_count << 0x10) <= 0) {
            a1->dz14 = 0;
            a1->dy10 = 0;
            a1->dxC = 0;
            func_800A2B04(a1, a2->x24, a2->y25);
            global83460 = D_80083460;
            if (global83460[4] == (s32)((u8 *)a3 - 0x20)) {
                global83460[4] &= 0x7FFFFFFF;
                a0->field8c = D_80171FA4;
            } else {
                a0->field8c = D_80171FA4;
            }
        }
        goto done;
done:
    return;
}
