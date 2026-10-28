/* One native TU; source order follows the complete ledger cohort. */
#include "dungeon/effect/screen/transform_shade_and_queue_model_quads.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct S_800C9088_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x4];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_800C9088_0;   /* object in transform_shade_and_queue_model_quads */

typedef struct S_800C9088_1 {
    u8 pad_00[0x20];
    union { u8 * s; void * u; } unk_20;   /* accessed as both */
    u8 pad_24[0xC];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x4];
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    u8 pad_62[0xE];
    s32 unk_70;
    u16 unk_74;
    u8 pad_76[0x2];
    s32 unk_78;
    u16 unk_7C;
    u8 pad_7E[0x2];
    s32 unk_80;
    u16 unk_84;
    u8 pad_86[0x2];
    s32 unk_88;
    u16 unk_8C;
    u8 pad_8E[0x32];
    s32 unk_C0;
    u8 pad_C4[0x50];
    volatile s32 unk_114;
} S_800C9088_1;   /* scratch in transform_shade_and_queue_model_quads */

typedef struct S_800C9088_2 {
    u8 unk_00;
    u8 pad_01[0x1];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x3154];
    u8 * unk_3160;
} S_800C9088_2;   /* ptr_s0 in transform_shade_and_queue_model_quads */

   /* state in transform_shade_and_queue_model_quads */

typedef struct S_800C9088_4 {
    u8 * unk_00;
    u8 * unk_04;
    u8 * unk_08;
} S_800C9088_4;   /* descriptor in transform_shade_and_queue_model_quads */



typedef struct S_800C9088_6 {
    s32 unk_00;
} S_800C9088_6;   /* table + next_index * 8 in transform_shade_and_queue_model_quads */

typedef struct S_800C9088_7 {
    s32 unk_00;
} S_800C9088_7;   /* word2_ptr in transform_shade_and_queue_model_quads */

typedef struct S_800C9088_8 {
    s32 unk_00;
} S_800C9088_8;   /* word3_ptr in transform_shade_and_queue_model_quads */

typedef struct S_800C9088_9 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800C9088_9;   /* table + half_index * 8 in transform_shade_and_queue_model_quads */

   /* *(u8 **)state_base in transform_shade_and_queue_model_quads */

typedef struct S_800C9088_12 {
    s32 unk_00;
} S_800C9088_12;   /* table + ((S_800C9088_5 *)indices)->unk_00 * 8 in transform_shade_and_queue_model_quads */

typedef struct S_800C9088_13 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800C9088_13;   /* table + (*(u16 *)((u8 *)ptr_s1 + -0x1D)) * 8 in transform_shade_and_queue_model_quads */


typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

