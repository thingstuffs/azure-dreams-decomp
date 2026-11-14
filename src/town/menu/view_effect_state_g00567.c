/* Updates effect state from shared view values and allocates objects with randomized state. */
/* inferred-strong view_effect_state_g00567; joins CL:town/func_800A4E6C; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A4E6C. */
#include "town/menu/view_effect_state_g00567.h"
#include "shared/object_node.h"
#include "engine/window.h"
#include "town/menu.h"
#include "town/menu_callbacks_api.h"
#include "town/menu/fading_triangle_effect.h"

/*
 * Derives effect angle and intensity from the camera heading, copies camera X/Y, and spawns a
 * randomized effect whenever the countdown is reset to 15.
 */
void spawn_flickering_triangles_from_view(State *state) {

    state->field_8 = (rcos(g_game_work.view.camera_rotation.parts.viewAngle) + 0x1000) / 2;
    state->field_0 = -rcos(g_game_work.view.camera_rotation.parts.viewAngle) / 24;
    state->field_2 = ratan2(state->field_0, 160);
    state->field_4 = ((u16)g_game_work.view.camera_position.parts.camera_position_x);
    state->field_6 = ((u16)g_game_work.view.camera_position.parts.camera_position_y);

    if (--state->field_C <= 0) {
        state->field_C = 15;
        create_flickering_triangle(state);
    }
}

/* Allocates an object and initializes its randomized state. */
void *create_flickering_triangle(State *state_value)
{
    s32 offset_sample;
    s16 initial_count;
    FadingTriangleEffectBody *state;
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0x136);
    if (object == 0) {
        return 0;
    }
    object->update_callback = draw_fading_flickering_triangle;
    state = NODE_BODY(object);
    initial_count = scale_random_by_limit(0xB4) + 0x3C;
    state->ticks_left = initial_count;
    state->fade_period = initial_count;
    state->triangle_width = (scale_random_by_limit(0x28) & 0xFFFF) + 0x80;
    state->parameters = state_value;
    offset_sample = scale_random_by_limit(0x40);
    state->center_offset = offset_sample + scale_random_by_limit(0x40) - 0x40;
    state->phase_x_offset = scale_random_by_limit(0x40);
    state->phase_y_offset = scale_random_by_limit(0x40);
    return object;
}
