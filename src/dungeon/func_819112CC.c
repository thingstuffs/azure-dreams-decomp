#include "common.h"

typedef struct S_819112CC_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u16 unk_10;
    s16 unk_12;
    u8 pad_14[0x2C];
    u8 unk_40;
    u8 unk_41;
    u8 unk_42;
} S_819112CC_0;   /* arg0 in func_819112CC */

typedef struct S_819112CC_1 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_819112CC_1;   /* arg1 in func_819112CC */

typedef struct S_819112CC_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    s8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 pad_17[0x1];
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 pad_1F[0x1];
    u16 unk_20;
    u16 unk_22;
} S_819112CC_2;   /* temp_s1 in func_819112CC */

typedef struct S_819112CC_3 {
    u8 pad_00[0x18];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_18;   /* overlapping accesses */
    u8 pad_1C[0x10];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_2C;   /* overlapping accesses */
} S_819112CC_3;   /* temp_a3 in func_819112CC */

typedef struct S_819112CC_4 {
    u32 unk_00;
} S_819112CC_4;   /* temp_s1_2 in func_819112CC */

typedef struct S_819112CC_5 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    s8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 pad_17[0x1];
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 pad_1F[0x1];
    u16 unk_20;
    u16 unk_22;
} S_819112CC_5;   /* temp_s1_3 in func_819112CC */


#define SP16(off) (*(u16 *)(scratch + (off)))
#define SP32(off) (*(u32 *)(scratch + (off)))
/* Same address as D_80083160 (0x80083178 - 0x18); this spelling keeps its
   page construction shared with the other references below. */
#define GFX_ROOT_SLOT (((u8 *)&D_80083178) - 0x18)

extern s32 func_800644B8();
extern s32 func_80064584();
extern u32 func_80065590();
extern s32 func_80066460();
extern void func_80067F20();
typedef struct {
    u8 pad0[0x8D0];
    u8 *nextPrim;
} RenderContext;
typedef struct {} EmptyArg;
extern RenderContext *D_80083160;

