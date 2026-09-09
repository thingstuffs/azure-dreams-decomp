#include "common.h"

typedef struct S_80166968_0 {
    u8 pad_00[0x24];
    union { u8 * p; u32 * p2; } unk_24;   /* accessed as both */
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x48];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x6];
    s16 unk_B0;
    s16 unk_B2;
    s16 unk_B4;
    u8 pad_B6[0x2];
    s16 unk_B8;
    s16 unk_BA;
    s16 unk_BC;
    u8 pad_BE[0x2];
    s16 unk_C0;
    s16 unk_C2;
    s16 unk_C4;
    u8 pad_C6[0x2];
    s16 unk_C8;
    s16 unk_CA;
    s16 unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} S_80166968_0;   /* scratch in func_80166968 */

typedef struct S_80166968_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80166968_1;   /* arg1 in func_80166968 */

typedef struct S_80166968_2 {
    u8 pad_00[0x8];
    s8 * unk_08;
    u8 pad_0C[0x3];
    u8 unk_0F;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_80166968_2;   /* arg2 in func_80166968 */

typedef struct S_80166968_3 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80166968_3;   /* *global in func_80166968 */

typedef struct S_80166968_4 {
    u32 unk_00;
    u8 pad_04[0x70];
    s16 unk_74;
    s16 unk_76;
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    s16 unk_7E;
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    s16 unk_86;
    s16 unk_88;
    s16 unk_8A;
} S_80166968_4;   /* arg0 in func_80166968 */

typedef struct S_80166968_5 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_80166968_5;   /* packet in func_80166968 */



typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern u16 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);
extern u8 *D_80083160;

