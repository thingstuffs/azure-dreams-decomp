#include "common.h"


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
extern void func_800666E0(void *);
extern u8 D_80083160[];


typedef struct S_800D6170_0 {
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
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    u8 pad_B6[0x2];
    u16 unk_B8;
    u16 unk_BA;
    u16 unk_BC;
    u8 pad_BE[0x2];
    u16 unk_C0;
    u16 unk_C2;
    u16 unk_C4;
    u8 pad_C6[0x2];
    u16 unk_C8;
    u16 unk_CA;
    u16 unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} S_800D6170_0;   /* scratch in func_800D6170 */

typedef struct S_800D6170_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D6170_1;   /* arg1 in func_800D6170 */

typedef struct S_800D6170_2 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_800D6170_2;   /* arg2 in func_800D6170 */

typedef struct S_800D6170_3 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800D6170_3;   /* *global in func_800D6170 */

typedef struct S_800D6170_4 {
    u32 unk_00;
    u32 unk_04;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
} S_800D6170_4;   /* packet in func_800D6170 */

/* Project depth-sliced quads and link visible packets into the ordering table. */
void func_800D6170(void *geometry, S_800D6170_1 *position, S_800D6170_2 *render_state, s16 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 **render_context = (u8 **)D_80083160;
    u8 *packet;
    s32 ot_index;
    register s32 depth_span ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 coord_index;
    u32 address_mask;
    u32 length_mask;
    u16 depth_edges[4];
    MATRIX matrix;

    ((S_800D6170_0 *)scratch)->unk_24.p = *render_context + 0xB0;
    ((S_800D6170_0 *)scratch)->unk_88 = position->unk_02;
    ((S_800D6170_0 *)scratch)->unk_8C = position->unk_06;
    ((S_800D6170_0 *)scratch)->unk_90 = position->unk_0A;
    render_state->unk_14 |= 0x8000;

    func_800649A0();

    ((S_800D6170_0 *)scratch)->unk_3C = 0x2000;
    ((S_800D6170_0 *)scratch)->unk_38 = 0x2000;
    ((S_800D6170_0 *)scratch)->unk_34 = 0x2000;
    ((S_800D6170_0 *)scratch)->unk_A4 = render_state->unk_16;
    ((S_800D6170_0 *)scratch)->unk_A8 = render_state->unk_1A;
    ((S_800D6170_0 *)scratch)->unk_A6 = render_state->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    ((S_800D6170_0 *)scratch)->unk_28 = render_state->unk_14;
    for (coord_index = 0; coord_index < 4; coord_index++) {
        depth_edges[coord_index] = (*(u16 *)((u8 *)geometry + 0x54 + coord_index * 2));
    }

    depth_span = (s16)depth_edges[0];
    depth_span -= (s16)depth_edges[2];
    if (depth_span < 0) {
        depth_span = -depth_span;
    }
    if (depth_span >= 0x11) {
        address_mask = 0x00FFFFFF;
        length_mask = 0xFF000000;
        do {
            ((S_800D6170_0 *)scratch)->unk_B0 = (*(u16 *)((u8 *)geometry + 0x44));
            ((S_800D6170_0 *)scratch)->unk_B8 = (*(u16 *)((u8 *)geometry + 0x46));
            ((S_800D6170_0 *)scratch)->unk_C0 = (*(u16 *)((u8 *)geometry + 0x48));
            ((S_800D6170_0 *)scratch)->unk_C8 = (*(u16 *)((u8 *)geometry + 0x4A));
            ((S_800D6170_0 *)scratch)->unk_B2 = (*(u16 *)((u8 *)geometry + 0x4C));
            ((S_800D6170_0 *)scratch)->unk_BA = (*(u16 *)((u8 *)geometry + 0x4E));
            ((S_800D6170_0 *)scratch)->unk_C2 = (*(u16 *)((u8 *)geometry + 0x50));
            ((S_800D6170_0 *)scratch)->unk_CA = (*(u16 *)((u8 *)geometry + 0x52));
            ((S_800D6170_0 *)scratch)->unk_B4 = depth_edges[2] - 0x10;
            ((S_800D6170_0 *)scratch)->unk_BC = depth_edges[3] - 0x10;
            ((S_800D6170_0 *)scratch)->unk_C4 = depth_edges[2];
            ((S_800D6170_0 *)scratch)->unk_CC = depth_edges[3];
            depth_edges[2] -= 0x10;
            depth_edges[3] -= 0x10;

            packet = ((S_800D6170_3 *)(*render_context))->unk_8D0;
            ((S_800D6170_3 *)(*render_context))->unk_8D0 = packet + 0x18;
            ot_index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                                  scratch + 0xC0, scratch + 0xC8,
                                  packet + 8, packet + 0xC,
                                  packet + 0x10, packet + 0x14,
                                  scratch + 0xD0, scratch + 0xD4) - depth_bias - 6;
            ((S_800D6170_0 *)scratch)->unk_100 = ot_index;

            if ((u32)ot_index < 0x1E0) {
                if ((((u16)(((S_800D6170_4 *)packet)->unk_08 + 0x20) < 0x181) &&
                     ((u16)(((S_800D6170_4 *)packet)->unk_0A + 0x20) < 0x121)) |
                    (((u16)(((S_800D6170_4 *)packet)->unk_0C + 0x20) < 0x181) &&
                     ((u16)(((S_800D6170_4 *)packet)->unk_0E + 0x20) < 0x121)) |
                    (((u16)(((S_800D6170_4 *)packet)->unk_10 + 0x20) < 0x181) &&
                     ((u16)(((S_800D6170_4 *)packet)->unk_12 + 0x20) < 0x121)) |
                    (((u16)(((S_800D6170_4 *)packet)->unk_14 + 0x20) < 0x181) &&
                     ((u16)(((S_800D6170_4 *)packet)->unk_16 + 0x20) < 0x121))) {
                    render_state->unk_14 &= 0x7FFF;
                    ((S_800D6170_4 *)packet)->unk_04 = render_state->unk_0C;
                    func_800666E0(packet);

                    ((S_800D6170_4 *)packet)->unk_00 = (((S_800D6170_4 *)packet)->unk_00 & length_mask) |
                        ((*(u32 *)((u8 *)(((S_800D6170_0 *)scratch)->unk_24.p2) + ((S_800D6170_0 *)scratch)->unk_100 * 4)) & address_mask);
                    (*(u32 *)((u8 *)(((S_800D6170_0 *)scratch)->unk_24.p2) + ((S_800D6170_0 *)scratch)->unk_100 * 4)) =
                        ((*(u32 *)((u8 *)(((S_800D6170_0 *)scratch)->unk_24.p2) + ((S_800D6170_0 *)scratch)->unk_100 * 4)) & length_mask) |
                        ((u32)packet & address_mask);
                }
            }
            depth_span = (s16)depth_edges[0];
            depth_span -= (s16)depth_edges[2];
            if (depth_span < 0) {
                depth_span = -depth_span;
            }
        } while (depth_span >= 0x11);
    }

    if ((s16)depth_edges[0] != (s16)depth_edges[2]) {
        ((S_800D6170_0 *)scratch)->unk_B0 = (*(u16 *)((u8 *)geometry + 0x44));
        ((S_800D6170_0 *)scratch)->unk_B8 = (*(u16 *)((u8 *)geometry + 0x46));
        ((S_800D6170_0 *)scratch)->unk_C0 = (*(u16 *)((u8 *)geometry + 0x48));
        ((S_800D6170_0 *)scratch)->unk_C8 = (*(u16 *)((u8 *)geometry + 0x4A));
        ((S_800D6170_0 *)scratch)->unk_B2 = (*(u16 *)((u8 *)geometry + 0x4C));
        ((S_800D6170_0 *)scratch)->unk_BA = (*(u16 *)((u8 *)geometry + 0x4E));
        ((S_800D6170_0 *)scratch)->unk_C2 = (*(u16 *)((u8 *)geometry + 0x50));
        ((S_800D6170_0 *)scratch)->unk_CA = (*(u16 *)((u8 *)geometry + 0x52));
        ((S_800D6170_0 *)scratch)->unk_B4 = depth_edges[0];
        ((S_800D6170_0 *)scratch)->unk_BC = depth_edges[1];
        ((S_800D6170_0 *)scratch)->unk_C4 = depth_edges[2];
        ((S_800D6170_0 *)scratch)->unk_CC = depth_edges[3];

        packet = ((S_800D6170_3 *)(*render_context))->unk_8D0;
        ((S_800D6170_3 *)(*render_context))->unk_8D0 = packet + 0x18;
        ot_index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                              scratch + 0xC0, scratch + 0xC8,
                              packet + 8, packet + 0xC,
                              packet + 0x10, packet + 0x14,
                              scratch + 0xD0, scratch + 0xD4) - depth_bias - 6;
        ((S_800D6170_0 *)scratch)->unk_100 = ot_index;

        if ((u32)ot_index < 0x1E0) {
            if ((((u16)(((S_800D6170_4 *)packet)->unk_08 + 0x20) < 0x181) &&
                 ((u16)(((S_800D6170_4 *)packet)->unk_0A + 0x20) < 0x121)) |
                (((u16)(((S_800D6170_4 *)packet)->unk_0C + 0x20) < 0x181) &&
                 ((u16)(((S_800D6170_4 *)packet)->unk_0E + 0x20) < 0x121)) |
                (((u16)(((S_800D6170_4 *)packet)->unk_10 + 0x20) < 0x181) &&
                 ((u16)(((S_800D6170_4 *)packet)->unk_12 + 0x20) < 0x121)) |
                (((u16)(((S_800D6170_4 *)packet)->unk_14 + 0x20) < 0x181) &&
                 ((u16)(((S_800D6170_4 *)packet)->unk_16 + 0x20) < 0x121))) {
                render_state->unk_14 &= 0x7FFF;
                ((S_800D6170_4 *)packet)->unk_04 = render_state->unk_0C;
                func_800666E0(packet);

                ((S_800D6170_4 *)packet)->unk_00 = (((S_800D6170_4 *)packet)->unk_00 & 0xFF000000) |
                    ((*(u32 *)((u8 *)(((S_800D6170_0 *)scratch)->unk_24.p2) + ((S_800D6170_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
                (*(u32 *)((u8 *)(((S_800D6170_0 *)scratch)->unk_24.p2) + ((S_800D6170_0 *)scratch)->unk_100 * 4)) =
                    ((*(u32 *)((u8 *)(((S_800D6170_0 *)scratch)->unk_24.p2) + ((S_800D6170_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                    ((u32)packet & 0x00FFFFFF);
            }
        }
    }

    func_80064A40();
}
