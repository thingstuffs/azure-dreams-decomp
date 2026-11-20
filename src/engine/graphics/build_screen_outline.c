#include "common.h"
#include "shared/game_work.h"
#include "engine/graphics.h"
#include "engine/effect.h"
#include "sdk/libgte.h"

/* Builds a closed outline from a screen rectangle, with a rotated square as fallback. */
void build_screen_outline(
    GameView *view, SVECTOR *points, s32 depth)
{
    SVECTOR corners[4];
    SVECTOR transformed_corners[4];
    s32 screen_origin[2];
    SVECTOR screen_point;
    SVECTOR center;
    GameWork *view_geometry;
    s32 corner_index;
    s32 angle;
    s32 cos_angle;
    s32 sin_angle;
    s32 use_fallback;
    u16 left;
    u16 right;
    u16 top;
    u16 bottom;

    left = view->clip_x;
    use_fallback = 0;
    corners[3].vx = left;
    corners[0].vx = left;

    right = view->clip_x + view->clip_width;
    corners[2].vx = right;
    corners[1].vx = right;

    top = view->clip_y;
    corners[1].vy = top;
    corners[0].vy = top;

    bottom = view->clip_y + view->clip_height;
    screen_origin[0] = 0;
    screen_origin[1] = 0;
    corners[2].vy = bottom;
    corners[3].vy = bottom;

    view_geometry = &g_game_work;
    corners[0].vz = corners[1].vz = corners[2].vz = corners[3].vz =
        ReadGeomScreen();

    world_to_local_position(
        (SVECTOR *)screen_origin,
        &points[5]);

    for (corner_index = 3; corner_index >= 0; corner_index--) {
        world_to_local_position(&corners[corner_index], &transformed_corners[corner_index]);
        if (intersect_view_ray_with_depth_plane(&points[5], &transformed_corners[corner_index],
                          &points[corner_index], depth)) {
            use_fallback = 1;
        }
    }

    if (use_fallback != 0) {
        angle = view_geometry->view.camera_rotation.parts.viewAngle + 0x600;
        screen_point.vx = view_geometry->view.view_offset.parts.view_offset_x;
        screen_point.vy = view_geometry->view.view_offset.parts.view_offset_y;
        screen_point.vz = view_geometry->view.view_offset.parts.view_offset_z;
        world_to_local_position(&screen_point, &center);

        for (corner_index = 3; corner_index >= 0; corner_index--) {
            cos_angle = rcos(angle);
            sin_angle = rsin(angle);
            angle += 0x400;
            points[corner_index].vx =
                center.vx + (cos_angle >> 3) + (cos_angle >> 4);
            points[corner_index].vy =
                center.vy + (sin_angle >> 3) + (sin_angle >> 4);
            points[corner_index].vz = center.vz;
        }
    }

    points[4].vx = points[0].vx;
    points[4].vy = points[0].vy;
    points[4].vz = points[0].vz;
}
