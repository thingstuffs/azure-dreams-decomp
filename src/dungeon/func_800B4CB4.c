#include "common.h"

typedef struct S_800BA414_0 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0x9C];
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u8 pad_F0[0x10];
    u32 unk_100;
    u16 unk_104;
} S_800BA414_0;   /* scratch in func_800BA414 */

typedef struct S_800BA414_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BA414_1;   /* arg1 in func_800BA414 */

typedef struct S_800BA414_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800BA414_2;   /* state in func_800BA414 */

typedef struct S_800BA414_3 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
} S_800BA414_3;   /* prim in func_800BA414 */

typedef struct S_800BA414_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800BA414_4;   /* owner in func_800BA414 */

typedef struct S_800BA414_5 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800BA414_5;   /* *global in func_800BA414 */


extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern u32 func_80065590(void *, void *, void *, void *, void *, void *,
                        void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_800666E0(void *);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern s8 D_80083160[];

/* Project a quad and enqueue it with its draw mode when depth and screen bounds allow. */
void func_800BA414(void *unused, S_800BA414_1 *position, void *owner_data, s16 depth_bias)
{
    u8 *scratch;
    u8 *prim;
    u8 **state_slot;
    S_800BA414_4 *owner;
    s16 depth_offset;
    u8 *rotation;
    u8 *local_matrix;
    u8 *view_matrix;
    u8 *combined_matrix;
    u8 *vertex_0;
    u8 *vertex_1;
    u8 *vertex_2;
    u8 *mode_ptr;
    u8 *mode_zero;
    u8 *vertex_3;
    u8 *transform_flags;
    u8 *depth_cue;
    u8 *state;
    u8 *quad;
    u8 *draw_mode;
    u32 ot_index;
    u32 clip_test;
    s32 first_pair_visible;
    s32 first_three_visible;
    s32 third_visible;
    s32 corner_visible;

    (void)unused;
    state = *(u8 **)D_80083160;
    scratch = (u8 *)0x1F800000;
    owner = owner_data;
    depth_offset = depth_bias;
    ((S_800BA414_0 *)scratch)->unk_20 = state + 0xB0;
    ((S_800BA414_0 *)scratch)->unk_E4 = position->unk_02;
    ((S_800BA414_0 *)scratch)->unk_E8 = position->unk_06;
    ((S_800BA414_0 *)scratch)->unk_EC = position->unk_0A;
    prim = ((S_800BA414_2 *)state)->unk_8D0;
    state_slot = (u8 **)D_80083160;

    func_800649A0();
    rotation = scratch;
    rotation = (u8 *)((u32)rotation | 0x100);
    local_matrix = scratch;
    local_matrix = (u8 *)((u32)local_matrix | 0xD0);
    ((S_800BA414_0 *)scratch)->unk_100 = 0;
    ((S_800BA414_0 *)scratch)->unk_104 = 0;
    func_80065820(rotation, local_matrix);
    view_matrix = scratch;
    view_matrix = (u8 *)((u32)view_matrix | 0x11C);
    func_80064AE0(view_matrix);
    view_matrix = scratch;
    view_matrix = (u8 *)((u32)view_matrix | 0x11C);
    local_matrix = scratch;
    local_matrix = (u8 *)((u32)local_matrix | 0xD0);
    combined_matrix = scratch;
    combined_matrix = (u8 *)((u32)combined_matrix | 0x50);
    func_80064840(view_matrix, local_matrix, combined_matrix);
    combined_matrix = scratch;
    combined_matrix = (u8 *)((u32)combined_matrix | 0x50);
    func_80064D80(combined_matrix);
    combined_matrix = scratch;
    combined_matrix = (u8 *)((u32)combined_matrix | 0x50);
    func_80064CF0(combined_matrix);

    depth_cue = scratch;
    depth_cue = (u8 *)((u32)depth_cue | 0x90);
    transform_flags = scratch;
    transform_flags = (u8 *)((u32)transform_flags | 0x94);
    vertex_0 = scratch;
    vertex_0 = (u8 *)((u32)vertex_0 | 0x70);
    vertex_1 = scratch;
    vertex_1 = (u8 *)((u32)vertex_1 | 0x78);
    vertex_2 = scratch;
    vertex_2 = (u8 *)((u32)vertex_2 | 0x80);
    vertex_3 = scratch;
    vertex_3 = (u8 *)((u32)vertex_3 | 0x88);
    ot_index = (func_80065590(vertex_0, vertex_1, vertex_2, vertex_3,
                           prim + 8, prim + 0xC, prim + 0x10, prim + 0x14,
                           depth_cue, transform_flags) -
             depth_offset) - 8;
    ((S_800BA414_0 *)scratch)->unk_C0 = ot_index;

    if (ot_index < 0x1E0U) {
        first_pair_visible = 0;
        clip_test = ((S_800BA414_3 *)prim)->unk_08;
        clip_test = (u16)(clip_test + 0x20);
        if (clip_test < 0x181U) {
            clip_test = ((S_800BA414_3 *)prim)->unk_0A;
            clip_test = (u16)(clip_test + 0x20);
            first_pair_visible = clip_test < 0x121U;
        }
        corner_visible = 0;
        clip_test = ((S_800BA414_3 *)prim)->unk_0C;
        clip_test = (u16)(clip_test + 0x20);
        if (clip_test < 0x181U) {
            clip_test = ((S_800BA414_3 *)prim)->unk_0E;
            clip_test = (u16)(clip_test + 0x20);
            corner_visible = clip_test < 0x121U;
        }
        first_three_visible = 0;
        first_pair_visible |= corner_visible;
        clip_test = ((S_800BA414_3 *)prim)->unk_10;
        clip_test = (u16)(clip_test + 0x20);
        if (clip_test < 0x181U) {
            clip_test = ((S_800BA414_3 *)prim)->unk_12;
            clip_test = (u16)(clip_test + 0x20);
            first_three_visible = clip_test < 0x121U;
        }
        corner_visible = 0;
        third_visible = first_three_visible;
        first_three_visible = first_pair_visible | third_visible;
        clip_test = ((S_800BA414_3 *)prim)->unk_14;
        clip_test = (u16)(clip_test + 0x20);
        if (clip_test < 0x181U) {
            clip_test = ((S_800BA414_3 *)prim)->unk_16;
            clip_test = (u16)(clip_test + 0x20);
            corner_visible = clip_test < 0x121U;
        }
        clip_test = first_three_visible | corner_visible;

        if (clip_test != 0) {
            ((S_800BA414_3 *)prim)->unk_04.at00.v = owner->unk_0C;
            func_800666E0(prim);
            quad = prim;
            draw_mode = prim + 0x18;
            ((S_800BA414_3 *)prim)->unk_04.at03.v |= 2;
            prim += 0x24;
            func_8006658C(((S_800BA414_0 *)scratch)->unk_20 +
                              ((S_800BA414_0 *)scratch)->unk_C0 * 4,
                          quad);
            mode_ptr = draw_mode;
            mode_zero = 0;
            func_80067F20(mode_ptr, (s32)mode_zero, (s32)mode_zero, 0x20, 0);
            func_8006658C(((S_800BA414_0 *)scratch)->unk_20 +
                              ((S_800BA414_0 *)scratch)->unk_C0 * 4,
                          draw_mode);
        }
    }

    ((S_800BA414_5 *)(*state_slot))->unk_8D0 = prim;
    func_80064A40();
}
