#include "common.h"

typedef struct S_8187B1F4_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8187B1F4_0;   /* arg1 in func_8187B1F4 */

typedef struct S_8187B1F4_1 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x12];
    u16 unk_A6;
} S_8187B1F4_1;   /* scratch in func_8187B1F4 */

typedef struct S_8187B1F4_2 {
    u8 pad_00[0x16];
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_8187B1F4_2;   /* arg2 in func_8187B1F4 */

typedef struct S_8187B1F4_3_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_8187B1F4_3_pre;   /* the 0x8 bytes before arg0 in func_8187B1F4, addressed as arg0[-1] */

typedef struct S_8187B1F4_3 {
    s32 unk_00;
    u8 pad_04[0xC];
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
} S_8187B1F4_3;   /* arg0 in func_8187B1F4 */

typedef struct S_8187B1F4_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s8 v; } at00u; struct { u8 v; } at00p; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; s8 v; } at03; } unk_04;   /* overlapping accesses */
} S_8187B1F4_4;   /* temp_s0 in func_8187B1F4 */

typedef struct S_8187B1F4_5 {
    u32 unk_00;
} S_8187B1F4_5;   /* (u8 *)VFIELD(scratch, void *, 0x24) +
                           VFIELD(scratch, u32, 0x100) * 4 in func_8187B1F4 */

typedef struct S_8187B1F4_6 {
    u32 unk_00;
    u8 pad_04[0x4];
    u8 * unk_08;
    u8 * unk_0C;
} S_8187B1F4_6;   /* tail in func_8187B1F4 */

typedef struct S_8187B1F4_7 {
    u32 unk_00;
} S_8187B1F4_7;   /* temp_s0_2 in func_8187B1F4 */

typedef struct S_8187B1F4_8 {
    u32 unk_00;
} S_8187B1F4_8;   /* state in func_8187B1F4 */


#define VFIELD(base, type, offset) (*(volatile type *)((u8 *)(base) + (offset)))

typedef struct GlobalState {
    u8 pad[0x8D0];
    u8 *next;
} GlobalState;

extern void func_80024A54() __attribute__((noreturn));
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern u32 func_80065420(void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u32, s32);
extern GlobalState *D_80083160[];

