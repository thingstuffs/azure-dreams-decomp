#include "common.h"
#include "sdk/libgpu.h"
#include "town/map/animation.h"
#include "town/data.h"

extern u16 building_palette_frame_zero[];
extern u16 D_80111F68[];
extern u16 D_80111F88[];

/* Advance the animation tick and upload the selected texture and palette frames. */
void advance_building_texture_frame(BuildingSelectionHandlerBody *state)
{
    BuildingUploadRect *rect;
    void *upload_data;
    s32 palette_phase;
    s32 next_tick;
    s32 texture_phase;

    next_tick = state->animation_tick.u + 1;
    state->animation_tick.u = next_tick;
    if ((s16)next_tick >= 24) {
        state->animation_tick.u = 0;
    }

    texture_phase = state->animation_tick.s % 24;
    switch (texture_phase) {
    case 0:
        rect = &building_upload_rect;
        upload_data = building_texture_frame_zero;
        building_upload_rect.x = 808;
        rect->y = 128;
        rect->w = 8;
        rect->h = 32;
        LoadImage(rect, upload_data);
        break;
    case 4:
    case 20:
        rect = &building_upload_rect;
        upload_data = building_texture_frame_one;
        building_upload_rect.x = 808;
        rect->y = 128;
        rect->w = 8;
        rect->h = 32;
        LoadImage(rect, upload_data);
        break;
    case 8:
    case 16:
        rect = &building_upload_rect;
        upload_data = building_texture_frame_two;
        building_upload_rect.x = 808;
        rect->y = 128;
        rect->w = 8;
        rect->h = 32;
        LoadImage(rect, upload_data);
        break;
    case 12:
        rect = &building_upload_rect;
        upload_data = building_texture_frame_three;
        building_upload_rect.x = 808;
        rect->y = 128;
        rect->w = 8;
        rect->h = 32;
        LoadImage(rect, upload_data);
    }

    palette_phase = state->animation_tick.s % 6;
    switch (palette_phase) {
    case 0:
        rect = &building_upload_rect;
        upload_data = building_palette_frame_zero;
        building_upload_rect.x = 16;
        rect->y = 449;
        rect->w = 16;
        rect->h = 1;
        LoadImage(rect, upload_data);
        return;
    case 2:
        rect = &building_upload_rect;
        upload_data = D_80111F68;
        building_upload_rect.x = 16;
        rect->y = 449;
        rect->w = 16;
        rect->h = 1;
        LoadImage(rect, upload_data);
        return;
    case 4:
        rect = &building_upload_rect;
        upload_data = D_80111F88;
        building_upload_rect.x = 16;
        rect->y = 449;
        rect->w = 16;
        rect->h = 1;
        LoadImage(rect, upload_data);
    default:
        return;
    }
}
