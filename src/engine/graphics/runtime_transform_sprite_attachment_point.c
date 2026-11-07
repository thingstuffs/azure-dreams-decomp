#include "common.h"
#include "shared/game_work.h"
#include "shared/sprite_frame_state.h"
#include "engine/graphics/sprite_scratch.h"
#include "engine/graphics.h"
#include "sdk/libgte.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))


/* Transforms a flipped point using local scale, rotation, and offsets, then adjusts for view angles. */
void runtime_transform_sprite_attachment_point(void *transform, void *point, void *result)
{
    GameWork *render_state;
    SpriteFrameState *sprite = transform;
    SpriteAttachmentScratch *scratch;
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
    scratch = (SpriteAttachmentScratch *)0x1F800000;

    view_angle_x = render_state->view.camera_rotation.parts.camera_rotation_x;
    view_angle_y = render_state->view.camera_rotation.parts.camera_rotation_y;
    view_angle_z = render_state->view.camera_rotation.parts.viewAngle;
    scratch->input_x = view_angle_x;
    scratch->input_y = view_angle_y;
    scratch->input_z = view_angle_z;
    angle_x = sprite->angle_x - 0x400;
    scratch->angle_x = angle_x - (u16)scratch->input_x;
    scratch->angle_z = ((u16)(render_state->view.view_rotation_offset.parts.view_rotation_offset_z)) + (sprite->angle_z - (u16)scratch->input_y);
    scratch->angle_y = sprite->angle_y;
    offset_x = sprite->offset_x;
    scratch->local_matrix.t[0] = offset_x;
    scratch->extent_x = offset_x;
    offset_y = sprite->offset_y;
    scratch->local_matrix.t[2] = 0;
    scratch->local_matrix.t[1] = offset_y;
    scratch->extent_y = offset_y;
    RotMatrix((void *)0x1F800100, (void *)0x1F8000D0);

    scratch->input_x = sprite->scale_x << 1;
    scratch->input_y = sprite->scale_y << 1;
    scratch->input_z = 0x2000;
    ScaleMatrix((void *)0x1F8000D0, (void *)0x1F800030);
    SetTransMatrix((void *)0x1F8000D0);
    SetRotMatrix((void *)0x1F8000D0);

    scratch->sprite_flags = sprite->flags;

    if ((U8_AT(point, 0) ^ scratch->sprite_flags) & 1) {
        scratch->point_x = -S8_AT(point, 2) - scratch->extent_x;
    } else {
        scratch->point_x = S8_AT(point, 2) - scratch->extent_x;
    }

    if ((U8_AT(point, 0) ^ scratch->sprite_flags) & 2) {
        scratch->point_y = -S8_AT(point, 3) - scratch->extent_y;
    } else {
        scratch->point_y = S8_AT(point, 3) - scratch->extent_y;
    }
    scratch->point_z = 0;
    RotTransSV(&scratch->point_x, result, &scratch->transform_flag);

    transformed_x = U16_AT(((u8 *)result), 0);
    scratch->transformed_x = transformed_x;
    final_angle_x = render_state->view.camera_rotation.parts.camera_rotation_x;
    transformed_y = U16_AT(((u8 *)result), 2);
    scratch->input_x = -final_angle_x;
    final_angle_z = render_state->view.camera_rotation.parts.viewAngle;
    base_angle = render_state->view.view_rotation_offset.parts.view_rotation_offset_z;
    scratch->transformed_y = transformed_y;
    scratch->input_z = base_angle - final_angle_z;
    U16_AT(((u8 *)result), 4) += ((s32)(s16)scratch->transformed_y * rcos(scratch->input_x)) >> 12;
    S16_AT(((u8 *)result), 0) = ((s16)scratch->transformed_x * rcos(scratch->input_z)) >> 12;
    S16_AT(((u8 *)result), 2) = ((s16)scratch->transformed_x * rsin(scratch->input_z)) >> 12;
    PopMatrix();
}
