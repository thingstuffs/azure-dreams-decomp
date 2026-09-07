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

void func_80046884(
    RectU16_80046884 *rect, Geometry_80046884 *geometry, s32 depth)
{
    UVec4_80046884 corners[4];
    SVec4_80046884 transformed[4];
    s32 origin[2];
    UVec4_80046884 screen_point;
    SVec4_80046884 center;
    s32 hit;
    GlobalGeometry_80046884 *global;
    UVec4_80046884 *corner;
    SVec4_80046884 *transformed_corner;
    SVec4_80046884 *output;
    s32 i;
    s32 angle;
    s32 x_offset;
    s32 y_offset;
    s32 hits;
    u16 left;
    u16 right;
    u16 top;
    u16 bottom;

    left = rect->x;
    hits = 0;
    hit = hits;
    corners[3].x = left;
    corners[0].x = left;

    right = rect->x + rect->w;
    i = 3;
    corners[2].x = right;
    corners[1].x = right;

    top = rect->y;
    transformed_corner = &transformed[3];
    corners[1].y = top;
    corners[0].y = top;

    bottom = rect->y + rect->h;
    corner = &corners[3];
    origin[0] = 0;
    origin[1] = 0;
    corners[2].y = bottom;
    corners[3].y = bottom;

    global = &D_80083160;
    corners[0].z = corners[1].z = corners[2].z = corners[3].z =
        ReadGeomScreen();

    func_80046A5C(
        (UVec4_80046884 *)origin,
        (SVec4_80046884 *)&geometry->vectors[5]);

    output = &geometry->vectors[3];
first_loop:
    func_80046A5C(corner, transformed_corner);
    if (func_80046AFC(
            &geometry->vectors[5], transformed_corner, output, (s16)depth)) {
        hit = 1;
        hits |= hit;
    }
    output--;
    transformed_corner--;
    i--;
    corner--;
    if (i >= 0) {
        goto first_loop;
    }

    if (hits != 0) {
        angle = global->angle + 0x600;
        screen_point.x = global->base_x;
        screen_point.y = global->base_y;
        screen_point.z = global->base_z;
        func_80046A5C(&screen_point, &center);

        for (i = 3; i >= 0; i--) {
            x_offset = rcos(angle);
            y_offset = rsin(angle);
            angle += 0x400;
            geometry->vectors[i].x =
                center.x + (x_offset >> 3) + (x_offset >> 4);
            geometry->vectors[i].y =
                center.y + (y_offset >> 3) + (y_offset >> 4);
            geometry->vectors[i].z = center.z;
        }
    }

    geometry->vectors[4].x = geometry->vectors[0].x;
    geometry->vectors[4].y = geometry->vectors[0].y;
    geometry->vectors[4].z = geometry->vectors[0].z;
}
