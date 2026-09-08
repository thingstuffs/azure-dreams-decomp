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

/* Initializes random buffer data and advances the cycle and completion counters. */
void func_807AF9A4(S807AF9A4 *data)
{
    s16 state;
    s16 buf_index;
    u16 cycle_count;
    u8 progress_count;

    state = data->state;
    if (state != 0) {
        if (state != 1) {
            func_800F72CC();
            return;
        }
        goto update_counters;
    }

    buf_index = 0;
    do {
        data->buf[buf_index] = rand() & 0x1F;
        buf_index = buf_index + 1;
    } while (buf_index < 0x40);
    data->counter1 = 0;
    data->flag_e = 0;
    data->buf[0x20] = 0;
    data->flag_f = 1;
    func_8004491C((u8 *)data - 0x20, &D_800F6E48[0]);
    data->state = (u16) data->state + 1;

update_counters:
    cycle_count = data->counter1 + 1;
    data->counter1 = cycle_count;
    if ((s16) cycle_count >= 0x11) {
        data->counter1 = 0;
    }

    progress_count = data->buf[0x20] + 1;
    data->buf[0x20] = progress_count;
    if ((s8) progress_count >= 0x41) {
        data->buf[0x20] = 0x40;
        data->flag_e = 1;
    }

    if (data->flag_f == 0) {
        *(u16 *)((u8 *)data - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
