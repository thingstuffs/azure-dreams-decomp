#include "common.h"

typedef struct {
    s32 pad[3];
} StateHandler;

extern s32 func_800AB030();
extern StateHandler D_800AB4A8;
extern StateHandler D_800AB708;

void func_800AB408(void *arg0, void *arg1) {
    u16 timer;

    if (*(s16 *)((s8 *)arg0 + 0x90) < 100) {
        *(StateHandler **)((s8 *)arg0 + 0x50) = &D_800AB708;
    }
    *(u16 *)((s8 *)arg1 + 2) = *(u16 *)((s8 *)arg1 + 0xE);
    *(u16 *)((s8 *)arg1 + 6) = *(u16 *)((s8 *)arg1 + 0x12);
    *(s16 *)((s8 *)arg1 + 0xA) = *(u16 *)((s8 *)arg1 + 0x16) + func_800AB030(arg0);
    timer = *(u16 *)((s8 *)arg0 + 0x6C) - 1;
    *(u16 *)((s8 *)arg0 + 0x6C) = timer;
    if ((s16)timer < 0) {
        *(StateHandler **)((s8 *)arg0 + 0x50) = &D_800AB4A8;
        *(u16 *)((s8 *)arg0 + 0x6C) = 10;
    }
}
