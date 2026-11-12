#include "common.h"
#include "sdk/libgpu.h"
#include "town/map/animation.h"
#include "town/data.h"

/* Advance the animation tick and upload the selected frame to VRAM. */
void advance_building_animation_frame(BuildingSelectionHandlerBody *state) {
    u16 next_tick;
    s32 tick_index;
    RECT *rect;

    next_tick = state->animation_tick.u + 1;
    state->animation_tick.u = next_tick;
    if ((s16)next_tick >= 24) {
        state->animation_tick.u = 0;
    }

    tick_index = state->animation_tick.s % 24;
    switch (tick_index) {
    case 0:
        rect = &building_upload_rect;
        building_upload_rect.x = 808;
        rect->y = 128;
        rect->w = 8;
        rect->h = 32;
        LoadImage(rect, building_texture_frame_zero);
        return;

    case 4:
    case 20:
        rect = &building_upload_rect;
        building_upload_rect.x = 808;
        rect->y = 128;
        rect->w = 8;
        rect->h = 32;
        LoadImage(rect, building_texture_frame_one);
        return;

    case 8:
    case 16:
        rect = &building_upload_rect;
        building_upload_rect.x = 808;
        rect->y = 128;
        rect->w = 8;
        rect->h = 32;
        LoadImage(rect, building_texture_frame_two);
        return;

    case 12:
        rect = &building_upload_rect;

        building_upload_rect.x = 808;
        rect->y = 128;
        rect->w = 8;
        rect->h = 32;
        LoadImage(rect, building_texture_frame_three);
    }
}
