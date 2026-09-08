#include "common.h"

typedef struct S_819A088C_0 {
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
} S_819A088C_0;   /* scratch in func_819A088C */

typedef struct S_819A088C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_819A088C_1;   /* arg1 in func_819A088C */

typedef struct S_819A088C_2 {
    u8 pad_00[0xF];
    u8 unk_0F;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_819A088C_2;   /* arg2 in func_819A088C */

typedef struct S_819A088C_3 {
    u8 pad_00[0xB0];
    u32 unk_B0;
    u8 pad_B4[0x81C];
    u8 * unk_8D0;
} S_819A088C_3;   /* *(u8 **)D_80083160 in func_819A088C */

typedef struct S_819A088C_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u32 unk_14;
    u16 unk_18;
    u16 unk_1A;
    u32 unk_1C;
    u16 unk_20;
    u16 unk_22;
} S_819A088C_4;   /* packet in func_819A088C */

typedef struct S_819A088C_5 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_819A088C_5;   /* context in func_819A088C */

typedef struct S_819A088C_6 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u8 pad_1C[0x38];
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
} S_819A088C_6;   /* arg0 in func_819A088C */

typedef struct S_819A088C_7 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_819A088C_7;   /* *global in func_819A088C */



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
extern u8 D_80083160[];

/* Transform and queue a visible Gouraud-shaded quad in the ordering table. */
void func_819A088C(void *quad, void *position, void *render_state, s16 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    s32 ot_index;
    u16 render_flags;
    u8 texture_flags;
    u8 **render_context_ptr = (u8 **)D_80083160;
    MATRIX base_matrix;

    ((S_819A088C_0 *)scratch)->unk_24.p = *(u8 **)D_80083160 + 0xB0;
    ((S_819A088C_0 *)scratch)->unk_88 = ((S_819A088C_1 *)position)->unk_02;
    ((S_819A088C_0 *)scratch)->unk_8C = ((S_819A088C_1 *)position)->unk_06;
    ((S_819A088C_0 *)scratch)->unk_90 = ((S_819A088C_1 *)position)->unk_0A;
    ((S_819A088C_2 *)render_state)->unk_14 |= 0x8000;

    func_800649A0();

    ((S_819A088C_0 *)scratch)->unk_3C = 0x2000;
    ((S_819A088C_0 *)scratch)->unk_38 = 0x2000;
    ((S_819A088C_0 *)scratch)->unk_34 = 0x2000;
    ((S_819A088C_0 *)scratch)->unk_A4 = ((S_819A088C_2 *)render_state)->unk_16;
    ((S_819A088C_0 *)scratch)->unk_A8 = ((S_819A088C_2 *)render_state)->unk_1A;
    ((S_819A088C_0 *)scratch)->unk_A6 = ((S_819A088C_2 *)render_state)->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&base_matrix);
    func_80064840(&base_matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture = (*(u8 * *)((u8 *)render_state + 8));
    ((S_819A088C_0 *)scratch)->unk_28 = ((S_819A088C_2 *)render_state)->unk_14;

    packet = ((S_819A088C_3 *)(*(u8 **)D_80083160))->unk_8D0;
    ((S_819A088C_3 *)(*(u8 **)D_80083160))->unk_8D0 = packet + 0xC;
    func_80067F20(packet, 0, 1, func_80066460(0, 0, 0, 0) & 0xFFFF, 0);
    (*(u32 *)((u8 *)packet + 0)) = (((S_819A088C_4 *)packet)->unk_00.at00.v & 0xFF000000) |
        (((S_819A088C_3 *)(*(u8 **)D_80083160))->unk_B0 & 0x00FFFFFF);
    (*(u32 *)((u8 *)(*(u8 **)D_80083160) + 0xB0)) =
        (((S_819A088C_3 *)(*(u8 **)D_80083160))->unk_B0 & 0xFF000000) |
        ((u32)packet & 0x00FFFFFF);

    {
        u8 *render_context;

        render_context = *(u8 * volatile *)D_80083160;
        packet = ((S_819A088C_5 *)render_context)->unk_8D0;
        ((S_819A088C_5 *)render_context)->unk_8D0 = packet + 0x24;
    }

    ((S_819A088C_0 *)scratch)->unk_B0 = ((S_819A088C_6 *)quad)->unk_54;
    ((S_819A088C_0 *)scratch)->unk_B8 = ((S_819A088C_6 *)quad)->unk_5A;
    ((S_819A088C_0 *)scratch)->unk_C0 = ((S_819A088C_6 *)quad)->unk_60;
    ((S_819A088C_0 *)scratch)->unk_C8 = ((S_819A088C_6 *)quad)->unk_66;
    ((S_819A088C_0 *)scratch)->unk_B2 = ((S_819A088C_6 *)quad)->unk_56;
    ((S_819A088C_0 *)scratch)->unk_BA = ((S_819A088C_6 *)quad)->unk_5C;
    ((S_819A088C_0 *)scratch)->unk_C2 = ((S_819A088C_6 *)quad)->unk_62;
    ((S_819A088C_0 *)scratch)->unk_CA = ((S_819A088C_6 *)quad)->unk_68;
    ((S_819A088C_0 *)scratch)->unk_B4 = ((S_819A088C_6 *)quad)->unk_58;
    ((S_819A088C_0 *)scratch)->unk_BC = ((S_819A088C_6 *)quad)->unk_5E;
    ((S_819A088C_0 *)scratch)->unk_C4 = ((S_819A088C_6 *)quad)->unk_64;
    ((S_819A088C_0 *)scratch)->unk_CC = ((S_819A088C_6 *)quad)->unk_6A;

    ot_index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                          scratch + 0xC0, scratch + 0xC8,
                          packet + 8, packet + 0x10,
                          packet + 0x18, packet + 0x20,
                          scratch + 0xD0, scratch + 0xD4) - depth_bias - 6;
    ((S_819A088C_0 *)scratch)->unk_100 = ot_index;

    if ((u32)ot_index < 0x1E0) {
        if ((((u16)(((S_819A088C_4 *)packet)->unk_08 + 0x20) < 0x181) &&
             ((u16)(((S_819A088C_4 *)packet)->unk_0A + 0x20) < 0x121)) |
            (((u16)(((S_819A088C_4 *)packet)->unk_10 + 0x20) < 0x181) &&
             ((u16)(((S_819A088C_4 *)packet)->unk_12 + 0x20) < 0x121)) |
            (((u16)(((S_819A088C_4 *)packet)->unk_18 + 0x20) < 0x181) &&
             ((u16)(((S_819A088C_4 *)packet)->unk_1A + 0x20) < 0x121)) |
            (((u16)(((S_819A088C_4 *)packet)->unk_20 + 0x20) < 0x181) &&
             ((u16)(((S_819A088C_4 *)packet)->unk_22 + 0x20) < 0x121))) {
            ((S_819A088C_2 *)render_state)->unk_14 &= 0x7FFF;
            texture_flags = texture[1];
            ((S_819A088C_2 *)render_state)->unk_0F = texture_flags;
            render_flags = ((S_819A088C_0 *)scratch)->unk_28;
            if (render_flags & 8) {
                ((S_819A088C_2 *)render_state)->unk_0F = (render_flags & 4) ?
                    (texture_flags | 2) : (texture_flags & 0xFD);
            }

            ((S_819A088C_4 *)packet)->unk_04.at00.v = ((S_819A088C_6 *)quad)->unk_0C;
            ((S_819A088C_4 *)packet)->unk_0C = ((S_819A088C_6 *)quad)->unk_10;
            ((S_819A088C_4 *)packet)->unk_14 = ((S_819A088C_6 *)quad)->unk_14;
            ((S_819A088C_4 *)packet)->unk_1C = ((S_819A088C_6 *)quad)->unk_18;
            ((S_819A088C_4 *)packet)->unk_00.at03.v = 8;
            ((S_819A088C_4 *)packet)->unk_04.at03.v = 0x3A;

            ((S_819A088C_4 *)packet)->unk_00.at00.v = (((S_819A088C_4 *)packet)->unk_00.at00.v & 0xFF000000) |
                ((*(u32 *)((u8 *)(((S_819A088C_0 *)scratch)->unk_24.p2) + ((S_819A088C_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((S_819A088C_0 *)scratch)->unk_24.p2) + ((S_819A088C_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((S_819A088C_0 *)scratch)->unk_24.p2) + ((S_819A088C_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);

            packet = ((S_819A088C_7 *)(*render_context_ptr))->unk_8D0;
            ((S_819A088C_7 *)(*render_context_ptr))->unk_8D0 = packet + 0xC;
            func_80067F20(packet, 0, 1, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
            ((S_819A088C_4 *)packet)->unk_00.at00.v = (((S_819A088C_4 *)packet)->unk_00.at00.v & 0xFF000000) |
                ((*(u32 *)((u8 *)(((S_819A088C_0 *)scratch)->unk_24.p2) + ((S_819A088C_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((S_819A088C_0 *)scratch)->unk_24.p2) + ((S_819A088C_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((S_819A088C_0 *)scratch)->unk_24.p2) + ((S_819A088C_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    func_80064A40();
}
