#include "common.h"

typedef struct {
    u16 h[4];
} Coord8;

typedef struct {
    u32 w0;
    u32 w1;
} __attribute__((packed)) Packed8;

extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 func_800A130C();
extern s32 func_800A1330();
extern s32 func_800A2E30(Coord8, Coord8, Packed8, Packed8, s32);

static __inline__ s16 scale_trig(s32 trig, s32 radius)
{
    return (trig * radius) >> 16;
}

static __inline__ s16 offset_coord(s16 base, s32 offset)
{
    return base + offset;
}

/* Builds 16 segments between two radii around a shared center. */
void func_800A2FCC(s32 center_source, s32 radius_a, s32 radius_b, s16 segment_arg)
{
    Coord8 center;
    Coord8 prev_a;
    Coord8 prev_b;
    Coord8 point_a;
    Coord8 point_b;
    Coord8 *start_a;
    Coord8 *start_b;
    register Coord8 *point_a_ptr;
    Coord8 *point_b_ptr;
    register s32 angle;
    s32 segment_count;

    func_800A130C(&center, center_source);
    start_a = &point_a;
    func_800A1330(start_a, &center);
    start_b = &point_b;
    func_800A1330(start_b, &center);
    point_a.h[0] = offset_coord(point_a.h[0], scale_trig(func_800644B8(0), radius_a));
    point_a.h[1] = offset_coord(point_a.h[1], scale_trig(func_80064584(0), radius_a));
    point_b.h[0] = offset_coord(point_b.h[0], scale_trig(func_800644B8(0), radius_b));
    point_b.h[1] = offset_coord(point_b.h[1], scale_trig(func_80064584(0), radius_b));
    angle = 0;
    segment_count = 0;
    point_a_ptr = start_a;
    point_b_ptr = start_b;

    {
        s32 upper_mask = 0xFFFF0000;


        do {
            func_800A1330(&prev_a, point_a_ptr);
            func_800A1330(&prev_b, point_b_ptr);
            angle += 0x100;
            func_800A1330(point_a_ptr, &center);
            func_800A1330(point_b_ptr, &center);
            point_a.h[0] = offset_coord(point_a.h[0], scale_trig(func_800644B8(angle), radius_a));
            point_a.h[1] = offset_coord(point_a.h[1], scale_trig(func_80064584(angle), radius_a));
            point_b.h[0] = offset_coord(point_b.h[0], scale_trig(func_800644B8(angle), radius_b));
            segment_count++;
            point_b.h[1] = offset_coord(point_b.h[1], scale_trig(func_80064584(angle), radius_b));
            func_800A2E30(prev_a, prev_b,
                          *(Packed8 *)&point_a,
                          *(Packed8 *)&point_b,
                          segment_arg);
        } while (segment_count < 0x10);
    }
}
