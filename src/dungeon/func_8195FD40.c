#include "common.h"

typedef struct S_8195FD40_0 {
    u8 pad_00[0x20];
    u32 unk_20;
    u8 pad_24[0xC];
    u32 unk_30;
    u32 unk_34;
    u32 unk_38;
    u8 pad_3C[0x34];
    u32 unk_70;
    u16 unk_74;
    u8 pad_76[0x2];
    u32 unk_78;
    u16 unk_7C;
    u8 pad_7E[0x2];
    u32 unk_80;
    u16 unk_84;
    u8 pad_86[0x2];
    u32 unk_88;
    u16 unk_8C;
    u8 pad_8E[0x32];
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u8 pad_F0[0x10];
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
} S_8195FD40_0;   /* scratch in func_8195FD40 */

typedef struct S_8195FD40_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195FD40_1;   /* arg1 in func_8195FD40 */

typedef struct S_8195FD40_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8195FD40_2;   /* *global in func_8195FD40 */

typedef struct S_8195FD40_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_8195FD40_3;   /* arg2 in func_8195FD40 */

typedef struct S_8195FD40_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 pad_0E[0x2];
    u16 unk_10;
    u16 unk_12;
    s8 unk_14;
    u8 unk_15;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x2];
    u16 unk_20;
    u16 unk_22;
    s8 unk_24;
    s8 unk_25;
} S_8195FD40_4;   /* packet in func_8195FD40 */

typedef struct S_8195FD40_5 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_8195FD40_5;   /* texture in func_8195FD40 */

typedef struct S_8195FD40_6 {
    u32 unk_00;
} S_8195FD40_6;   /* (u8 *)((((S_8195FD40_0 *)scratch)->unk_C0 * 4) +
                              ((S_8195FD40_0 *)scratch)->unk_20) in func_8195FD40 */



extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern u8 D_80083160[];