/* Project edge midpoints and queue line and draw-mode packets in the ordering table. */
void func_80166968(S_80166968_4 *geometry, S_80166968_1 *position, u8 *render_data, s32 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *render_state = D_80083160;
    u32 draw_flags;
    u8 **render_state_ref;
    u8 *packet;
    s8 *texture_entry;
    u32 color;
    s32 zero;
    s32 ot_index;
    s32 mid_a_x;
    s32 mid_b_x;
    s32 mid_a_y;
    s32 mid_b_y;
    s32 mid_a_z;
    s32 mid_b_z;
    u8 *point_a;
    u8 *point_b;
    u8 *point_a_copy;
    u8 *point_b_copy;
    u32 address_mask;
    u32 length_mask;
    u16 render_flags;
    s32 saved_depth_bias;
    MATRIX matrix;

    ((S_80166968_0 *)scratch)->unk_24.p = render_state + 0xB0;
    address_mask = 0x00FFFFFF;
    ((S_80166968_0 *)scratch)->unk_88 = position->unk_02;
    ((S_80166968_0 *)scratch)->unk_8C = position->unk_06;
    saved_depth_bias = depth_bias;
    ((S_80166968_0 *)scratch)->unk_90 = position->unk_0A;
    ((S_80166968_2 *)render_data)->unk_14 |= 0x8000;
    render_state_ref = &D_80083160;
    func_800649A0();

    ((S_80166968_0 *)scratch)->unk_3C = 0x2000;
    ((S_80166968_0 *)scratch)->unk_38 = 0x2000;
    ((S_80166968_0 *)scratch)->unk_34 = 0x2000;
    ((S_80166968_0 *)scratch)->unk_A4 = ((S_80166968_2 *)render_data)->unk_16;
    ((S_80166968_0 *)scratch)->unk_A8 = ((S_80166968_2 *)render_data)->unk_1A;
    ((S_80166968_0 *)scratch)->unk_A6 = ((S_80166968_2 *)render_data)->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture_entry = ((S_80166968_2 *)render_data)->unk_08;
    length_mask = 0xFF000000;
    ((S_80166968_0 *)scratch)->unk_28 = ((S_80166968_2 *)render_data)->unk_14;

    for (;;) {
        packet = ((S_80166968_3 *)(*render_state_ref))->unk_8D0;
        ((S_80166968_3 *)(*render_state_ref))->unk_8D0 = packet + 0x10;

        point_a = scratch + 0xB0;
        mid_a_x = (geometry->unk_74 + geometry->unk_7A) / 2;
        ((S_80166968_0 *)scratch)->unk_C0 = mid_a_x;
        ((S_80166968_0 *)scratch)->unk_B0 = mid_a_x;
        point_b = scratch + 0xB8;
        mid_b_x = (geometry->unk_80 + geometry->unk_86) / 2;
        ((S_80166968_0 *)scratch)->unk_C8 = mid_b_x;
        ((S_80166968_0 *)scratch)->unk_B8 = mid_b_x;
        point_a_copy = scratch + 0xC0;
        mid_a_y = (geometry->unk_76 + geometry->unk_7C) / 2;
        ((S_80166968_0 *)scratch)->unk_C2 = mid_a_y;
        ((S_80166968_0 *)scratch)->unk_B2 = mid_a_y;
        point_b_copy = scratch + 0xC8;
        mid_b_y = (geometry->unk_82 + geometry->unk_88) / 2;
        ((S_80166968_0 *)scratch)->unk_CA = mid_b_y;
        ((S_80166968_0 *)scratch)->unk_BA = mid_b_y;
        mid_a_z = (geometry->unk_78 + geometry->unk_7E) / 2;
        ((S_80166968_0 *)scratch)->unk_C4 = mid_a_z;
        ((S_80166968_0 *)scratch)->unk_B4 = mid_a_z;
        mid_b_z = (geometry->unk_84 + geometry->unk_8A) / 2;
        ((S_80166968_0 *)scratch)->unk_CC = mid_b_z;
        ((S_80166968_0 *)scratch)->unk_BC = mid_b_z;

        ot_index = func_80065590(point_a, point_b, point_a_copy, point_b_copy,
                              packet + 8, packet + 0xC,
                              packet + 8, packet + 0xC,
                              scratch + 0xD0, scratch + 0xD4) - (s16)saved_depth_bias - 6;
        ((S_80166968_0 *)scratch)->unk_100 = ot_index;

        render_flags = ((S_80166968_0 *)scratch)->unk_28;
        if (render_flags & 8) {
            if (render_flags & 4) {
                draw_flags = ((S_80166968_2 *)render_data)->unk_0F | 2;
            } else {
                draw_flags = ((S_80166968_2 *)render_data)->unk_0F & 0xFD;
            }
            ((S_80166968_2 *)render_data)->unk_0F = draw_flags;
        }

        zero = 0;
        color = geometry->unk_00;
        ((S_80166968_5 *)packet)->unk_00.at03.v = 3;
        ((S_80166968_5 *)packet)->unk_04.at00.v = color;
        ((S_80166968_5 *)packet)->unk_04.at03.v = 0x42;

        ((S_80166968_5 *)packet)->unk_00.at00.v = (((S_80166968_5 *)packet)->unk_00.at00.v & length_mask) |
            ((*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) & address_mask);
        (*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) =
            ((*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) & length_mask) |
            ((u32)packet & address_mask);

        packet = ((S_80166968_3 *)(*render_state_ref))->unk_8D0;
        ((S_80166968_3 *)(*render_state_ref))->unk_8D0 = packet + 0xC;
        func_80067F20(packet, zero, zero, func_80066460(zero, 1, zero, zero) & 0xFFFF, zero);

        ((S_80166968_5 *)packet)->unk_00.at00.v = (((S_80166968_5 *)packet)->unk_00.at00.v & length_mask) |
            ((*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) & address_mask);
        packet = (u8 *)((u32)packet & address_mask);
        (*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) =
            ((*(u32 *)((u8 *)(((S_80166968_0 *)scratch)->unk_24.p2) + ((S_80166968_0 *)scratch)->unk_100 * 4)) & length_mask) |
            (u32)packet;

        if (*texture_entry < 0) {
            break;
        }
        texture_entry += 0xC;
    }

    func_80064A40();
}
