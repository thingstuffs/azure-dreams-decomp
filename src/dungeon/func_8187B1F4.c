#include "modules/dungeon_native_abi.h"
#include "shared/game_work.h"

typedef struct S_8187B1F4_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8187B1F4_0;   /* arg1 in func_800249F4 */

typedef struct S_8187B1F4_1 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x12];
    u16 unk_A6;
} S_8187B1F4_1;   /* scratch in func_800249F4 */

typedef struct S_8187B1F4_2 {
    u8 pad_00[0x16];
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_8187B1F4_2;   /* arg2 in func_800249F4 */

typedef struct S_8187B1F4_3_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_8187B1F4_3_pre;   /* the 0x8 bytes before arg0 in func_800249F4, addressed as arg0[-1] */

typedef struct S_8187B1F4_3 {
    s32 unk_00;
    u8 pad_04[0xC];
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
} S_8187B1F4_3;   /* arg0 in func_800249F4 */

typedef struct S_8187B1F4_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s8 v; } at00u;
        struct { u8 v; } at00p;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x3]; s8 v; } at03;
    } unk_04;   /* overlapping accesses */
} S_8187B1F4_4;   /* temp_s0 in func_800249F4 */

typedef struct S_8187B1F4_5 {
    u32 unk_00;
} S_8187B1F4_5;   /* (u8 *)VFIELD(scratch, void *, 0x24) +
                           VFIELD(scratch, u32, 0x100) * 4 in func_800249F4 */

typedef struct S_8187B1F4_6 {
    u32 unk_00;
    u8 pad_04[0x4];
    u8 * unk_08;
    u8 * unk_0C;
} S_8187B1F4_6;   /* tail in func_800249F4 */

typedef struct S_8187B1F4_7 {
    u32 unk_00;
} S_8187B1F4_7;   /* temp_s0_2 in func_800249F4 */

typedef struct S_8187B1F4_8 {
    u32 unk_00;
} S_8187B1F4_8;   /* state in func_800249F4 */


#define VFIELD(base, type, offset) (((struct { u8 _pad_[offset]; type v; } *)(base))->v)

typedef struct GlobalState {
    u8 pad[0x8D0];
    u8 *next;
} GlobalState;

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

typedef struct GlobalRef {
    GlobalState *cur;
} GlobalRef;

typedef struct PrimitiveTag { unsigned addr : 24; unsigned len : 8; } PrimitiveTag;