/* Transform a textured quad and add it to the ordering table if visible. */
void func_8195FD40(s32 unused, S_8195FD40_1 *position, S_8195FD40_3 *quad, s16 depth_bias)
{
    s32 view_matrix[8];
    u8 *scratch = (u8 *)0x1F800000;
    u8 **render_context = (u8 **)D_80083160;
    s32 *ot_entry;
    s32 packet_addr;
    s32 corner0_visible;
    s32 corner1_visible;
    s32 corner2_visible;
    s32 corner3_visible;
    s32 first_two_visible;
    s32 first_three_visible;
    s8 u_right;
    s8 v_bottom;
    u32 depth;
    u8 u_left;
    u8 v_top;
    u8 *packet;
    u8 *texture;

    (void)unused;
    ((S_8195FD40_0 *)scratch)->unk_20 = *render_context + 0xB0;
    ((S_8195FD40_0 *)scratch)->unk_E4 = position->unk_02;
    ((S_8195FD40_0 *)scratch)->unk_E8 = position->unk_06;
    ((S_8195FD40_0 *)scratch)->unk_EC = position->unk_0A;
    packet = ((S_8195FD40_2 *)(*render_context))->unk_8D0;
    texture = quad->unk_08;
    func_800649A0();

    ((S_8195FD40_0 *)scratch)->unk_30 = quad->unk_1C * 2;
    ((S_8195FD40_0 *)scratch)->unk_34 = quad->unk_1E * 2;
    ((S_8195FD40_0 *)scratch)->unk_38 = 0x2000;
    ((S_8195FD40_0 *)scratch)->unk_100 = quad->unk_16;
    ((S_8195FD40_0 *)scratch)->unk_104 = quad->unk_1A;
    ((S_8195FD40_0 *)scratch)->unk_102 = quad->unk_18;
    func_80065820(scratch + 0x100, scratch + 0xD0);
    func_80064AE0(&view_matrix);
    func_80064840(&view_matrix, scratch + 0xD0, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    ((S_8195FD40_0 *)scratch)->unk_78 = 0x20;
    ((S_8195FD40_0 *)scratch)->unk_88 = 0x200000;
    ((S_8195FD40_0 *)scratch)->unk_80 = 0x200000;
    ((S_8195FD40_0 *)scratch)->unk_70 = 0;
    ((S_8195FD40_0 *)scratch)->unk_8C = 0;
    ((S_8195FD40_0 *)scratch)->unk_84 = 0;
    ((S_8195FD40_0 *)scratch)->unk_7C = 0;
    ((S_8195FD40_0 *)scratch)->unk_74 = 0;
    depth = func_80065590(scratch + 0x70, scratch + 0x78,
                            scratch + 0x80, scratch + 0x88,
                            packet + 8, packet + 0x10,
                            packet + 0x18, packet + 0x20,
                            scratch + 0x90, scratch + 0x94) - depth_bias;
    ((S_8195FD40_0 *)scratch)->unk_C0 = depth;

    if (depth < 0x1E0U) {
        corner0_visible = 0;
        if ((u16)(((S_8195FD40_4 *)packet)->unk_08 + 0x20) < 0x181U) {
            corner0_visible = (u16)(((S_8195FD40_4 *)packet)->unk_0A + 0x20) < 0x121U;
        }
        corner1_visible = 0;
        if ((u16)(((S_8195FD40_4 *)packet)->unk_10 + 0x20) < 0x181U) {
            corner1_visible = (u16)(((S_8195FD40_4 *)packet)->unk_12 + 0x20) < 0x121U;
        }
        corner2_visible = 0;
        first_two_visible = corner0_visible | corner1_visible;
        if ((u16)(((S_8195FD40_4 *)packet)->unk_18 + 0x20) < 0x181U) {
            corner2_visible = (u16)(((S_8195FD40_4 *)packet)->unk_1A + 0x20) < 0x121U;
        }
        corner3_visible = 0;
        first_three_visible = first_two_visible | corner2_visible;
        if ((u16)(((S_8195FD40_4 *)packet)->unk_20 + 0x20) < 0x181U) {
            corner3_visible = (u16)(((S_8195FD40_4 *)packet)->unk_22 + 0x20) < 0x121U;
        }

        if ((first_three_visible | corner3_visible) != 0) {
            u_left = ((S_8195FD40_5 *)texture)->unk_08;
            ((S_8195FD40_4 *)packet)->unk_1C = u_left;
            ((S_8195FD40_4 *)packet)->unk_0C = u_left;
            u_right = ((S_8195FD40_5 *)texture)->unk_08 + ((S_8195FD40_5 *)texture)->unk_0A;
            ((S_8195FD40_4 *)packet)->unk_24 = u_right;
            ((S_8195FD40_4 *)packet)->unk_14 = u_right;
            v_top = ((S_8195FD40_5 *)texture)->unk_09;
            ((S_8195FD40_4 *)packet)->unk_15 = v_top;
            ((S_8195FD40_4 *)packet)->unk_0D = v_top;
            v_bottom = ((S_8195FD40_5 *)texture)->unk_09 + ((S_8195FD40_5 *)texture)->unk_0B;
            ((S_8195FD40_4 *)packet)->unk_25 = v_bottom;
            ((S_8195FD40_4 *)packet)->unk_1D = v_bottom;
            ((S_8195FD40_4 *)packet)->unk_16 = ((S_8195FD40_5 *)texture)->unk_04;
            ((S_8195FD40_4 *)packet)->unk_04.at00.v = quad->unk_0C;
            ((S_8195FD40_4 *)packet)->unk_00.at03.v = 9;
            ((S_8195FD40_4 *)packet)->unk_04.at03.v = 0x2C;
            if (quad->unk_14 & 4) {
                ((S_8195FD40_4 *)packet)->unk_04.at03.v = 0x2E;
            }
            packet_addr = (s32)packet & 0xFFFFFF;
            ((S_8195FD40_4 *)packet)->unk_00.at00.v = (((S_8195FD40_4 *)packet)->unk_00.at00.v & 0xFF000000) |
                (((S_8195FD40_6 *)((u8 *)((((S_8195FD40_0 *)scratch)->unk_C0 * 4) +
                              ((S_8195FD40_0 *)scratch)->unk_20)))->unk_00 & 0xFFFFFF);
            ot_entry = (s32 *)((((S_8195FD40_0 *)scratch)->unk_C0 * 4) +
                              ((S_8195FD40_0 *)scratch)->unk_20);
            packet += 0x28;
            *ot_entry = (*ot_entry & 0xFF000000) | packet_addr;
        }
    }
    func_80064A40();
    ((S_8195FD40_2 *)(*render_context))->unk_8D0 = packet;
}