extern void *CompMatrix(void *, void *, void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void ReadRotMatrix(void *);
extern void TransMatrix(void *, void *);
extern void *ScaleMatrix(void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern void func_80065034(void *, void *, void *);
extern s32 NormalClip(s32, s32, s32);
extern s32 RotAverage4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void RotMatrixX(u16, void *);
extern void RotMatrixY(u16, void *);
extern void RotMatrixZ(u16, void *);
extern void AddPrim(void *, void *);
extern void SetPolyGT4(void *);

/* Transform, shade, and enqueue visible textured quads for the model. */
void transform_shade_and_queue_model_quads(void *parent_matrix, void *translation, void *model, s16 depth_bias)
{
    u8 *scratch;
    u8 *indices;
    u8 *positions;
    u8 *normals;
    u8 *packet;
    u8 *base_color;
    u8 *state;
    u8 **state_table = (u8 **)((u8 *)(&g_game_work));
    S_800C9088_4 *descriptor;
    u8 *vertex0;
    u8 *vertex1;
    u8 *vertex2;
    u8 *vertex3;
    s32 vertex_xy;
    u32 vertex_index;
    u32 last_index;
    s32 vertex2_xy;
    s32 vertex3_xy;
    u32 z_index;
    u16 vertex_z;
    u16 vertex3_z;
    S_800C9088_7 *vertex2_pos;
    S_800C9088_8 *vertex3_pos;
    s32 depth;
    s32 winding;
    s32 flags;
    u16 scale_x;
    MATRIX saved_transform;
    s32 screen_xy0, screen_xy1, screen_xy2;


    PushMatrix();

    scale_x = ((S_800C9088_0 *)model)->unk_1C;
    scratch = (u8 *)0x1F800000;
    ((S_800C9088_1 *)scratch)->unk_30 = scale_x;
    ((S_800C9088_1 *)scratch)->unk_34 = ((S_800C9088_0 *)model)->unk_1E;
    ((S_800C9088_1 *)scratch)->unk_38 = ((S_800C9088_0 *)model)->unk_20;
    ((S_800C9088_1 *)scratch)->unk_40 = ((S_800C9088_2 *)translation)->unk_02;
    ((S_800C9088_1 *)scratch)->unk_44 = ((S_800C9088_2 *)translation)->unk_06;
    ((S_800C9088_1 *)scratch)->unk_48 = ((S_800C9088_2 *)translation)->unk_0A;

    ReadRotMatrix(&saved_transform);

    ((S_800C9088_1 *)scratch)->unk_60 = 0x1000;
    ((S_800C9088_1 *)scratch)->unk_58 = 0x1000;
    ((S_800C9088_1 *)scratch)->unk_50 = 0x1000;
    ((S_800C9088_1 *)scratch)->unk_5E = 0;
    ((S_800C9088_1 *)scratch)->unk_5C = 0;
    ((S_800C9088_1 *)scratch)->unk_5A = 0;
    ((S_800C9088_1 *)scratch)->unk_56 = 0;
    ((S_800C9088_1 *)scratch)->unk_54 = 0;
    ((S_800C9088_1 *)scratch)->unk_52 = 0;

    RotMatrixX(((S_800C9088_0 *)model)->unk_16, scratch + 0x50);
    RotMatrixZ(((S_800C9088_0 *)model)->unk_1A, scratch + 0x50);
    RotMatrixY(((S_800C9088_0 *)model)->unk_18, scratch + 0x50);

    if (((S_800C9088_0 *)model)->unk_14 & 1) {
        ((S_800C9088_1 *)scratch)->unk_30 = -((S_800C9088_1 *)scratch)->unk_30;
    }
    if (((S_800C9088_0 *)model)->unk_14 & 2) {
        ((S_800C9088_1 *)scratch)->unk_34 = -((S_800C9088_1 *)scratch)->unk_34;
    }

    ScaleMatrix(scratch + 0x50, scratch + 0x30);
    TransMatrix(scratch + 0x50, scratch + 0x40);
    CompMatrix(scratch + 0x50, parent_matrix, scratch + 0xD0);
    CompMatrix(&saved_transform, scratch + 0xD0, scratch + 0x50);
    SetTransMatrix(scratch + 0x50);
    SetRotMatrix(scratch + 0x50);

    state = state_table[0];
    base_color = (u8 *)model + 0xC;
    ((S_800C9088_1 *)scratch)->unk_20.s = state + 0xB0;
    packet = ((GpuContext *)state)->packetCursor;
    ((S_800C9088_0 *)model)->unk_14 |= 0x8000;

    descriptor = (S_800C9088_4 *)((S_800C9088_0 *)model)->unk_08;
    indices = descriptor->unk_00;
    positions = descriptor->unk_04;
    normals = descriptor->unk_08;

    for (;;) {
    vertex_xy = ((S_800C9088_12 *)(positions + ((u16 *)indices)[0] * 8))->unk_00;
    vertex_index = (*(u16 *)((u8 *)indices + 2));
    ((S_800C9088_1 *)scratch)->unk_70 = vertex_xy;
    vertex_xy = ((S_800C9088_6 *)(positions + vertex_index * 8))->unk_00;
    vertex2_pos = (S_800C9088_7 *)((*(u16 *)((u8 *)indices + 4)) * 8 + (u32)positions);
    ((S_800C9088_1 *)scratch)->unk_78 = vertex_xy;
    last_index = (*(u16 *)((u8 *)indices + 6));
    vertex2_xy = vertex2_pos->unk_00;
    vertex3_pos = (S_800C9088_8 *)(last_index * 8 + (unsigned long)positions);
    ((S_800C9088_1 *)scratch)->unk_80 = vertex2_xy;
    z_index = ((u16 *)indices)[0];
    vertex3_xy = vertex3_pos->unk_00;

    vertex_z = ((S_800C9088_9 *)(positions + z_index * 8))->unk_04;
    ((S_800C9088_1 *)scratch)->unk_74 = vertex_z;

    vertex_z = ((S_800C9088_13 *)(positions + (*(u16 *)((u8 *)indices + 2)) * 8))->unk_04;
    vertex0 = scratch + 0x70;
    ((S_800C9088_1 *)scratch)->unk_7C = vertex_z;

    z_index = (*(u16 *)((u8 *)indices + 4));
    vertex1 = scratch + 0x78;
    vertex_z = ((S_800C9088_9 *)(positions + z_index * 8))->unk_04;
    vertex2 = scratch + 0x80;
    ((S_800C9088_1 *)scratch)->unk_84 = vertex_z;

    z_index = (*(u16 *)((u8 *)indices + 6));
    vertex3 = scratch + 0x88;
    ((S_800C9088_1 *)scratch)->unk_88 = vertex3_xy;
    vertex3_z = ((S_800C9088_9 *)(positions + z_index * 8))->unk_04;

    ((S_800C9088_1 *)scratch)->unk_8C = vertex3_z;
    depth = RotAverage4(vertex0, vertex1,
                          vertex2, vertex3,
                          packet + 8, packet + 0x14,
                          packet + 0x20, packet + 0x2C,
                          scratch + 0x90, scratch + 0x94);
    ((S_800C9088_1 *)scratch)->unk_C0 = depth;

    flags = ((S_800C9088_0 *)model)->unk_14 & 3;
    switch (flags) {
    case 0:
        screen_xy0 = (*(s32 *)((u8 *)packet + 8));
        screen_xy1 = (*(s32 *)((u8 *)packet + 0x14));
        screen_xy2 = (*(s32 *)((u8 *)packet + 0x20));
        break;
    case 1:
        screen_xy0 = (*(s32 *)((u8 *)packet + 0x14));
        screen_xy1 = (*(s32 *)((u8 *)packet + 8));
        screen_xy2 = (*(s32 *)((u8 *)packet + 0x20));
        break;
    case 2:
        screen_xy0 = (*(s32 *)((u8 *)packet + 0x20));
        screen_xy1 = (*(s32 *)((u8 *)packet + 0x14));
        screen_xy2 = (*(s32 *)((u8 *)packet + 8));
        break;
    default:
        screen_xy0 = (*(s32 *)((u8 *)packet + 0x20));
        screen_xy1 = (*(s32 *)((u8 *)packet + 8));
        screen_xy2 = (*(s32 *)((u8 *)packet + 0x14));
        break;
    }
    winding = NormalClip(screen_xy0, screen_xy1, screen_xy2);
    ((S_800C9088_1 *)scratch)->unk_114 = winding;
    if (((S_800C9088_1 *)scratch)->unk_114 > 0) {
        ((S_800C9088_1 *)scratch)->unk_C0 -= depth_bias;
        if ((u32)((S_800C9088_1 *)scratch)->unk_C0 < 0x1E0) {
            func_80065034(normals + (*(u16 *)((u8 *)indices + 0x10)) * 8,
                          base_color, packet + 4);
            func_80065034(normals + (*(u16 *)((u8 *)indices + 0x12)) * 8,
                          base_color, packet + 0x10);
            func_80065034(normals + (*(u16 *)((u8 *)indices + 0x14)) * 8,
                          base_color, packet + 0x1C);
            func_80065034(normals + (*(u16 *)((u8 *)indices + 0x16)) * 8,
                          base_color, packet + 0x28);

            (*(s32 *)((u8 *)packet + 0xC)) = (*(s32 *)((u8 *)indices + 8));
            (*(u16 *)((u8 *)packet + 0xE)) += ((S_800C9088_0 *)model)->unk_12;
            (*(s32 *)((u8 *)packet + 0x18)) = (*(s32 *)((u8 *)indices + 0xC));
            if (((S_800C9088_0 *)model)->unk_10 != 0) {
                (*(u16 *)((u8 *)packet + 0x1A)) =
                    ((*(u16 *)((u8 *)packet + 0x1A)) & 0xFF9F) +
                    ((S_800C9088_0 *)model)->unk_10;
            }
            (*(u16 *)((u8 *)packet + 0x24)) = (*(u16 *)((u8 *)indices + 0x1A));
            (*(u16 *)((u8 *)packet + 0x30)) = (*(u16 *)((u8 *)indices + 0x1C));

            SetPolyGT4(packet);
            flags = ((S_800C9088_0 *)model)->unk_14;
            if (flags & 8) {
                if (flags & 4) {
                    packet[7] |= 2;
                }
            }
            AddPrim((u8 *)((S_800C9088_1 *)scratch)->unk_20.u +
                          ((S_800C9088_1 *)scratch)->unk_C0 * 4,
                          packet);
            packet += 0x34;
            ((S_800C9088_0 *)model)->unk_14 &= 0x7FFF;
        }
    }

    if (indices[0x1E] == 1 && ((s8 *)indices)[0x1F] < 0) {
        break;
    }
    indices += 0x20;
    }

    PopMatrix();
    ((GpuContext *)state_table[0])->packetCursor = packet;
}
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C95C0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800C95C0_0;   /* arg1 in queue_linked_visible_rectangle_copies */

typedef struct S_800C95C0_1_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_800C95C0_1_pre;   /* the 0x8 bytes before state in queue_linked_visible_rectangle_copies, addressed as state[-1] */


extern s32 RotTransPers(void *, void *, ...);
struct S_Rect;
struct S_Arg1;
extern void queue_visible_rectangle_copy(struct S_Rect *copy_rect, struct S_Arg1 *source);

/* Updates each linked state from its input values and delta using scratchpad memory. */
s32 queue_linked_visible_rectangle_copies(void *initial_state, void *input_values, s16 *initial_delta) {
    void *state = initial_state;
    s16 *delta = initial_delta;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *next_node;

    for (;;) {
        *(u16 *)(scratch + 0) = ((S_800C95C0_0 *)input_values)->unk_02;
        *(u16 *)(scratch + 2) = (*(u16 *)((u8 *)input_values + 6));
        *(u16 *)(scratch + 4) = (*(u16 *)((u8 *)input_values + 0xA));
        *(s32 *)(scratch + 0xC0) =
            RotTransPers((void *)scratch, (void *)(scratch + 0xB8),
                          (void *)(scratch + 0x90), (void *)(scratch + 0x94)) -
            *(s16 *)((u8 *)delta + 6);
        queue_visible_rectangle_copy(state, scratch);
        next_node = ((S_800C95C0_1_pre *)state)[-1].unk_00;
        if (next_node == NULL)
            break;
        state = next_node + 0x20;
        input_values = *(u8 **)(next_node + 8);
        delta = *(u8 **)(next_node + 0xC);
    }
    return 0;
}
#include "common.h"

struct S_Rect;
struct S_Arg1;
extern void queue_visible_rectangle_copy(struct S_Rect *copy_rect, struct S_Arg1 *source);

/* Processes linked entries with position values staged in scratchpad memory. */
s32 process_linked_entries_at_position(void *entry_data, void *position) {
    register u8 *data = entry_data;
    register u8 *scratch = (u8 *)0x1F800000;
    register u8 *next_node;
    s32 offset;

    for (;;) {
        offset = (s32)((u32)*(u16 *)data << 16) >> 17;
        *(u16 *)(scratch + 0xB8) = *(u16 *)((u8 *)position + 2) - offset;
        *(u16 *)(scratch + 0xBA) = *(u16 *)((u8 *)position + 6);
        *(s32 *)(scratch + 0xC0) = *(s16 *)((u8 *)position + 10);
        queue_visible_rectangle_copy(data, scratch);
        next_node = *(u8 **)(data - 8);
        if (next_node == 0) {
            break;
        }
        data = next_node + 0x20;
        position = *(u8 **)(next_node + 8);
    }
    return 0;
}
#include "common.h"

typedef struct {
    char pad0[0x8D0];
    u8 *field_8D0;
} Ctx;

typedef struct S_Rect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} S_Rect;

typedef struct S_Arg1 {
    char pad0[0xB8];
    s16 x;
    s16 y;
    char pad_BC[4];
    u32 index;
} S_Arg1;

typedef struct {
    u16 x;
    s16 y;
    u16 w;
    u16 h;
} S_Stack;

extern u8 resident_globals_page[];
extern u8 upper_draw_context[16];
extern void func_80066890(u8 *dst, S_Stack *rect, s32 x, s32 y);
extern void AddPrim(void *, void *);

/* Queue a rectangle copy when both source and destination fit on screen. */
void queue_visible_rectangle_copy(S_Rect *copy_rect, S_Arg1 *source) {
    S_Stack source_rect;
    s16 source_y, width, source_x, height;
    s32 dest_y, second_buffer, dest_x, buffer_y;
    u8 *packet;
    u8 *cursor;
    Ctx **active_ctx;

    active_ctx = (Ctx **)((u8 *)&resident_globals_page + 0x3160);
    cursor = (*(Ctx **)((u8 *)&resident_globals_page + 0x3160))->field_8D0;
    second_buffer = *(Ctx **)((u8 *)&resident_globals_page + 0x3160) != (Ctx *)upper_draw_context;
    if (source->index < 480) {
        source_x = source->x;
        source_y = source->y;
        dest_x = source_x + copy_rect->w;
        dest_y = source_y + copy_rect->h;
        if (dest_x >= 0) {
            width = copy_rect->x;
            if (((dest_x + width) < 320) && (dest_y >= 0)) {
                height = copy_rect->y;
                if (((dest_y + height) < 224) && (source_x >= 0) && ((source_x + width) < 320) && (source_y >= 0)
                    && ((source_y + height) < 224)) {
                    source_rect.x = source->x;
                    buffer_y = source->y;
                    if ((s16)second_buffer) {
                        buffer_y += 224;
                    }
                    source_rect.y = buffer_y;
                    source_rect.w = copy_rect->x;
                    source_rect.h = copy_rect->y;
                    func_80066890(cursor, &source_rect, source_x + copy_rect->w, (s16)buffer_y + copy_rect->h);
                    packet = cursor;
                    cursor += 24;
                    AddPrim((u8 *)(*(Ctx **)((u8 *)&resident_globals_page + 0x3160)) + ((source->index * 4) + 0xB0), packet);
                }
            }
        }
    }
    (*active_ctx)->field_8D0 = cursor;
}
