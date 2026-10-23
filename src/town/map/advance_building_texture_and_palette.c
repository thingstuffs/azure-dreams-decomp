#include "common.h"

extern u16 building_upload_rect[];
extern u8 D_80110EC8[];
extern u8 D_801110C8[];
extern u8 D_801112C8[];
extern u8 D_801114C8[];
extern u8 D_801116C8[];
extern u8 D_801118C8[];
extern u8 D_80111AC8[];
extern u8 D_80111CC8[];
extern u8 D_80111EC8[];
extern u8 D_80111EE8[];
extern u8 D_80111F08[];
extern u8 D_80111F28[];

extern void LoadImage();

/* Advance the animation tick and upload the current texture and palette frames. */
void advance_building_texture_and_palette(u16 *anim_tick, s32 unused, s32 upload_arg) {
    u16 next_tick;
    s16 phase;
    s32 dispatch_index;
    s16 *rect;
    s32 tile_width;

    next_tick = *anim_tick + 1;
    *anim_tick = next_tick;
    if ((s16)next_tick >= 48) {
        *anim_tick = 0;
    }

    phase = *(s16 *)anim_tick % 24;
    dispatch_index = phase;
    switch (dispatch_index) {
    case 0:
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0x328;
        rect[1] = 0x80;
        rect[2] = 8;
        rect[3] = 0x20;
        LoadImage(rect, D_80110EC8, upload_arg);
        break;

    case 4:
    case 20:
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0x328;
        rect[1] = 0x80;
        rect[2] = 8;
        rect[3] = 0x20;
        LoadImage(rect, D_801110C8, upload_arg);
        break;

    case 8:
    case 16:
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0x328;
        rect[1] = 0x80;
        rect[2] = 8;
        rect[3] = 0x20;
        LoadImage(rect, D_801112C8, upload_arg);
        break;

    case 12:
        rect = (s16 *)building_upload_rect;

        *(s16 *)building_upload_rect = 0x328;
        rect[1] = 0x80;
        rect[2] = 8;
        rect[3] = 0x20;
        LoadImage(rect, D_801114C8, upload_arg);
        break;

    default:
        break;
    }

    phase = *(s16 *)anim_tick % 16;
    switch (phase) {
    case 0:
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0x330;
        ((s16 *)rect)[1] = 0x80;
        ((s16 *)rect)[2] = 8;
        rect[3] = 0x20;
        LoadImage(rect, D_801116C8);
        break;

    case 4:
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0x330;
        rect[1] = 0x80;
        rect[2] = 8;
        rect[3] = 0x20;
        LoadImage(rect, D_801118C8);
        break;

    case 8:
        tile_width = 8;
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0x330;
        rect[1] = 0x80;
        {
            s32 tile_height;
            tile_height = 0x20;
            rect[2] = tile_width;
            rect[3] = tile_height;
            LoadImage(rect, D_80111AC8);
        }
        break;

    case 12:
        tile_width = 8;
        rect = (s16 *)building_upload_rect;

        *(s16 *)building_upload_rect = 0x330;
        rect[1] = 0x80;
        {
            s32 tile_height;
            tile_height = 0x20;
            rect[2] = tile_width;
            rect[3] = tile_height;
            LoadImage(rect, D_80111CC8);
        }
    }

    phase = *(s16 *)anim_tick % 8;
    switch (phase) {
    case 0:
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0;
        rect[1] = 0x1FB;
        rect[2] = 0x10;
        rect[3] = 1;
        LoadImage(rect, D_80111EC8);
        return;

    case 2:
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0;
        rect[1] = 0x1FB;
        rect[2] = 0x10;
        rect[3] = 1;
        LoadImage(rect, D_80111EE8);
        return;

    case 4:
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0;
        rect[1] = 0x1FB;
        rect[2] = 0x10;
        rect[3] = 1;
        LoadImage(rect, D_80111F08);
        return;

    case 6:
        rect = (s16 *)building_upload_rect;

        *(s16 *)building_upload_rect = 0;
        rect[1] = 0x1FB;
        rect[2] = 0x10;
        rect[3] = 1;
        LoadImage(rect, D_80111F28);
    }
}
