#include "common.h"
#include "town/map.h"
#include "town/data.h"

extern u8 D_801118C8[];
extern u8 D_80111AC8[];
extern u8 D_80111CC8[];
extern u8 D_80111EE8[];
extern u8 D_80111F08[];
extern u8 D_80111F28[];

extern void LoadImage();

/* Advance the animation tick and upload the current texture and palette frames. */
void advance_building_texture_and_palette(BuildingSelectionHandlerBody *state, s32 unused, s32 upload_arg) {
    u16 next_tick;
    s16 phase;
    s32 dispatch_index;
    RECT *rect;
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
        rect = &building_upload_rect;
        building_upload_rect.x = 0x328;
        rect->y = 0x80;
        rect->w = 8;
        rect->h = 0x20;
        LoadImage(rect, building_texture_frame_zero, upload_arg);
        break;

    case 4:
    case 20:
        rect = &building_upload_rect;
        building_upload_rect.x = 0x328;
        rect->y = 0x80;
        rect->w = 8;
        rect->h = 0x20;
        LoadImage(rect, building_texture_frame_one, upload_arg);
        break;

    case 8:
    case 16:
        rect = &building_upload_rect;
        building_upload_rect.x = 0x328;
        rect->y = 0x80;
        rect->w = 8;
        rect->h = 0x20;
        LoadImage(rect, building_texture_frame_two, upload_arg);
        break;

    case 12:
        rect = &building_upload_rect;

        building_upload_rect.x = 0x328;
        rect->y = 0x80;
        rect->w = 8;
        rect->h = 0x20;
        LoadImage(rect, building_texture_frame_three, upload_arg);
        break;

    default:
        break;
    }

    phase = state->animation_tick.s % 16;
    switch (phase) {
    case 0:
        rect = &building_upload_rect;
        building_upload_rect.x = 0x330;
        rect->y = 0x80;
        rect->w = 8;
        rect->h = 0x20;
        LoadImage(rect, building_texture_backup);
        break;

    case 4:
        rect = &building_upload_rect;
        building_upload_rect.x = 0x330;
        rect->y = 0x80;
        rect->w = 8;
        rect->h = 0x20;
        LoadImage(rect, D_801118C8);
        break;

    case 8:
        tile_width = 8;
        rect = &building_upload_rect;
        building_upload_rect.x = 0x330;
        rect->y = 0x80;
        {
            s32 tile_height;
            tile_height = 0x20;
            rect->w = tile_width;
            rect->h = tile_height;
            LoadImage(rect, D_80111AC8);
        }
        break;

    case 12:
        tile_width = 8;
        rect = &building_upload_rect;

        building_upload_rect.x = 0x330;
        rect->y = 0x80;
        {
            s32 tile_height;
            tile_height = 0x20;
            rect->w = tile_width;
            rect->h = tile_height;
            LoadImage(rect, D_80111CC8);
        }
    }

    phase = state->animation_tick.s % 8;
    switch (phase) {
    case 0:
        rect = &building_upload_rect;
        building_upload_rect.x = 0;
        rect->y = 0x1FB;
        rect->w = 0x10;
        rect->h = 1;
        LoadImage(rect, building_palette_backup);
        return;

    case 2:
        rect = &building_upload_rect;
        building_upload_rect.x = 0;
        rect->y = 0x1FB;
        rect->w = 0x10;
        rect->h = 1;
        LoadImage(rect, D_80111EE8);
        return;

    case 4:
        rect = &building_upload_rect;
        building_upload_rect.x = 0;
        rect->y = 0x1FB;
        rect->w = 0x10;
        rect->h = 1;
        LoadImage(rect, D_80111F08);
        return;

    case 6:
        rect = &building_upload_rect;

        building_upload_rect.x = 0;
        rect->y = 0x1FB;
        rect->w = 0x10;
        rect->h = 1;
        LoadImage(rect, D_80111F28);
    }
}
