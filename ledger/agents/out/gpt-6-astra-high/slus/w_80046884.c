#include "common.h"

typedef struct RectU16_80046884 {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} RectU16_80046884;

typedef struct UVec4_80046884 {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} UVec4_80046884;

typedef struct SVec4_80046884 {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} SVec4_80046884;

typedef struct Geometry_80046884 {
    SVec4_80046884 vectors[6];
} Geometry_80046884;

typedef struct GlobalGeometry_80046884 {
    u8 pad0[0xAC];
    u16 base_x;
    u16 base_y;
    u16 base_z;
    u8 padB2[0xC8 - 0xB2];
    s16 angle;
} GlobalGeometry_80046884;

extern GlobalGeometry_80046884 D_80083160;
extern s32 ReadGeomScreen(void);
extern void func_80046A5C(UVec4_80046884 *, SVec4_80046884 *);
extern s16 func_80046AFC(
    SVec4_80046884 *, SVec4_80046884 *, SVec4_80046884 *, s32);
extern s32 rsin(s32);
extern s32 rcos(s32);

/* Builds a closed outline from a screen rectangle, with a rotated square as fallback. */
void func_80046884(
    RectU16_80046884 *rect, Geometry_80046884 *geometry, s32 depth)
{
    UVec4_80046884 corners[4];
    SVec4_80046884 transformed_corners[4];
    s32 screen_origin[2];
    UVec4_80046884 screen_point;
    SVec4_80046884 center;
    GlobalGeometry_80046884 *view_geometry;
    UVec4_80046884 *corner;
    SVec4_80046884 *transformed_corner;
    SVec4_80046884 *output_corner;
    s32 corner_index;
    s32 angle;
    s32 cos_angle;
    s32 sin_angle;
    s32 use_fallback;
    u16 left;
    u16 right;
    u16 top;
    u16 bottom;

    left = rect->x;
    use_fallback = 0;
    corners[3].x = left;
    corners[0].x = left;

    right = rect->x + rect->w;
    corner_index = 3;
    corners[2].x = right;
    corners[1].x = right;

    top = rect->y;
    transformed_corner = &transformed_corners[3];
    corners[1].y = top;
    corners[0].y = top;

    bottom = rect->y + rect->h;
    corner = &corners[3];
    screen_origin[0] = 0;
    screen_origin[1] = 0;
    corners[2].y = bottom;
    corners[3].y = bottom;

    view_geometry = &D_80083160;
    corners[0].z = corners[1].z = corners[2].z = corners[3].z =
        ReadGeomScreen();

    func_80046A5C(
        (UVec4_80046884 *)screen_origin,
        (SVec4_80046884 *)&geometry->vectors[5]);

    output_corner = &geometry->vectors[3];
project_corners:
    func_80046A5C(corner, transformed_corner);
    if (func_80046AFC(
            &geometry->vectors[5], transformed_corner, output_corner, (s16)depth)) {
        use_fallback = 1;
    }
    output_corner--;
    transformed_corner--;
    corner_index--;
    corner--;
    if (corner_index >= 0) {
        goto project_corners;
    }

    ASM_USE(use_fallback);   /* MATCH pin: slus-diff */
    if (use_fallback != 0) {
        angle = view_geometry->angle + 0x600;
        screen_point.x = view_geometry->base_x;
        screen_point.y = view_geometry->base_y;
        screen_point.z = view_geometry->base_z;
        func_80046A5C(&screen_point, &center);

        for (corner_index = 3; corner_index >= 0; corner_index--) {
            cos_angle = rcos(angle);
            sin_angle = rsin(angle);
            angle += 0x400;
            geometry->vectors[corner_index].x =
                center.x + (cos_angle >> 3) + (cos_angle >> 4);
            geometry->vectors[corner_index].y =
                center.y + (sin_angle >> 3) + (sin_angle >> 4);
            geometry->vectors[corner_index].z = center.z;
        }
    }

    geometry->vectors[4].x = geometry->vectors[0].x;
    geometry->vectors[4].y = geometry->vectors[0].y;
    geometry->vectors[4].z = geometry->vectors[0].z;
}
