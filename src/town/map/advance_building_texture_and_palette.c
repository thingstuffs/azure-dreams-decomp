#include "common.h"
#include "town/map.h"

extern u16 building_upload_rect[];
extern u8 building_texture_frame_zero[];
extern u8 building_texture_frame_one[];
extern u8 building_texture_frame_two[];
extern u8 building_texture_frame_three[];
extern u8 building_texture_backup[];
extern u8 D_801118C8[];
extern u8 D_80111AC8[];
extern u8 D_80111CC8[];
extern u8 building_palette_backup[];
extern u8 D_80111EE8[];
extern u8 D_80111F08[];
extern u8 D_80111F28[];

extern void LoadImage();

/* Advance the animation tick and upload the current texture and palette frames. */
void advance_building_texture_and_palette(BuildingSelectionHandlerBody *state, s32 unused, s32 upload_arg) {
    u16 next_tick;
    s16 phase;
    s32 dispatch_index;
    s16 *rect;
    s32 tile_width;

    next_tick = state->animation_tick.u + 1;
    state->animation_tick.u = next_tick;
    if ((s16)next_tick >= 48) {
        state->animation_tick.u = 0;
    }

    phase = state->animation_tick.s % 24;
    dispatch_index = phase;
    switch (dispatch_index) {
    case 0:
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0x328;
        rect[1] = 0x80;
        rect[2] = 8;
        rect[3] = 0x20;
        LoadImage(rect, building_texture_frame_zero, upload_arg);
        break;

    case 4:
    case 20:
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0x328;
        rect[1] = 0x80;
        rect[2] = 8;
        rect[3] = 0x20;
        LoadImage(rect, building_texture_frame_one, upload_arg);
        break;

    case 8:
    case 16:
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0x328;
        rect[1] = 0x80;
        rect[2] = 8;
        rect[3] = 0x20;
        LoadImage(rect, building_texture_frame_two, upload_arg);
        break;

    case 12:
        rect = (s16 *)building_upload_rect;

        *(s16 *)building_upload_rect = 0x328;
        rect[1] = 0x80;
        rect[2] = 8;
        rect[3] = 0x20;
        LoadImage(rect, building_texture_frame_three, upload_arg);
        break;

    default:
        break;
    }

    phase = state->animation_tick.s % 16;
    switch (phase) {
    case 0:
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0x330;
        rect[1] = 0x80;
        rect[2] = 8;
        rect[3] = 0x20;
        LoadImage(rect, building_texture_backup);
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

    phase = state->animation_tick.s % 8;
    switch (phase) {
    case 0:
        rect = (s16 *)building_upload_rect;
        *(s16 *)building_upload_rect = 0;
        rect[1] = 0x1FB;
        rect[2] = 0x10;
        rect[3] = 1;
        LoadImage(rect, building_palette_backup);
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
