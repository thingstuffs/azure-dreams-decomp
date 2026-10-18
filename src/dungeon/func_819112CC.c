#include "modules/dungeon_ovl_1930844.h"

static __inline__ s32 radial_coordinate(s32 center, s32 trig, s16 radius)
{
    return center + (((trig >> 4) * radius) << 8);
}

typedef union { s32 value; struct { u16 low, high; } half; } PointCoord;
typedef struct { u8 prefix[0x18]; PointCoord x[5]; PointCoord y[5]; } EffectCoords;

/* Build and queue interpolated vertical quads around five perimeter points. */
void build_and_queue_interpolated_vertical_quads_around_five_perimeter_points(void *effect_in, ovl_1930844_819112CC_S_819112CC_1 *origin, s16 step_in, s16 duration_in)
{
    void *effect = effect_in;
    s32 step = step_in;
    s32 duration = duration_in;

    u8 *prim;
    s32 angle_x_or_mask;
    s32 angle_x_or_mask_2;
    s32 target_x;
    s32 target_y;
    s32 radial_y;
    s32 interpolate;
    s32 vertex_base;
    s16 next_end_y;
    s16 end_y;
    s16 bottom_z;
    s16 end_x;
    s16 next_end_x;
    u32 *link;
    s32 radial_x;
    s32 next_delta_y;
    s32 delta_y;
    s32 next_delta_x;
    s32 delta_x;
    s32 point_index;
    s32 twice_index;
    s32 next_index;
    u16 y_step;
    u16 next_start_y;
    u16 start_x;
    u16 start_y;
    u16 top_z;
    u16 next_start_x;
    u8 *point;
    s32 row_off;
    s32 modulo_result;
    s32 ot_slot;
    s32 ot_slot2;
    ScratchPad *scratch;
    u8 *context_slot;
    u8 *v1;
    u8 *v2;
    u8 *v3;
    u8 *sxy0;
    u8 *sxy1;
    u8 *sxy2;
    u8 *sxy3;
    u8 *depth;
    u8 *flag;
    ovl_1930844_819112CC_EmptyArg empty_arg;
    u8 *render_context = *(u8 **)ovl_1930844_819112CC_GFX_ROOT_SLOT;

    context_slot = ovl_1930844_819112CC_GFX_ROOT_SLOT;
    point_index = 0;
    scratch = (ScratchPad *)0x1F800000;
    interpolate = step < duration;
    vertex_base = 0x1F800064;
    ovl_1930844_819112CC_SP32(0x18) = (u32)render_context + 0xB0;
    for (; point_index < 5; point_index = next_index) {
        twice_index = point_index * 2;
        angle_x_or_mask_2 = (twice_index + 1) * 0x199;
        link = (u32 *)(angle_x_or_mask_2 + ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_0A);
        radial_x = func_800644B8((s32)link);
        target_x = radial_coordinate(origin->unk_00, radial_x, ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_0E);
        row_off = func_80064584(angle_x_or_mask_2 + ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_0A);
        row_off >>= 4;
        radial_y = origin->unk_04 +
            ((row_off * ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_0E) << 8);
        target_y = radial_y;
        {
            GpuContext **pool = (GpuContext **)context_slot;
            prim = (*pool)->packetCursor;
            (*pool)->packetCursor = prim + 0x24;
        }
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_00.at03.v = 8;
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_07 = 0x3A;
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_04 = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_40;
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_05 = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_41;
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_06 = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_42;
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_0C = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_40;
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_0D = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_41;
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_0E = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_42;
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_14 = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_40;
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_15 = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_41;
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_16 = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_42;
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_1C = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_40;
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_1D = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_41;
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_1E = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_42;
        start_x = ((EffectCoords *)effect)->x[point_index].half.high;
        ovl_1930844_819112CC_SP16(0x74) = start_x;
        ovl_1930844_819112CC_SP16(0x64) = start_x;
        delta_x = target_x - ((EffectCoords *)effect)->x[point_index].value;
        ovl_1930844_819112CC_SP32(0x108) = delta_x;
        if (interpolate != 0) {
            ovl_1930844_819112CC_SP32(0x108) = (delta_x / duration) * step;
        }
        end_x = ((EffectCoords *)effect)->x[point_index].half.high + ovl_1930844_819112CC_SP16(0x10A);
        ovl_1930844_819112CC_SP16(0x7C) = end_x;
        ovl_1930844_819112CC_SP16(0x6C) = end_x;
        start_y = ((EffectCoords *)effect)->y[point_index].half.high;
        ovl_1930844_819112CC_SP16(0x76) = start_y;
        ovl_1930844_819112CC_SP16(0x66) = start_y;
        delta_y = radial_y - ((EffectCoords *)effect)->y[point_index].value;
        ovl_1930844_819112CC_SP32(0x10C) = delta_y;
        if (interpolate != 0) {
            ovl_1930844_819112CC_SP32(0x10C) = (delta_y / duration) * step;
        }
        end_y = ((EffectCoords *)effect)->y[point_index].half.high + ovl_1930844_819112CC_SP16(0x10E);
        ovl_1930844_819112CC_SP16(0x7E) = end_y;
        ovl_1930844_819112CC_SP16(0x6E) = end_y;
        bottom_z = origin->unk_0A - ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_10;
        ovl_1930844_819112CC_SP16(0x70) = bottom_z;
        ovl_1930844_819112CC_SP16(0x68) = bottom_z;
        top_z = origin->unk_0A;
        v1 = (u8 *)scratch + 0x6C;
        v2 = (u8 *)scratch + 0x74;
        v3 = (u8 *)scratch + 0x7C;
        sxy0 = (u8 *)scratch + 0xD8;
        sxy1 = (u8 *)scratch + 0xDC;
        sxy2 = (u8 *)scratch + 0xE0;
        sxy3 = (u8 *)scratch + 0xE4;
        depth = (u8 *)scratch + 0x84;
        flag = (u8 *)scratch + 0x88;
        ovl_1930844_819112CC_SP32(0xB4) = func_80065590(vertex_base, v1, v2, v3,
                                   sxy0, sxy1, sxy2, sxy3,
                                   depth, (ovl_1930844_819112CC_SP16(0x78) = top_z,
                                    ovl_1930844_819112CC_SP16(0x80) = top_z,
                                    flag));
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_08 = ovl_1930844_819112CC_SP16(0xD8);
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_0A = ovl_1930844_819112CC_SP16(0xDA);
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_10 = ovl_1930844_819112CC_SP16(0xDC);
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_12 = ovl_1930844_819112CC_SP16(0xDE);
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_18 = ovl_1930844_819112CC_SP16(0xE0);
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_1A = ovl_1930844_819112CC_SP16(0xE2);
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_20 = ovl_1930844_819112CC_SP16(0xE4);
        ((ovl_1930844_819112CC_S_819112CC_2 *)prim)->unk_22 = ovl_1930844_819112CC_SP16(0xE6);
        link = (u32 *)(ovl_1930844_819112CC_SP32(0xB4));
        if ((u32)link < 0x1E0U) {
            ot_slot = (u32)link << 2;
            angle_x_or_mask = (s32)0xFF000000;
            ot_slot += ovl_1930844_819112CC_SP32(0x18);
            ovl_1930844_819112CC_setaddr(prim, ovl_1930844_819112CC_getaddr(ot_slot));
            link = (u32 *)ovl_1930844_819112CC_SP32(0xB4);
            link = (u32 *)((u32)link << 2);
            link = (u32 *)((u8 *)link + ovl_1930844_819112CC_SP32(0x18));
            *link = (*link & (u32)angle_x_or_mask) | ((u32)prim & 0xFFFFFF);
            {
                GpuContext *ctx = *(GpuContext **)context_slot;
                prim = ctx->packetCursor;
                ctx->packetCursor = prim + 0xC;
            }
            func_80067F20(prim, 0, 0,
                          func_80066460(0, ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_12, 0, 0) & 0xFFFF,
                          0);
            ovl_1930844_819112CC_setaddr(prim, ovl_1930844_819112CC_getaddr(&((u32 *)ovl_1930844_819112CC_SP32(0x18))[ovl_1930844_819112CC_SP32(0xB4)]));
            link = (u32 *)ovl_1930844_819112CC_SP32(0xB4);
            link = (u32 *)((u32)link << 2);
            link = (u32 *)((u8 *)link + ovl_1930844_819112CC_SP32(0x18));
            *link = (*link & (u32)angle_x_or_mask) | ((u32)prim & 0xFFFFFF);
        }
        {
            GpuContext **pool = (GpuContext **)context_slot;
            prim = (*pool)->packetCursor;
            (*pool)->packetCursor = prim + 0x24;
        }
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_00.at03.v = 8;
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_07 = 0x3A;
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_04 = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_40;
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_05 = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_41;
        next_index = point_index + 1;
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_06 = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_42;
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_0C = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_40;
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_0D = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_41;
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_0E = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_42;
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_14 = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_40;
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_15 = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_41;
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_16 = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_42;
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_1C = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_40;
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_1D = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_41;
        row_off = ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_42;
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_1E = row_off;
        modulo_result = next_index % 5;
        row_off = modulo_result;
        point = (u8 *)effect + row_off * 4;
        next_start_x = ((ovl_1930844_819112CC_S_819112CC_3 *)point)->unk_18.at02.v;
        ovl_1930844_819112CC_SP16(0x74) = next_start_x;
        ovl_1930844_819112CC_SP16(0x64) = next_start_x;
        next_delta_x = target_x - ((ovl_1930844_819112CC_S_819112CC_3 *)point)->unk_18.at00.v;
        ovl_1930844_819112CC_SP32(0x108) = next_delta_x;
        if (interpolate != 0) {
            ovl_1930844_819112CC_SP32(0x108) = (next_delta_x / duration) * step;
        }
        next_end_x = ((ovl_1930844_819112CC_S_819112CC_3 *)point)->unk_18.at02.v + ovl_1930844_819112CC_SP16(0x10A);
        ovl_1930844_819112CC_SP16(0x7C) = next_end_x;
        ovl_1930844_819112CC_SP16(0x6C) = next_end_x;
        next_start_y = ((ovl_1930844_819112CC_S_819112CC_3 *)point)->unk_2C.at02.v;
        ovl_1930844_819112CC_SP16(0x76) = next_start_y;
        ovl_1930844_819112CC_SP16(0x66) = next_start_y;
        next_delta_y = target_y - ((ovl_1930844_819112CC_S_819112CC_3 *)point)->unk_2C.at00.v;
        ovl_1930844_819112CC_SP32(0x10C) = next_delta_y;
        if (interpolate != 0) {
            ovl_1930844_819112CC_SP32(0x10C) = (next_delta_y / duration) * step;
        }
        next_end_y = ((ovl_1930844_819112CC_S_819112CC_3 *)point)->unk_2C.at02.v;
        y_step = ovl_1930844_819112CC_SP16(0x10E);
        ovl_1930844_819112CC_SP32(0xB4) = func_80065590(vertex_base, v1, v2, v3,
                                   sxy0, sxy1, sxy2, sxy3,
                                   depth, (next_end_y += y_step,
                                    ovl_1930844_819112CC_SP16(0x7E) = next_end_y,
                                    ovl_1930844_819112CC_SP16(0x6E) = next_end_y,
                                    flag));
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_08 = ovl_1930844_819112CC_SP16(0xD8);
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_0A = ovl_1930844_819112CC_SP16(0xDA);
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_10 = ovl_1930844_819112CC_SP16(0xDC);
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_12 = ovl_1930844_819112CC_SP16(0xDE);
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_18 = ovl_1930844_819112CC_SP16(0xE0);
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_1A = ovl_1930844_819112CC_SP16(0xE2);
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_20 = ovl_1930844_819112CC_SP16(0xE4);
        ((ovl_1930844_819112CC_S_819112CC_5 *)prim)->unk_22 = ovl_1930844_819112CC_SP16(0xE6);
        link = (u32 *)(ovl_1930844_819112CC_SP32(0xB4));
        if ((u32)link < 0x1E0U) {
            ot_slot2 = (u32)link << 2;
            angle_x_or_mask = (s32)0xFF000000;
            ot_slot2 += ovl_1930844_819112CC_SP32(0x18);
            ovl_1930844_819112CC_setaddr(prim, ovl_1930844_819112CC_getaddr(ot_slot2));
            link = (u32 *)ovl_1930844_819112CC_SP32(0xB4);
            link = (u32 *)((u32)link << 2);
            link = (u32 *)((u8 *)link + ovl_1930844_819112CC_SP32(0x18));
            *link = (*link & (u32)angle_x_or_mask) | ((u32)prim & 0xFFFFFF);
            {
                GpuContext *ctx = *(GpuContext **)context_slot;
                prim = ctx->packetCursor;
                ctx->packetCursor = prim + 0xC;
            }
            func_80067F20(prim, 0, 0,
                          func_80066460(0, ((ovl_1930844_819112CC_S_819112CC_0 *)effect)->unk_12, 0, 0) & 0xFFFF,
                          0);
            ovl_1930844_819112CC_setaddr(prim, ovl_1930844_819112CC_getaddr(&((u32 *)ovl_1930844_819112CC_SP32(0x18))[ovl_1930844_819112CC_SP32(0xB4)]));
            link = (u32 *)ovl_1930844_819112CC_SP32(0xB4);
            link = (u32 *)((u32)link << 2);
            link = (u32 *)((u8 *)link + ovl_1930844_819112CC_SP32(0x18));
            *link = (*link & (u32)angle_x_or_mask) | ((u32)prim & 0xFFFFFF);
        }
    }
}
