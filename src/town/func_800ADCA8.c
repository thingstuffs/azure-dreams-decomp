#include "common.h"

typedef struct {
    s32 pad[3];
} StateHandler;

extern s32 func_800AB030();
extern StateHandler D_800AB4A8;
extern StateHandler D_800AB708;

/* Updates coordinates and selects the state handler based on the threshold and timer. */
void func_800AB408(void *state, void *coords) {
    u16 timer;

    if (*(s16 *)((s8 *)state + 0x90) < 100) {
        *(StateHandler **)((s8 *)state + 0x50) = &D_800AB708;
    }
    *(u16 *)((s8 *)coords + 2) = *(u16 *)((s8 *)coords + 0xE);
    *(u16 *)((s8 *)coords + 6) = *(u16 *)((s8 *)coords + 0x12);
    *(s16 *)((s8 *)coords + 0xA) = *(u16 *)((s8 *)coords + 0x16) + func_800AB030(state);
    timer = *(u16 *)((s8 *)state + 0x6C) - 1;
    *(u16 *)((s8 *)state + 0x6C) = timer;
    if ((s16)timer < 0) {
        *(StateHandler **)((s8 *)state + 0x50) = &D_800AB4A8;
        *(u16 *)((s8 *)state + 0x6C) = 10;
    }
}
