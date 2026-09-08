#include "common.h"

typedef struct {
    u8 pad_00[0xA];
    u16 count;
    u8 pad_0C[0x2A];
    s16 target_x;
    s16 target_y;
} Work;

typedef struct {
    s32 x;
    s32 y;
    u16 pad_08;
    u16 angle;
} Position;

extern s16 func_800C2AE8(void *arg0);
extern void func_80098928(void *arg0, void *arg1, s32 arg2);

void func_80099C18(void *arg0, void *arg1, s32 arg2) {
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
        func_80098928(work, pos, arg2);
        ASM_USE(arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
        pos->angle = func_800C2AE8(pos);
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

    ASM_USE(arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    pos->angle = func_800C2AE8(pos);
}
