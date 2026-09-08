#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void RotMatrix(void *r, void *m);
extern void ScaleMatrix(void *m, void *v);
extern void SetRotMatrix(void *m);
extern void SetTransMatrix(void *m);
extern void RotTransSV(void *v0, void *out, void *flag);
extern s32 rcos(s32);
extern s32 rsin(s32);
extern void *D_80083160[3];

/* Transforms a flipped point using local scale, rotation, and offsets, then adjusts for view angles. */
void func_8003DBD0(void *transform, void *point, void *result)
{
    register u8 *position ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    u8 *render_state;
    u8 *scratch;
    s32 view_angle_x;
    s32 view_angle_y;
    s32 view_angle_z;
    s32 angle_x;
    s32 offset_x;
    s32 offset_y;
    s32 saved_offset_x;
    s32 saved_offset_y;
    s32 transformed_x;
    s32 transformed_y;
    s32 final_angle_x;
    s32 final_angle_z;
    s32 base_angle;

    position = (u8 *)result;
    render_state = (u8 *)D_80083160;
    PushMatrix();
    scratch = (u8 *)0x1F800000;

    view_angle_x = S16_AT(render_state, 0xC4);
    view_angle_y = S16_AT(render_state, 0xC6);
    view_angle_z = S16_AT(render_state, 0xC8);
    U32_AT(scratch, 0x30) = view_angle_x;
    U32_AT(scratch, 0x34) = view_angle_y;
    U32_AT(scratch, 0x38) = view_angle_z;
    angle_x = U16_AT(transform, 0x16) - 0x400;
    U16_AT(scratch, 0x100) = angle_x - U16_AT(scratch, 0x30);
    U16_AT(scratch, 0x104) = U16_AT(render_state, 0xB8) + (U16_AT(transform, 0x1A) - U16_AT(scratch, 0x34));
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
        s32 point_x = U8_AT(point, 2);
        saved_offset_x = U16_AT(scratch, 0x108);
        ASM_KEEP_DEP_NV(point_x, saved_offset_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        S16_AT(scratch, 0x70) = -((point_x << 24) >> 24) - saved_offset_x;
    } else {
        s32 point_x = U8_AT(point, 2);
        saved_offset_x = U16_AT(scratch, 0x108);
        ASM_KEEP_DEP_NV(point_x, saved_offset_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        S16_AT(scratch, 0x70) = ((point_x << 24) >> 24) - saved_offset_x;
    }

    if ((U8_AT(point, 0) ^ U16_AT(scratch, 0x24)) & 2) {
        s32 point_y = U8_AT(point, 3);
        saved_offset_y = U16_AT(scratch, 0x10A);
        ASM_KEEP_DEP_NV(point_y, saved_offset_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        S16_AT(scratch, 0x74) = -((point_y << 24) >> 24) - saved_offset_y;
    } else {
        s32 point_y = U8_AT(point, 3);
        saved_offset_y = U16_AT(scratch, 0x10A);
        ASM_KEEP_DEP_NV(point_y, saved_offset_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        S16_AT(scratch, 0x74) = ((point_y << 24) >> 24) - saved_offset_y;
    }
    S16_AT(scratch, 0x72) = 0;
    RotTransSV((void *)((u32)scratch | 0x70), position, (void *)((u32)scratch | 0x94));

    transformed_x = U16_AT(position, 0);
    U16_AT(scratch, 0x00) = transformed_x;
    final_angle_x = S16_AT(render_state, 0xC4);
    transformed_y = U16_AT(position, 2);
    U32_AT(scratch, 0x30) = -final_angle_x;
    final_angle_z = S16_AT(render_state, 0xC8);
    base_angle = S16_AT(render_state, 0xB8);
    U16_AT(scratch, 0x02) = transformed_y;
    U32_AT(scratch, 0x38) = base_angle - final_angle_z;
    U16_AT(position, 4) += ((s32)(s16)U16_AT(scratch, 0x02) * rcos(U32_AT(scratch, 0x30))) >> 12;
    S16_AT(position, 0) = (S16_AT(scratch, 0x00) * rcos(U32_AT(scratch, 0x38))) >> 12;
    S16_AT(position, 2) = (S16_AT(scratch, 0x00) * rsin(U32_AT(scratch, 0x38))) >> 12;
    PopMatrix();
}
