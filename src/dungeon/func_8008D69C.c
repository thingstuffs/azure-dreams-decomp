#include "common.h"
#include "shared/game_work.h"

extern s32 D_8008ACDC;

/* Waits for a countdown or global state change before resetting the object's handler. */
void func_80092DFC(void *object) {
    GameWork *shared_data = &gameWork;
    u8 state = *(u8 *)((u8 *)object + 0x9B);
    u16 timer;

    switch (state) {
    case 0:
        *(u16 *)((u8 *)object + 0x96) = 0x10;
        (*(u8 *)((u8 *)object + 0x9B))++;
        break;
    case 1:
        timer = *(u16 *)((u8 *)object + 0x96) - 1;
        *(u16 *)((u8 *)object + 0x96) = timer;
        if ((s16)timer >= 0) {
            if (((s32)shared_data->unk_010) == 0) {
                return;
            }
            if (*(s32 *)0x80012090 == state) {
                return;
            }
        }
        *(s32 *)((u8 *)object + 0x124) = 0;
        *(void **)((u8 *)object + 0x8C) = &D_8008ACDC;
        break;
    }
}
