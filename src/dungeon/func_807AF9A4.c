#include "common.h"

extern s32 rand(void);
extern void func_800F72CC(void) __attribute__((noreturn));
extern void func_8004491C(void *a0, void *a1);
extern int D_800814A0;
extern u8 D_800F6E48[];

typedef struct {
    u8 unk00[8];
    s16 state;      /* 0x08 */
    u8 unk0A[2];
    u16 counter1;   /* 0x0C */
    s8 flag_e;      /* 0x0E */
    u8 flag_f;      /* 0x0F */
    u8 buf[0x40];   /* 0x10 - 0x4F */
} S807AF9A4;

void func_807AF9A4(S807AF9A4 *a0)
{
    s16 state;
    s16 i;
    u16 counter1;
    u8 counter2;

    state = a0->state;
    if (state != 0) {
        if (state != 1) {
            func_800F72CC();
            return;
        }
        goto shared_tail;
    }

    i = 0;
    do {
        a0->buf[i] = rand() & 0x1F;
        i = i + 1;
    } while (i < 0x40);
    a0->counter1 = 0;
    a0->flag_e = 0;
    a0->buf[0x20] = 0;
    a0->flag_f = 1;
    func_8004491C((u8 *)a0 - 0x20, &D_800F6E48[0]);
    a0->state = (u16) a0->state + 1;

shared_tail:
    counter1 = a0->counter1 + 1;
    a0->counter1 = counter1;
    if ((s16) counter1 >= 0x11) {
        a0->counter1 = 0;
    }

    counter2 = a0->buf[0x20] + 1;
    a0->buf[0x20] = counter2;
    if ((s8) counter2 >= 0x41) {
        a0->buf[0x20] = 0x40;
        a0->flag_e = 1;
    }

    if (a0->flag_f == 0) {
        *(u16 *)((u8 *)a0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
