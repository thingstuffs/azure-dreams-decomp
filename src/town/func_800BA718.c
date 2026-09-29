#include "common.h"

extern u16 D_80111FA8[];
extern u8 D_80110EC8[];
extern u8 D_801110C8[];
extern u8 D_801112C8[];
extern u8 D_801114C8[];

extern void LoadImage(void *, void *);

/* Advance the animation tick and upload the selected frame to VRAM. */
void func_800B7E78(u16 *frame_tick) {
    u16 next_tick;
    s32 tick_index;
    void *rect;

    next_tick = *frame_tick + 1;
    *frame_tick = next_tick;
    if ((s16)next_tick >= 24) {
        *frame_tick = 0;
    }

    tick_index = (s16)*frame_tick % 24;
    switch (tick_index) {
    case 0:
        rect = (void *)D_80111FA8;
        (*D_80111FA8) = 808;
        ((u16 *)rect)[1] = 128;
        ((u16 *)rect)[2] = 8;
        ((u16 *)rect)[3] = 32;
        LoadImage(rect, D_80110EC8);
        return;

    case 4:
    case 20:
        rect = (void *)D_80111FA8;
        (*D_80111FA8) = 808;
        ((u16 *)rect)[1] = 128;
        ((u16 *)rect)[2] = 8;
        ((u16 *)rect)[3] = 32;
        LoadImage(rect, D_801110C8);
        return;

    case 8:
    case 16:
        rect = (void *)D_80111FA8;
        (*D_80111FA8) = 808;
        ((u16 *)rect)[1] = 128;
        ((u16 *)rect)[2] = 8;
        ((u16 *)rect)[3] = 32;
        LoadImage(rect, D_801112C8);
        return;

    case 12:
        rect = (void *)D_80111FA8;

        (*D_80111FA8) = 808;
        ((u16 *)rect)[1] = 128;
        ((u16 *)rect)[2] = 8;
        ((u16 *)rect)[3] = 32;
        LoadImage(rect, D_801114C8);
    }
}
