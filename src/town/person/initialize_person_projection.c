#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

void SetFogFar(s32, s32);                /* extern */
void SetLightMatrix(void *);                      /* extern */
void SetColorMatrix(void *);                      /* extern */
void SetBackColor(s32, s32, s32);   /* extern */
void SetFarColor(s32, s32, s32);   /* extern */
void SetGeomOffset(s32, s32);            /* extern */
void SetGeomScreen(s32);                     /* extern */
extern struct S_800AB7FC_1 map_runtime_state;
/* Retail writes +0x19..+0x1B; the asset allocation extent is not established here. */
extern u8 upper_draw_context[];
extern u8 lower_draw_context[];

typedef struct S_800AB7FC_1 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_800AB7FC_1;   /* temp_global_a0 in initialize_person_projection */

/* Initialize town projection, lighting, view bounds, and color state. */
void initialize_person_projection(void) {
    GameView *view_state;
    GameWork *render_data;
    s32 screen_distance;
    S_800AB7FC_1 *scene_state;
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
    view_state->unk_078 = 0;
    view_state->unk_07C = 0;
    view_state->unk_080 = 0;
    SetFarColor(0, 0, 0);
    view_state->color_matrix_01 = -0x100;
    view_state->color_matrix_11 = -0x100;
    view_state->color_matrix_21 = -0x100;
    view_state->color_matrix_02 = 0;
    view_state->color_matrix_12 = 0;
    view_state->color_matrix_22 = 0;
    SetColorMatrix(&render_data->view.color_matrix_00);
    scene_state = (u8 *)render_data + 0x50;
    light_negative = -0x800;
    view_state->light_matrix_00 = light_negative;
    view_state->light_matrix_01 = 0x800;
    view_state->light_matrix_02 = light_negative;
    light_positive = 0x800;
    view_state->light_matrix_10 = light_positive;
    view_state->light_matrix_11 = -0x800;
    view_state->light_matrix_12 = light_positive;
    view_state->light_matrix_20 = 0;
    view_state->light_matrix_21 = 0;
    view_state->light_matrix_22 = 0;
    SetLightMatrix(scene_state);
    view_state->fog_far = 0x1000;
    SetFogFar(0x1000, view_state->projection_distance);
    scene_state = &map_runtime_state;
    if ((scene_state->unk_18 == 0xC) && (scene_state->unk_1A != 0x34)) {
        ambient_red = 0xA0;
        ambient_green = ambient_red;
        ambient_blue = ambient_red;
        view_state->color_matrix_00 = screen_distance;
        view_state->color_matrix_10 = screen_distance;
        view_state->color_matrix_20 = screen_distance;
    } else {
        ambient_red = 0xB0;
        ambient_green = ambient_red;
        ambient_blue = ambient_red;
        view_state->color_matrix_00 = 0x3C0;
        view_state->color_matrix_10 = 0x3C0;
        view_state->color_matrix_20 = 0x3C0;
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
    upper_draw_context[0x19] = 0;
    upper_draw_context[0x1A] = 0;
    upper_draw_context[0x1B] = 0;
    lower_draw_context[0x19] = 0;
    lower_draw_context[0x1A] = 0;
    lower_draw_context[0x1B] = 0;
}
