#include "common.h"
#include "sdk/libgpu.h"
#include "town/map/animation.h"
extern u8 building_upload_rect[];

extern u8 building_texture_frame_zero[];
extern u8 building_texture_frame_one[];
extern u8 building_texture_frame_two[];
extern u8 building_texture_frame_three[];
extern u16 building_palette_frame_zero[];
extern u16 D_80111F68[];
extern u16 D_80111F88[];

/* Advance the animation tick and upload the selected texture and palette frames. */
void advance_building_texture_frame(u16 *anim_tick)
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
        rect = (void *)building_upload_rect;
        upload_data = building_texture_frame_zero;
        *(u16 *)building_upload_rect = 808;
        ((u16 *)rect)[1] = 128;
        ((u16 *)rect)[2] = 8;
        ((u16 *)rect)[3] = 32;
        LoadImage(rect, upload_data);
        break;
    case 4:
    case 20:
        rect = (void *)building_upload_rect;
        upload_data = building_texture_frame_one;
        *(u16 *)building_upload_rect = 808;
        ((u16 *)rect)[1] = 128;
        ((u16 *)rect)[2] = 8;
        ((u16 *)rect)[3] = 32;
        LoadImage(rect, upload_data);
        break;
    case 8:
    case 16:
        rect = (void *)building_upload_rect;
        upload_data = building_texture_frame_two;
        *(u16 *)building_upload_rect = 808;
        ((u16 *)rect)[1] = 128;
        ((u16 *)rect)[2] = 8;
        ((u16 *)rect)[3] = 32;
        LoadImage(rect, upload_data);
        break;
    case 12:
        rect = (void *)building_upload_rect;
        upload_data = building_texture_frame_three;
        *(u16 *)building_upload_rect = 808;
        ((u16 *)rect)[1] = 128;
        ((u16 *)rect)[2] = 8;
        ((u16 *)rect)[3] = 32;
        LoadImage(rect, upload_data);
    }

    palette_phase = (s16)*anim_tick % 6;
    switch (palette_phase) {
    case 0:
        rect = (void *)building_upload_rect;
        upload_data = building_palette_frame_zero;
        *(u16 *)building_upload_rect = 16;
        ((u16 *)rect)[1] = 449;
        ((u16 *)rect)[2] = 16;
        ((u16 *)rect)[3] = 1;
        LoadImage(rect, upload_data);
        return;
    case 2:
        rect = (void *)building_upload_rect;
        upload_data = D_80111F68;
        *(u16 *)building_upload_rect = 16;
        ((u16 *)rect)[1] = 449;
        ((u16 *)rect)[2] = 16;
        ((u16 *)rect)[3] = 1;
        LoadImage(rect, upload_data);
        return;
    case 4:
        rect = (void *)building_upload_rect;
        upload_data = D_80111F88;
        *(u16 *)building_upload_rect = 16;
        ((u16 *)rect)[1] = 449;
        ((u16 *)rect)[2] = 16;
        ((u16 *)rect)[3] = 1;
        LoadImage(rect, upload_data);
    default:
        return;
    }
}
