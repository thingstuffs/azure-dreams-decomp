#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "dungeon/menu.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "engine/graphics/sprite_scratch.h"
#include "sdk/libgte.h"

extern M2C_UNK map_marker_sprite_source;

/* Creates an object at transformed coordinates and initializes its rendering and state. */
void *create_map_marker(s32 x, s32 y, s32 initial_value, s32 update_param, s32 mode) {
    s32 alloc_flags;
    ObjectPosition *position;
    ObjectNodeHeader *object;
    SpriteFrameState *render_data;
    MapMarkerRevealBody *state;
    SpriteQuadScratch *scratchpad;
    MapGrid *view_config;
    u8 *camera_config;

    alloc_flags = 2;
    view_config = &g_game_work.map;
    camera_config = (u8 *)view_config - 0x1C4;
    scratchpad = SPRITE_SCRATCH;
    if (mode != 0) {
        alloc_flags = 0x202;
    }
    object = allocate_flagged_object_node(alloc_flags);
    if (object != NULL) {
        position = *(void **)((u8 *)object + 8);
        object->update_callback = &update_map_marker_reveal;
        scratchpad->rotated[0].vx = 0;
        scratchpad->rotated[0].vy = 0;
        scratchpad->input.vy = 0x1800;
        scratchpad->input.vx = 0x1800;
        scratchpad->input.vz = 0;
        scratchpad->rotated[0].vz = *(u16 *)(camera_config + 0xB0);
        RotMatrix(&SPRITE_SCRATCH->rotated[0], &SPRITE_SCRATCH->matrix_D0);
        ScaleMatrix(&SPRITE_SCRATCH->matrix_D0, &SPRITE_SCRATCH->input);
        scratchpad->matrix_D0.t[0] = 0;
        scratchpad->matrix_D0.t[1] = 0;
        scratchpad->matrix_D0.t[2] = 0;
        SetRotMatrix(&SPRITE_SCRATCH->matrix_D0);
        SetTransMatrix(&SPRITE_SCRATCH->matrix_D0);
        scratchpad->vertices[0].vz = 0;
        scratchpad->vertices[0].vx = x - ((s32)(1 << view_config->shiftX) / 2);
        scratchpad->vertices[0].vy = y - ((s32)(1 << view_config->shiftY) / 2);
        RotTransPers(&SPRITE_SCRATCH->vertices[0], (void *)0x1F8000F0,
                      &SPRITE_SCRATCH->depth_cue, &SPRITE_SCRATCH->gte_flag);
        *(u16 *)((u8 *)position + 2) = scratchpad->projected_vertices[0].x;
        position->y.w.i = scratchpad->projected_vertices[0].y;
        render_data = object->sprite;
        render_data->flags = 0xC;
        render_data->source = &map_marker_sprite_source;
        render_data->scale_y = 0x2000;
        render_data->scale_x = 0x2000;
        state = NODE_BODY(object);
        state->ticks_left = 8;
        state->color.word = initial_value;
        state->floor_flags = update_param;
        state->mode = mode;
        if (mode == 0) {
            dungeon_floor_flags |= 0x40000;
        }
    }
    return object;
}
