#include "common.h"

typedef struct { s32 flags; } GlobalFlags;
extern GlobalFlags D_800814A0;
typedef struct { u16 unused; s16 timer; } Work;
void decrement_timer_and_set_completion_flag(Work *work) {
    work->timer--;
    if (work->timer <= 0) {
        GlobalFlags *status = &D_800814A0;
        ((u16 *)work)[-1] |= 0x8000;
        status->flags |= 0x8000;
    }
}
