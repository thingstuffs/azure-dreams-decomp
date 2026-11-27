#include "slus/map_state.h"
#include "common.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "sdk/libgte.h"
#include "town/person.h"

/* Retail writes +0x19..+0x1B; the asset allocation extent is not established here. */
extern u8 lower_draw_context[];

/* Initialize town projection, lighting, view bounds, and color state. */
void initialize_person_projection(void) {
    GameView *view_state;
    GameWork *render_data;
    s32 screen_distance;
    s32 light_negative;
    s32 light_positive;
    s32 ambient_red;
    s32 ambient_green;
    s32 ambient_blue;

    render_data = &g_game_work;
    view_state = &render_data->view;
    screen_distance = 0x200;
    view_state->projection_distance = screen_distance;
    SetGeomScreen(screen_distance);
    view_state->far_color_r = 0;
    view_state->far_color_g = 0;
    view_state->far_color_b = 0;
    SetFarColor(0, 0, 0);
    view_state->color_matrix.m[0][1] = -0x100;
    view_state->color_matrix.m[1][1] = -0x100;
    view_state->color_matrix.m[2][1] = -0x100;
    view_state->color_matrix.m[0][2] = 0;
    view_state->color_matrix.m[1][2] = 0;
    view_state->color_matrix.m[2][2] = 0;
    SetColorMatrix(&render_data->view.color_matrix);
    light_negative = -0x800;
    view_state->light_matrix.m[0][0] = light_negative;
    view_state->light_matrix.m[0][1] = 0x800;
    view_state->light_matrix.m[0][2] = light_negative;
    light_positive = 0x800;
    view_state->light_matrix.m[1][0] = light_positive;
    view_state->light_matrix.m[1][1] = -0x800;
    view_state->light_matrix.m[1][2] = light_positive;
    view_state->light_matrix.m[2][0] = 0;
    view_state->light_matrix.m[2][1] = 0;
    view_state->light_matrix.m[2][2] = 0;
    SetLightMatrix(&view_state->light_matrix);
    view_state->fog_far = 0x1000;
    SetFogFar(0x1000, view_state->projection_distance);
    if ((map_runtime_state.scene_selector == 0xC) && (map_runtime_state.map_index != 0x34)) {
        ambient_red = 0xA0;
        ambient_green = ambient_red;
        ambient_blue = ambient_red;
        view_state->color_matrix.m[0][0] = screen_distance;
        view_state->color_matrix.m[1][0] = screen_distance;
        view_state->color_matrix.m[2][0] = screen_distance;
    } else {
        ambient_red = 0xB0;
        ambient_green = ambient_red;
        ambient_blue = ambient_red;
        view_state->color_matrix.m[0][0] = 0x3C0;
        view_state->color_matrix.m[1][0] = 0x3C0;
        view_state->color_matrix.m[2][0] = 0x3C0;
    }
    SetBackColor(ambient_red, ambient_green, ambient_blue);
    SetGeomOffset(0xA0, 0x78);
    render_data->view.clip_x = -0xBC;
    render_data->view.clip_y = -0x88;
    render_data->view.clip_width = 0x172;
    render_data->view.clip_height = 0x19A;
    view_state->tint.parts.tint_r = 0x80;
    view_state->tint.parts.tint_g = 0x80;
    view_state->tint.parts.tint_b = 0x80;
    upper_draw_context[0].draw.r0 = 0;
    upper_draw_context[0].draw.g0 = 0;
    upper_draw_context[0].draw.b0 = 0;
    lower_draw_context[0x19] = 0;
    lower_draw_context[0x1A] = 0;
    lower_draw_context[0x1B] = 0;
}
