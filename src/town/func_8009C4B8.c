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

/* Advance the position toward its target and update its angle. */
void func_80099C18(void *work_data, void *position_data, s32 context) {
    Position *pos;
    Work *work;
    u16 steps_left;
    s32 remaining;

    work = work_data;
    pos = position_data;
    steps_left = work->count - 1;
    work->count = steps_left;
    remaining = (s16)steps_left;
    if (remaining <= 0) {
        pos->x = work->target_x << 16;
        pos->y = work->target_y << 16;
        func_80098928(work, pos, context);
        pos->angle = func_800C2AE8(pos);
        return;
    }

    {
        s32 x;

        x = pos->x;
        pos->x = x +
            ((work->target_x << 16) - x) / remaining;
    }
    {
        s32 y;

        y = pos->y;
        *(volatile s32 *)&pos->y = y +
            ((work->target_y << 16) - y) / (s16)work->count;
    }

    ASM_USE(position_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    pos->angle = func_800C2AE8(pos);
}
