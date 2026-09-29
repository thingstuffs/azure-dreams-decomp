#include "common.h"
extern u8 D_80111FA8[];

extern void func_800672D8(void *, void *);
extern u8 D_80110EC8[];
extern u8 D_801110C8[];
extern u8 D_801112C8[];
extern u8 D_801114C8[];
extern u16 D_80111F48[];
extern u16 D_80111F68[];
extern u16 D_80111F88[];

/* Advance the animation tick and upload the selected texture and palette frames. */
void func_800B7F8C(u16 *anim_tick)
{
    void *rect;
    void *upload_data;
    s32 palette_phase;
    s32 next_tick;
    s32 texture_phase;

    next_tick = *anim_tick + 1;
    *anim_tick = next_tick;
    if ((s16)next_tick >= 24) {
        *anim_tick = 0;
    }

    texture_phase = (s16)*anim_tick % 24;
    switch (texture_phase) {
    case 0:
        rect = (void *)D_80111FA8;
        upload_data = D_80110EC8;
        *(u16 *)D_80111FA8 = 808;
        ((u16 *)rect)[1] = 128;
        ((u16 *)rect)[2] = 8;
        ((u16 *)rect)[3] = 32;
        func_800672D8(rect, upload_data);
        break;
    case 4:
    case 20:
        rect = (void *)D_80111FA8;
        upload_data = D_801110C8;
        *(u16 *)D_80111FA8 = 808;
        ((u16 *)rect)[1] = 128;
        ((u16 *)rect)[2] = 8;
        ((u16 *)rect)[3] = 32;
        func_800672D8(rect, upload_data);
        break;
    case 8:
    case 16:
        rect = (void *)D_80111FA8;
        upload_data = D_801112C8;
        *(u16 *)D_80111FA8 = 808;
        ((u16 *)rect)[1] = 128;
        ((u16 *)rect)[2] = 8;
        ((u16 *)rect)[3] = 32;
        func_800672D8(rect, upload_data);
        break;
    case 12:
        rect = (void *)D_80111FA8;
        upload_data = D_801114C8;
        *(u16 *)D_80111FA8 = 808;
        ((u16 *)rect)[1] = 128;
        ((u16 *)rect)[2] = 8;
        ((u16 *)rect)[3] = 32;
        func_800672D8(rect, upload_data);
    }

    palette_phase = (s16)*anim_tick % 6;
    switch (palette_phase) {
    case 0:
        rect = (void *)D_80111FA8;
        upload_data = D_80111F48;
        *(u16 *)D_80111FA8 = 16;
        ((u16 *)rect)[1] = 449;
        ((u16 *)rect)[2] = 16;
        ((u16 *)rect)[3] = 1;
        func_800672D8(rect, upload_data);
        return;
    case 2:
        rect = (void *)D_80111FA8;
        upload_data = D_80111F68;
        *(u16 *)D_80111FA8 = 16;
        ((u16 *)rect)[1] = 449;
        ((u16 *)rect)[2] = 16;
        ((u16 *)rect)[3] = 1;
        func_800672D8(rect, upload_data);
        return;
    case 4:
        rect = (void *)D_80111FA8;
        upload_data = D_80111F88;
        *(u16 *)D_80111FA8 = 16;
        ((u16 *)rect)[1] = 449;
        ((u16 *)rect)[2] = 16;
        ((u16 *)rect)[3] = 1;
        func_800672D8(rect, upload_data);
    default:
        return;
    }
}