/* Projects points and adds brightness-scaled pixel primitives to the ordering table. */
s32 func_8187B1F4(u8 *points, u8 *position, u8 *orientation) {
    s32 view_matrix[8];
    void * volatile model_matrix;
    u8 *scratch;
    register u8 *model_matrix_ptr ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    u8 *transform_matrix;
    GlobalState **global;
    register GlobalState *state ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *ordering_table;
    u8 *point_packet;
    u8 *draw_mode_packet;
    u8 *unused_ptr;
    register s32 point_index ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    volatile u16 *point_coords;
    u32 depth;
    s32 point_count;
    register s32 result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 hard_zero ASM_REG("$0");   /* MATCH pin: load-bearing for the whole function shape */
    register u32 linked_tag ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u16 component;
    void *vertex;
    void *depth_cue;
    void *projection_flags;
    register u8 *tail ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    register u8 *aux_ptr ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u32 tag_length_mask;
    register u32 tag_addr_mask ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */

    global = (GlobalState **)&D_80083160;
    ASM_KEEP_NV(global);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    scratch = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch);   /* MATCH pin: keeps a statement from moving across a call/branch */
    model_matrix_ptr = scratch;
    ASM_KEEP_NV(model_matrix_ptr);   /* MATCH pin: keeps a statement from moving across a call/branch */
    model_matrix_ptr = (u8 *)((u32)model_matrix_ptr | 0x74);
    model_matrix = model_matrix_ptr;
    transform_matrix = scratch;
    ASM_KEEP_NV(transform_matrix);   /* MATCH pin: keeps a statement from moving across a call/branch */
    transform_matrix = (u8 *)((u32)transform_matrix | 0x54);
    ASM_KEEP_NV(transform_matrix);   /* MATCH pin: keeps a statement from moving across a call/branch */
    tag_addr_mask = 0x00FFFFFF;
    tag_length_mask = 0xFF000000;
    ASM_KEEP(tag_length_mask);   /* MATCH pin: retail immediate-load split depends on it */
    VFIELD(scratch, s32, 0x88) = ((S_8187B1F4_0 *)position)->unk_02;
    VFIELD(scratch, s32, 0x8C) = ((S_8187B1F4_0 *)position)->unk_06;
    ((S_8187B1F4_1 *)scratch)->unk_90 = ((S_8187B1F4_0 *)position)->unk_0A;
    func_800649A0();
    VFIELD(scratch, s32, 0x3C) = 0x1000;
    VFIELD(scratch, s32, 0x38) = 0x1000;
    VFIELD(scratch, s32, 0x34) = 0x1000;
    VFIELD(scratch, u16, 0xA4) = ((S_8187B1F4_2 *)orientation)->unk_16;
    VFIELD(scratch, u16, 0xA8) = ((S_8187B1F4_2 *)orientation)->unk_1A;
    component = ((S_8187B1F4_2 *)orientation)->unk_18;
    aux_ptr = (u8 *)model_matrix;
    ((S_8187B1F4_1 *)scratch)->unk_A6 = component;
    func_80065820(scratch + 0xA4, aux_ptr);
    func_80064AE0(&view_matrix);
    func_80064840(&view_matrix, model_matrix, transform_matrix);
    func_80064BC0(transform_matrix, scratch + 0x34);
    func_80064D80(transform_matrix);
    func_80064CF0(transform_matrix);
    state = global[0];
    ordering_table = (u8 *)state;
    state = (GlobalState *)state->next;
    ordering_table += 0xB0;
    VFIELD(scratch, void *, 0x24) = ordering_table;
    VFIELD(scratch, void *, 0x1C) = state;
    point_index = 0;
    if (((S_8187B1F4_3 *)points)->unk_14 > 0) {
        point_coords = (u16 *)points;
        do {
            VFIELD(scratch, u16, 4) = point_coords[0xB];
            VFIELD(scratch, u16, 6) = point_coords[0x22];
            vertex = scratch + 4;
            component = point_coords[0x39];
            state = global[0];
            depth_cue = scratch + 0xD0;
            VFIELD(scratch, u16, 8) = component;
            point_packet = state->next;
            projection_flags = scratch + 0xD4;
            state->next = point_packet + 0xC;
            depth = func_80065420(vertex, point_packet + 8,
                                    depth_cue, projection_flags);
            VFIELD(scratch, u32, 0x100) = depth;
            if (depth < 0x1E0U) {
                ((S_8187B1F4_4 *)point_packet)->unk_04.at00.v = ((S_8187B1F4_3 *)points)->unk_00;
                ((S_8187B1F4_4 *)point_packet)->unk_04.at00u.v = (s8)((((S_8187B1F4_4 *)point_packet)->unk_04.at00p.v *
                    ((S_8187B1F4_3 *)points)->unk_10) / ((S_8187B1F4_3 *)points)->unk_12);
                ((S_8187B1F4_4 *)point_packet)->unk_04.at01.v = (u8)((((S_8187B1F4_4 *)point_packet)->unk_04.at01.v *
                    ((S_8187B1F4_3 *)points)->unk_10) / ((S_8187B1F4_3 *)points)->unk_12);
                ((S_8187B1F4_4 *)point_packet)->unk_04.at02.v = (u8)((((S_8187B1F4_4 *)point_packet)->unk_04.at02.v *
                    ((S_8187B1F4_3 *)points)->unk_10) / ((S_8187B1F4_3 *)points)->unk_12);
                ((S_8187B1F4_4 *)point_packet)->unk_00.at03.v = 2;
                ((S_8187B1F4_4 *)point_packet)->unk_04.at03.v = 0x6A;
                ((S_8187B1F4_4 *)point_packet)->unk_00.at00.v =
                    (((S_8187B1F4_4 *)point_packet)->unk_00.at00.v & tag_length_mask) |
                    (((S_8187B1F4_5 *)((u8 *)VFIELD(scratch, void *, 0x24) +
                           VFIELD(scratch, u32, 0x100) * 4))->unk_00 & tag_addr_mask);
                tail = (u8 *)(VFIELD(scratch, u32, 0x100) * 4);
                tail += (u32)VFIELD(scratch, void *, 0x24);
                linked_tag =
                    (((S_8187B1F4_6 *)tail)->unk_00 & tag_length_mask) |
                    ((u32)point_packet & tag_addr_mask);
                ((S_8187B1F4_6 *)tail)->unk_00 = linked_tag;
                draw_mode_packet = global[0]->next;
                global[0]->next = draw_mode_packet + 0xC;
                func_80067F20(draw_mode_packet, 0, 0,
                              func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
                ((S_8187B1F4_7 *)draw_mode_packet)->unk_00 =
                    (((S_8187B1F4_7 *)draw_mode_packet)->unk_00 & tag_length_mask) |
                    (((S_8187B1F4_5 *)((u8 *)VFIELD(scratch, void *, 0x24) +
                           VFIELD(scratch, u32, 0x100) * 4))->unk_00 & tag_addr_mask);
                state = (GlobalState *)(VFIELD(scratch, u32, 0x100) * 4);
                state = (GlobalState *)((u8 *)state +
                                        (u32)VFIELD(scratch, void *, 0x24));
                ((S_8187B1F4_8 *)state)->unk_00 =
                    (((S_8187B1F4_8 *)state)->unk_00 & tag_length_mask) |
                    ((u32)draw_mode_packet & tag_addr_mask);
            }
            point_count = ((S_8187B1F4_3 *)points)->unk_14;
            ASM_KEEP(point_count);   /* MATCH pin: keeps a statement from moving across a call/branch */
            point_index += 1;
            point_coords += 1;
        } while (point_index < point_count);
    }
    ASM_USE(transform_matrix);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    func_80064A40();
    tail = ((S_8187B1F4_3_pre *)points)[-1].unk_00;
    points = tail + 0x20;
    if (tail != 0) {
        aux_ptr = ((S_8187B1F4_6 *)tail)->unk_08;
        point_packet = ((S_8187B1F4_6 *)tail)->unk_0C;
        ASM_USE2(points, aux_ptr);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        ASM_USE2(tail, point_packet);   /* MATCH pin: retail basic-block layout depends on it */
        func_80024A54();
    }
#ifndef __mips__
    hard_zero = 0;
#endif
    result = hard_zero;
    return result;
}
