#include "common.h"

typedef struct {
    u8 pad_00[0x6C];
    u16 count;
    u8 pad_6E[0x1A];
    s16 target_x;
    s16 target_y;
} Work;

typedef struct {
    s32 x;
    s32 y;
    u16 pad_08;
    u16 angle;
} Position;

extern u16 func_800C2B38(void *arg0);
extern void func_800C4174(void *arg0, void *arg1, s32 arg2);
extern void func_800C40A4(void) __attribute__((noreturn));

void func_800C3FFC(void *arg0, void *arg1, s32 arg2) {
    Position *pos;
    Work *work;
    u16 temp_v0;
    s32 remaining;

    work = arg0;
    pos = arg1;
    temp_v0 = work->count - 1;
    work->count = temp_v0;
    remaining = (s16)temp_v0;
    if (remaining <= 0) {
        pos->x = work->target_x << 16;
        pos->y = work->target_y << 16;
        func_800C4174(work, pos, arg2);
        func_800C40A4();
        return;
    }

    {
        s32 value;

        value = pos->x;
        pos->x = value +
            ((work->target_x << 16) - value) / remaining;
    }
    {
        s32 value_y;

        value_y = pos->y;
        *(volatile s32 *)&pos->y = value_y +
            ((work->target_y << 16) - value_y) / (s16)work->count;
    }

    {
        u16 angle;

        angle = *(volatile u16 *)&pos->angle;
        ASM_USE(arg1);
        pos->angle = angle - 0x40;
    }
    pos->angle = func_800C2B38(pos);
}
