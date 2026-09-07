#include "common.h"

typedef struct S_801750E4_0_pre {
    s16 unk_00;
    s16 unk_02;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x6];
    s16 unk_0C;
    s16 unk_0E;
    u8 unk_10;
    u8 unk_11;
} S_801750E4_0_pre;   /* the 0x12 bytes before q in func_801750E4, addressed as q[-1] */

typedef struct S_801750E4_0 {
    u16 unk_00;
    u8 pad_02[0x4];
    s16 unk_06;
    s16 unk_08;
    u8 unk_0A;
    u8 unk_0B;
    u8 pad_0C[0x6];
    s16 unk_12;
    s16 unk_14;
    u8 unk_16;
    u8 unk_17;
} S_801750E4_0;   /* q in func_801750E4 */



typedef struct GraphicsState {
    u8 pad[0x8D0];
    void *next_prim;
} GraphicsState;

typedef struct Elem {
    u32 color;
    s16 x;
    s16 y;
    u8  a;
    u8  b;
    u16 code;
} Elem;

typedef struct Block {
    u32 tag;
    Elem e[4];
} Block;

typedef struct StackValues {
    u16 arg0;
    u16 arg1;
    u16 arg2;
    u16 arg3;
} StackValues;

extern GraphicsState *D_80083160;
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8006658C(s32, void *);
extern void func_8006671C(void *);

/* Emit colored quads between two concentric elliptical arcs. */
void func_801750E4(u16 radius_a_x, u16 radius_a_y, u16 radius_b_x, u16 radius_b_y,
                   u16 center_x, u16 center_y, s32 *color_b_ptr, s32 *color_a_ptr,
                   s32 draw_bucket, s32 start_segment, s32 end_segment)
{
    StackValues radii;
    u16 segment_limit;
    u16 segment;
    s32 scale_b_x;
    s32 scale_b_y;
    s32 scale_a_x;
    s32 scale_a_y;
    register s32 angle ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
    s32 sin_angle;
    s32 cos_angle;
    s32 prev_sin;
    s32 prev_cos;
    u8 *prim;
    u8 *submit_prim;
    register u8 *vertex_data ASM_REG("$18");   /* MATCH pin: keeps a constant in a register as retail does */
    GraphicsState **graphics_ptr;
    register GraphicsState *graphics ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u16 next_segment ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 color_b;
    s32 color_a;
    register s32 first_segment ASM_REG("$18");   /* MATCH pin: keeps a constant in a register as retail does */

    first_segment = (s16)start_segment;
    angle = first_segment << 7;
    radii.arg0 = radius_a_x;
    graphics_ptr = &D_80083160;
    graphics = *graphics_ptr;
    prim = (u8 *)graphics->next_prim;
    radii.arg1 = radius_a_y;
    radii.arg2 = radius_b_x;
    radii.arg3 = radius_b_y;
    sin_angle = func_80064584(angle) >> 4;
    cos_angle = func_800644B8(angle) >> 4;
    segment_limit = end_segment;
    segment = start_segment;

    if (first_segment < (s16)end_segment) {
        scale_b_x = radii.arg2;
        scale_b_y = radii.arg3;
        scale_a_x = radii.arg0;
        scale_a_y = radii.arg1;
        vertex_data = prim + 0x1A;
        ASM_USE2(vertex_data, scale_a_y);   /* MATCH pin: retail schedule: same instructions, different order without it */
        do {
               ASM_USE_NV(angle);   /* MATCH pin: retail register colouring depends on it */
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            angle += 0x80;
            prev_sin = sin_angle;
            sin_angle = func_80064584(angle) >> 4;
            prev_cos = cos_angle;
            cos_angle = func_800644B8(angle);
            cos_angle = cos_angle >> 4;

            color_b = *color_b_ptr;
            (*(u32 *)((u8 *)vertex_data + -0x0A)) = color_b;
            (*(u32 *)((u8 *)vertex_data + -0x16)) = color_b;
            color_a = *color_a_ptr;
            (*(u32 *)((u8 *)vertex_data + 0x0E)) = color_a;
            (*(u32 *)((u8 *)vertex_data + 0x02)) = color_a;
            func_8006671C(prim);

            ((S_801750E4_0 *)vertex_data)->unk_0A = 1;
            ((S_801750E4_0_pre *)vertex_data)[-1].unk_04 = 1;
            ((S_801750E4_0 *)vertex_data)->unk_16 = 2;
            ((S_801750E4_0_pre *)vertex_data)[-1].unk_10 = 2;
            ((S_801750E4_0_pre *)vertex_data)[-1].unk_11 = 0xFB;
            ((S_801750E4_0_pre *)vertex_data)[-1].unk_05 = 0xFB;
            ((S_801750E4_0 *)vertex_data)->unk_17 = 0xFB;
            ((S_801750E4_0 *)vertex_data)->unk_0B = 0xFB;

            ((S_801750E4_0_pre *)vertex_data)[-1].unk_00 = center_x + ((scale_b_x * prev_sin) >> 8);
            ((S_801750E4_0_pre *)vertex_data)[-1].unk_02 = center_y + ((scale_b_y * prev_cos) >> 8);
            ((S_801750E4_0_pre *)vertex_data)[-1].unk_0C = center_x + ((scale_b_x * sin_angle) >> 8);
            ((S_801750E4_0_pre *)vertex_data)[-1].unk_0E = center_y + ((scale_b_y * cos_angle) >> 8);
            ((S_801750E4_0 *)vertex_data)->unk_06 = center_x + ((scale_a_x * prev_sin) >> 8);
            ((S_801750E4_0 *)vertex_data)->unk_08 = center_y + ((scale_a_y * prev_cos) >> 8);
            ((S_801750E4_0 *)vertex_data)->unk_12 = center_x + ((scale_a_x * sin_angle) >> 8);
            ((S_801750E4_0 *)vertex_data)->unk_14 = center_y + ((scale_a_y * cos_angle) >> 8);

            ((S_801750E4_0 *)vertex_data)->unk_00 = 0x133;

            submit_prim = prim;
            func_8006658C(draw_bucket, submit_prim);
            prim += sizeof(Block);
            next_segment = segment + 1;
            segment = next_segment;
            vertex_data += sizeof(Block);
        } while (((s32)(u32)next_segment << 16) < ((s32)(u32)segment_limit << 16));
    }
    (*graphics_ptr)->next_prim = prim;
}