/* Projects points and adds brightness-scaled pixel primitives to the ordering table. */
s32 func_800249F4(u8 *points, u8 *position, u8 *orientation) {
    s32 view_matrix[8];
    void *model_matrix;
    u8 *scratch;
    u8 *transform_matrix;
    GlobalRef *global;
    register GlobalState *state;
    GlobalState *cur_state;
    GlobalState *tag_state;
    u8 *ordering_table;
    u8 *point_packet;
    u8 *draw_mode_packet;
    u8 *unused_ptr;
    s32 point_index;
    u16 *point_coords;
    u32 depth;
    s32 point_count;
    s32 hard_zero = 0;
    u16 component;
    void *vertex;
    void *depth_cue;
    void *projection_flags;
    u8 *tail;
    u8 *tail_2;

    global = (GlobalRef *)((GlobalState * *)(&gameWork));
    scratch = (u8 *)0x1F800000;
    model_matrix = (u8 *)((u32)scratch | 0x74);
    transform_matrix = (u8 *)((u32)scratch | 0x54);
    do {
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
        ((S_8187B1F4_1 *)scratch)->unk_A6 = component;
        func_80065820(scratch + 0xA4, ((u8 *)model_matrix));
        func_80064AE0(&view_matrix);
        func_80064840(&view_matrix, model_matrix, transform_matrix);
        func_80064BC0(transform_matrix, scratch + 0x34);
        func_80064D80(transform_matrix);
        func_80064CF0(transform_matrix);
        state = global->cur;
        ordering_table = (u8 *)state;
        state = (GlobalState *)state->next;
        ordering_table += 0xB0;
        VFIELD(scratch, void *, 0x24) = ordering_table;
        VFIELD(scratch, void *, 0x1C) = state;
        point_index = 0;
        if (((S_8187B1F4_3 *)points)->unk_14 > 0) {
            point_coords = (u16 *)points;
            do {
                VFIELD(scratch, u16, 4) = point_coords[point_index + 0xB];
                VFIELD(scratch, u16, 6) = point_coords[point_index + 0x22];
                vertex = scratch + 4;
                component = point_coords[point_index + 0x39];
                cur_state = global->cur;
                depth_cue = scratch + 0xD0;
                VFIELD(scratch, u16, 8) = component;
                point_packet = cur_state->next;
                projection_flags = scratch + 0xD4;
                cur_state->next = point_packet + 0xC;
                depth = func_80065420(vertex, point_packet + 8,
                                      depth_cue, projection_flags);
                VFIELD(scratch, u32, 0x100) = depth;
                if (depth < 0x1E0U) {
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at00.v = ((S_8187B1F4_3 *)points)->unk_00;
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at00u.v =
                        (s8)((((S_8187B1F4_4 *)point_packet)->unk_04.at00p.v *
                        ((S_8187B1F4_3 *)points)->unk_10) / ((S_8187B1F4_3 *)points)->unk_12);
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at01.v =
                        (u8)((((S_8187B1F4_4 *)point_packet)->unk_04.at01.v *
                        ((S_8187B1F4_3 *)points)->unk_10) / ((S_8187B1F4_3 *)points)->unk_12);
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at02.v =
                        (u8)((((S_8187B1F4_4 *)point_packet)->unk_04.at02.v *
                        ((S_8187B1F4_3 *)points)->unk_10) / ((S_8187B1F4_3 *)points)->unk_12);
                    ((S_8187B1F4_4 *)point_packet)->unk_00.at03.v = 2;
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at03.v = 0x6A;
                    ((PrimitiveTag *)point_packet)->addr =
                        ((PrimitiveTag *)((u8 *)VFIELD(scratch, void *, 0x24) +
                               VFIELD(scratch, u32, 0x100) * 4))->addr;
                    tail = (u8 *)(VFIELD(scratch, u32, 0x100) * 4);
                    tail += (u32)VFIELD(scratch, void *, 0x24);
                    ((PrimitiveTag *)tail)->addr = (u32)point_packet;
                    draw_mode_packet = global->cur->next;
                    global->cur->next = draw_mode_packet + 0xC;
                    func_80067F20(draw_mode_packet, 0, 0,
                                  func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
                    ((PrimitiveTag *)draw_mode_packet)->addr =
                        ((PrimitiveTag *)((u8 *)VFIELD(scratch, void *, 0x24) +
                               VFIELD(scratch, u32, 0x100) * 4))->addr;
                    tag_state = (GlobalState *)(VFIELD(scratch, u32, 0x100) * 4);
                    tag_state = (GlobalState *)((u8 *)tag_state +
                                                (u32)VFIELD(scratch, void *, 0x24));
                    ((PrimitiveTag *)tag_state)->addr = (u32)draw_mode_packet;
                    point_count = ((S_8187B1F4_3 *)points)->unk_14;
                } else {
                    point_count = ((S_8187B1F4_3 *)points)->unk_14;
                }
                point_index += 1;
            } while (point_index < point_count);
        }
        func_80064A40();
        tail_2 = ((S_8187B1F4_3_pre *)points)[-1].unk_00;
        points = tail_2 + 0x20;
        if (tail_2 == 0) {
            break;
        }
        point_packet = ((S_8187B1F4_6 *)tail_2)->unk_0C;
        position = ((u8 *)(((S_8187B1F4_6 *)tail_2)->unk_08));
        orientation = point_packet;
    } while (1);
#ifndef __mips__
    hard_zero = 0;
#endif
    return hard_zero;
}