/* Build and queue interpolated vertical quads around five perimeter points. */
void func_819112CC(void *effect_in, S_819112CC_1 *origin, s16 step_in, s16 duration_in)
{
    void *effect = effect_in;
    s32 step = step_in;
    s32 duration = duration_in;
    register u32 low_mask ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *prim;
    register s32 angle_x_or_mask ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
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
    register u32 *link ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 angle ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 radial_x;
    s32 next_delta_y;
    s32 delta_y;
    s32 next_delta_x;
    s32 delta_x;
    s32 point_index;
    s32 twice_index;
    u16 y_step;
    u16 next_start_y;
    u16 start_x;
    u16 start_y;
    u16 top_z;
    u16 next_start_x;
    register u32 depth ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *point;
    register s32 coord_or_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *scratch ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u8 *context_slot;
    EmptyArg empty_arg;
    u8 *render_context = *(u8 **)GFX_ROOT_SLOT;

    context_slot = GFX_ROOT_SLOT;
    point_index = 0;
    scratch = (u8 *)0x1F800000;
    interpolate = step < duration;
    vertex_base = 0x1F800064;
    low_mask = 0x00FFFFFF;
    SP32(0x18) = (u32)render_context + 0xB0;
    while (point_index < 5) {
        twice_index = point_index * 2;
        angle_x_or_mask = (twice_index + 1) * 0x199;
        angle = angle_x_or_mask + ((S_819112CC_0 *)effect)->unk_0A;
        radial_x = func_800644B8(angle);
        angle = ((S_819112CC_0 *)effect)->unk_0A;
        angle = angle_x_or_mask + angle;
        angle_x_or_mask = origin->unk_00;
        angle_x_or_mask += (((radial_x >> 4) *
                     ((S_819112CC_0 *)effect)->unk_0E) << 8);
        ASM_KEEP_NV(angle_x_or_mask);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        coord_or_offset = func_80064584(angle);
        target_x = angle_x_or_mask;
        coord_or_offset >>= 4;
        radial_y = origin->unk_04 +
            ((coord_or_offset * ((S_819112CC_0 *)effect)->unk_0E) << 8);
        target_y = radial_y;
        {
            RenderContext **pool = (RenderContext **)context_slot;
            prim = (*pool)->nextPrim;
            (*pool)->nextPrim = prim + 0x24;
        }
        ((S_819112CC_2 *)prim)->unk_00.at03.v = 8;
        ((S_819112CC_2 *)prim)->unk_07 = 0x3A;
        ((S_819112CC_2 *)prim)->unk_04 = ((S_819112CC_0 *)effect)->unk_40;
        ((S_819112CC_2 *)prim)->unk_05 = ((S_819112CC_0 *)effect)->unk_41;
        ((S_819112CC_2 *)prim)->unk_06 = ((S_819112CC_0 *)effect)->unk_42;
        ((S_819112CC_2 *)prim)->unk_0C = ((S_819112CC_0 *)effect)->unk_40;
        ((S_819112CC_2 *)prim)->unk_0D = ((S_819112CC_0 *)effect)->unk_41;
        ((S_819112CC_2 *)prim)->unk_0E = ((S_819112CC_0 *)effect)->unk_42;
        ((S_819112CC_2 *)prim)->unk_14 = ((S_819112CC_0 *)effect)->unk_40;
        ((S_819112CC_2 *)prim)->unk_15 = ((S_819112CC_0 *)effect)->unk_41;
        ((S_819112CC_2 *)prim)->unk_16 = ((S_819112CC_0 *)effect)->unk_42;
        ((S_819112CC_2 *)prim)->unk_1C = ((S_819112CC_0 *)effect)->unk_40;
        ((S_819112CC_2 *)prim)->unk_1D = ((S_819112CC_0 *)effect)->unk_41;
        coord_or_offset = point_index * 4;
        point = (u8 *)effect + coord_or_offset;
        ((S_819112CC_2 *)prim)->unk_1E = ((S_819112CC_0 *)effect)->unk_42;
        start_x = ((S_819112CC_3 *)point)->unk_18.at02.v;
        SP16(0x74) = start_x;
        SP16(0x64) = start_x;
        delta_x = angle_x_or_mask - ((S_819112CC_3 *)point)->unk_18.at00.v;
        SP32(0x108) = delta_x;
        if (interpolate != 0) {
            SP32(0x108) = (delta_x / duration) * step;
        }
        end_x = ((S_819112CC_3 *)point)->unk_18.at02.v + SP16(0x10A);
        SP16(0x7C) = end_x;
        SP16(0x6C) = end_x;
        start_y = ((S_819112CC_3 *)point)->unk_2C.at02.v;
        SP16(0x76) = start_y;
        SP16(0x66) = start_y;
        delta_y = radial_y - ((S_819112CC_3 *)point)->unk_2C.at00.v;
        SP32(0x10C) = delta_y;
        if (interpolate != 0) {
            SP32(0x10C) = (delta_y / duration) * step;
        }
        end_y = ((S_819112CC_3 *)point)->unk_2C.at02.v + SP16(0x10E);
        SP16(0x7E) = end_y;
        SP16(0x6E) = end_y;
        bottom_z = origin->unk_0A - ((S_819112CC_0 *)effect)->unk_10;
        SP16(0x70) = bottom_z;
        SP16(0x68) = bottom_z;
        top_z = origin->unk_0A;
        SP32(0xB4) = func_80065590(vertex_base, scratch + 0x6C,
                                  scratch + 0x74, scratch + 0x7C,
                                  scratch + 0xD8, scratch + 0xDC,
                                  scratch + 0xE0, scratch + 0xE4,
                                  scratch + 0x84, scratch + 0x88,
                                  (SP16(0x78) = top_z,
                                   SP16(0x80) = top_z,
                                   empty_arg));
        ((S_819112CC_2 *)prim)->unk_08 = SP16(0xD8);
        ((S_819112CC_2 *)prim)->unk_0A = SP16(0xDA);
        ((S_819112CC_2 *)prim)->unk_10 = SP16(0xDC);
        ((S_819112CC_2 *)prim)->unk_12 = SP16(0xDE);
        ((S_819112CC_2 *)prim)->unk_18 = SP16(0xE0);
        ((S_819112CC_2 *)prim)->unk_1A = SP16(0xE2);
        ((S_819112CC_2 *)prim)->unk_20 = SP16(0xE4);
        ((S_819112CC_2 *)prim)->unk_22 = SP16(0xE6);
        depth = SP32(0xB4);
        if (depth < 0x1E0U) {
            coord_or_offset = depth << 2;
            angle_x_or_mask = (s32)0xFF000000;
            coord_or_offset += SP32(0x18);
            ((S_819112CC_2 *)prim)->unk_00.at00.v = (((S_819112CC_2 *)prim)->unk_00.at00.v & (u32)angle_x_or_mask) |
                (*(u32 *)coord_or_offset & low_mask);
            link = (u32 *)((SP32(0xB4) << 2) + SP32(0x18));
            *link = (*link & (u32)angle_x_or_mask) | ((u32)prim & low_mask);
            {
                RenderContext *ctx = *(RenderContext **)context_slot;
                prim = ctx->nextPrim;
                ctx->nextPrim = prim + 0xC;
            }
            func_80067F20(prim, 0, 0,
                         func_80066460(0, ((S_819112CC_0 *)effect)->unk_12, 0, 0) & 0xFFFF,
                         0);
            ((S_819112CC_4 *)prim)->unk_00 = (((S_819112CC_4 *)prim)->unk_00 & (u32)angle_x_or_mask) |
                (((u32 *)SP32(0x18))[SP32(0xB4)] & low_mask);
            link = (u32 *)((SP32(0xB4) << 2) + SP32(0x18));
            *link = (*link & (u32)angle_x_or_mask) | ((u32)prim & low_mask);
        }
        {
            RenderContext **pool = (RenderContext **)context_slot;
            prim = (*pool)->nextPrim;
            (*pool)->nextPrim = prim + 0x24;
        }
        ((S_819112CC_5 *)prim)->unk_00.at03.v = 8;
        ((S_819112CC_5 *)prim)->unk_07 = 0x3A;
        ((S_819112CC_5 *)prim)->unk_04 = ((S_819112CC_0 *)effect)->unk_40;
        ((S_819112CC_5 *)prim)->unk_05 = ((S_819112CC_0 *)effect)->unk_41;
        ((S_819112CC_5 *)prim)->unk_06 = ((S_819112CC_0 *)effect)->unk_42;
        point_index += 1;
        ((S_819112CC_5 *)prim)->unk_0C = ((S_819112CC_0 *)effect)->unk_40;
        ((S_819112CC_5 *)prim)->unk_0D = ((S_819112CC_0 *)effect)->unk_41;
        ((S_819112CC_5 *)prim)->unk_0E = ((S_819112CC_0 *)effect)->unk_42;
        ((S_819112CC_5 *)prim)->unk_14 = ((S_819112CC_0 *)effect)->unk_40;
        ((S_819112CC_5 *)prim)->unk_15 = ((S_819112CC_0 *)effect)->unk_41;
        ((S_819112CC_5 *)prim)->unk_16 = ((S_819112CC_0 *)effect)->unk_42;
        ((S_819112CC_5 *)prim)->unk_1C = ((S_819112CC_0 *)effect)->unk_40;
        ((S_819112CC_5 *)prim)->unk_1D = ((S_819112CC_0 *)effect)->unk_41;
        coord_or_offset = ((S_819112CC_0 *)effect)->unk_42;
        ((S_819112CC_5 *)prim)->unk_1E = coord_or_offset;
        coord_or_offset = point_index % 5;
        coord_or_offset *= 4;
        point = (u8 *)effect + coord_or_offset;
        ASM_KEEP_NV(point_index);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        next_start_x = ((S_819112CC_3 *)point)->unk_18.at02.v;
        SP16(0x74) = next_start_x;
        SP16(0x64) = next_start_x;
        next_delta_x = target_x - ((S_819112CC_3 *)point)->unk_18.at00.v;
        SP32(0x108) = next_delta_x;
        if (interpolate != 0) {
            SP32(0x108) = (next_delta_x / duration) * step;
        }
        next_end_x = ((S_819112CC_3 *)point)->unk_18.at02.v + SP16(0x10A);
        SP16(0x7C) = next_end_x;
        SP16(0x6C) = next_end_x;
        next_start_y = ((S_819112CC_3 *)point)->unk_2C.at02.v;
        SP16(0x76) = next_start_y;
        SP16(0x66) = next_start_y;
        next_delta_y = target_y - ((S_819112CC_3 *)point)->unk_2C.at00.v;
        SP32(0x10C) = next_delta_y;
        if (interpolate != 0) {
            SP32(0x10C) = (next_delta_y / duration) * step;
        }
        next_end_y = ((S_819112CC_3 *)point)->unk_2C.at02.v;
        y_step = SP16(0x10E);
        SP32(0xB4) = func_80065590(vertex_base, scratch + 0x6C,
                                  scratch + 0x74, scratch + 0x7C,
                                  scratch + 0xD8, scratch + 0xDC,
                                  scratch + 0xE0, scratch + 0xE4,
                                  scratch + 0x84, scratch + 0x88,
                                  (next_end_y += y_step,
                                   SP16(0x7E) = next_end_y,
                                   SP16(0x6E) = next_end_y,
                                   empty_arg));
        ((S_819112CC_5 *)prim)->unk_08 = SP16(0xD8);
        ((S_819112CC_5 *)prim)->unk_0A = SP16(0xDA);
        ((S_819112CC_5 *)prim)->unk_10 = SP16(0xDC);
        ((S_819112CC_5 *)prim)->unk_12 = SP16(0xDE);
        ((S_819112CC_5 *)prim)->unk_18 = SP16(0xE0);
        ((S_819112CC_5 *)prim)->unk_1A = SP16(0xE2);
        ((S_819112CC_5 *)prim)->unk_20 = SP16(0xE4);
        ((S_819112CC_5 *)prim)->unk_22 = SP16(0xE6);
        depth = SP32(0xB4);
        if (depth < 0x1E0U) {
            coord_or_offset = depth << 2;
            angle_x_or_mask = (s32)0xFF000000;
            coord_or_offset += SP32(0x18);
            ((S_819112CC_5 *)prim)->unk_00.at00.v = (((S_819112CC_5 *)prim)->unk_00.at00.v & (u32)angle_x_or_mask) |
                (*(u32 *)coord_or_offset & low_mask);
            link = (u32 *)((SP32(0xB4) << 2) + SP32(0x18));
            *link = (*link & (u32)angle_x_or_mask) | ((u32)prim & low_mask);
            {
                RenderContext *ctx = *(RenderContext **)context_slot;
                prim = ctx->nextPrim;
                ctx->nextPrim = prim + 0xC;
            }
            func_80067F20(prim, 0, 0,
                         func_80066460(0, ((S_819112CC_0 *)effect)->unk_12, 0, 0) & 0xFFFF,
                         0);
            ((S_819112CC_4 *)prim)->unk_00 = (((S_819112CC_4 *)prim)->unk_00 & (u32)angle_x_or_mask) |
                (((u32 *)SP32(0x18))[SP32(0xB4)] & low_mask);
            link = (u32 *)((SP32(0xB4) << 2) + SP32(0x18));
            *link = (*link & (u32)angle_x_or_mask) | ((u32)prim & low_mask);
        }
    }
}
