#include "common.h"
#include "shared/game_work.h"
#include "shared/sprite_frame_state.h"
#include "engine/graphics/sprite_scratch.h"
#include "engine/graphics.h"
#include "sdk/libgte.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))


/* Transforms a flipped point using local scale, rotation, and offsets, then adjusts for view angles. */
void transform_sprite_attachment_point(SpriteFrameState *transform, void *point, SVECTOR *result)
{
    GameWork *render_state;
    SpriteFrameState *sprite = transform;
    SpriteQuadScratch *scratch;
    s32 view_angle_x;
    s32 view_angle_y;
    s32 view_angle_z;
    s32 angle_x;
    s32 offset_x;
    s32 offset_y;
    s32 transformed_x;
    s32 transformed_y;
    s32 final_angle_x;
    s32 final_angle_z;
    s32 base_angle;

    render_state = &g_game_work;
    PushMatrix();
    scratch = SPRITE_SCRATCH;

    view_angle_x = render_state->view.camera_rotation.parts.camera_rotation_x;
    view_angle_y = render_state->view.camera_rotation.parts.camera_rotation_y;
    view_angle_z = render_state->view.camera_rotation.parts.viewAngle;
    scratch->input.vx = view_angle_x;
    scratch->input.vy = view_angle_y;
    scratch->input.vz = view_angle_z;
    angle_x = sprite->angle_x - 0x400;
    scratch->angles.vx = angle_x - (u16)scratch->input.vx;
    scratch->angles.vz = ((u16)(render_state->view.view_rotation_offset.parts.view_rotation_offset_z)) + (sprite->angle_z - (u16)scratch->input.vy);
    scratch->angles.vy = sprite->angle_y;
    offset_x = sprite->offset_x;
    scratch->matrix_D0.t[0] = offset_x;
    scratch->extent_x = offset_x;
    offset_y = sprite->offset_y;
    scratch->matrix_D0.t[2] = 0;
    scratch->matrix_D0.t[1] = offset_y;
    scratch->extent_y = offset_y;
    RotMatrix(&scratch->angles, &scratch->matrix_D0);

    scratch->input.vx = sprite->scale_x << 1;
    scratch->input.vy = sprite->scale_y << 1;
    scratch->input.vz = 0x2000;
    ScaleMatrix(&scratch->matrix_D0, &scratch->input);
    SetTransMatrix(&scratch->matrix_D0);
    SetRotMatrix(&scratch->matrix_D0);

    scratch->sprite_flags = sprite->flags;

    if ((U8_AT(point, 0) ^ scratch->sprite_flags) & 1) {
        scratch->vertices[0].vx = -S8_AT(point, 2) - scratch->extent_x;
    } else {
        scratch->vertices[0].vx = S8_AT(point, 2) - scratch->extent_x;
    }

    if ((U8_AT(point, 0) ^ scratch->sprite_flags) & 2) {
        scratch->vertices[0].vz = -S8_AT(point, 3) - scratch->extent_y;
    } else {
        scratch->vertices[0].vz = S8_AT(point, 3) - scratch->extent_y;
    }
    scratch->vertices[0].vy = 0;
    RotTransSV(&scratch->vertices[0], result, &scratch->gte_flag);

    transformed_x = (u16)result->vx;
    scratch->position.vx = transformed_x;
    final_angle_x = render_state->view.camera_rotation.parts.camera_rotation_x;
    transformed_y = (u16)result->vy;
    scratch->input.vx = -final_angle_x;
    final_angle_z = render_state->view.camera_rotation.parts.viewAngle;
    base_angle = render_state->view.view_rotation_offset.parts.view_rotation_offset_z;
    scratch->position.vy = transformed_y;
    scratch->input.vz = base_angle - final_angle_z;
    result->vz += ((s32)scratch->position.vy * rcos(scratch->input.vx)) >> 12;
    result->vx = (scratch->position.vx * rcos(scratch->input.vz)) >> 12;
    result->vy = (scratch->position.vx * rsin(scratch->input.vz)) >> 12;
    PopMatrix();
}
