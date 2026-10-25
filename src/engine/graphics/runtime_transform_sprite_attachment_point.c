#include "common.h"
#include "shared/game_work.h"
#include "engine/graphics.h"
#include "sdk/libgte.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void RotTransSV(void *v0, void *out, void *flag);

/* Transforms a flipped point using local scale, rotation, and offsets, then adjusts for view angles. */
void runtime_transform_sprite_attachment_point(void *transform, void *point, void *result)
{
    GameWork *render_state;
    u8 *scratch;
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
    scratch = (u8 *)0x1F800000;

    view_angle_x = render_state->view.camera_rotation.parts.camera_rotation_x;
    view_angle_y = render_state->view.camera_rotation.parts.camera_rotation_y;
    view_angle_z = render_state->view.camera_rotation.parts.viewAngle;
    U32_AT(scratch, 0x30) = view_angle_x;
    U32_AT(scratch, 0x34) = view_angle_y;
    U32_AT(scratch, 0x38) = view_angle_z;
    angle_x = U16_AT(transform, 0x16) - 0x400;
    U16_AT(scratch, 0x100) = angle_x - U16_AT(scratch, 0x30);
    U16_AT(scratch, 0x104) = *(u16 *)&render_state->view.view_rotation_offset.parts.view_rotation_offset_z + (U16_AT(transform, 0x1A) - U16_AT(scratch, 0x34));
    U16_AT(scratch, 0x102) = U16_AT(transform, 0x18);
    offset_x = U16_AT(transform, 0x20);
    U32_AT(scratch, 0xE4) = offset_x;
    U16_AT(scratch, 0x108) = offset_x;
    offset_y = U16_AT(transform, 0x22);
    U32_AT(scratch, 0xEC) = 0;
    U32_AT(scratch, 0xE8) = offset_y;
    U16_AT(scratch, 0x10A) = offset_y;
    RotMatrix((void *)0x1F800100, (void *)0x1F8000D0);

    U32_AT(scratch, 0x30) = U16_AT(transform, 0x1C) << 1;
    U32_AT(scratch, 0x34) = U16_AT(transform, 0x1E) << 1;
    U32_AT(scratch, 0x38) = 0x2000;
    ScaleMatrix((void *)0x1F8000D0, (void *)0x1F800030);
    SetTransMatrix((void *)0x1F8000D0);
    SetRotMatrix((void *)0x1F8000D0);

    U16_AT(scratch, 0x24) = U16_AT(transform, 0x14);

    if ((U8_AT(point, 0) ^ U16_AT(scratch, 0x24)) & 1) {
        S16_AT(scratch, 0x70) = -S8_AT(point, 2) - U16_AT(scratch, 0x108);
    } else {
        S16_AT(scratch, 0x70) = S8_AT(point, 2) - U16_AT(scratch, 0x108);
    }

    if ((U8_AT(point, 0) ^ U16_AT(scratch, 0x24)) & 2) {
        S16_AT(scratch, 0x74) = -S8_AT(point, 3) - U16_AT(scratch, 0x10A);
    } else {
        S16_AT(scratch, 0x74) = S8_AT(point, 3) - U16_AT(scratch, 0x10A);
    }
    S16_AT(scratch, 0x72) = 0;
    RotTransSV(scratch + 0x70, result, scratch + 0x94);

    transformed_x = U16_AT(((u8 *)result), 0);
    U16_AT(scratch, 0x00) = transformed_x;
    final_angle_x = render_state->view.camera_rotation.parts.camera_rotation_x;
    transformed_y = U16_AT(((u8 *)result), 2);
    U32_AT(scratch, 0x30) = -final_angle_x;
    final_angle_z = render_state->view.camera_rotation.parts.viewAngle;
    base_angle = render_state->view.view_rotation_offset.parts.view_rotation_offset_z;
    U16_AT(scratch, 0x02) = transformed_y;
    U32_AT(scratch, 0x38) = base_angle - final_angle_z;
    U16_AT(((u8 *)result), 4) += ((s32)(s16)U16_AT(scratch, 0x02) * rcos(U32_AT(scratch, 0x30))) >> 12;
    S16_AT(((u8 *)result), 0) = (S16_AT(scratch, 0x00) * rcos(U32_AT(scratch, 0x38))) >> 12;
    S16_AT(((u8 *)result), 2) = (S16_AT(scratch, 0x00) * rsin(U32_AT(scratch, 0x38))) >> 12;
    PopMatrix();
}
