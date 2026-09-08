/* Rowbase phase-2 landing shape (docs/rowbase_lane_phase2.md): natural plain C
 * at the Beldo region true base 0x80174334 — the function defines its
 * TRUE-space name func_801663AC; the j->0x8017xxxx words are its own local
 * if/else joins (gap probe 5). No pins, no noreturn scaffolding. */
#include "common.h"

typedef struct S_801663AC_0 {
    u8 pad_00[0xC];
    union { s32 s32; u16 u16; } unk_0C;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_10;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_14;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_18;   /* accessed as both */
    u8 pad_1C[0x8];
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
} S_801663AC_0;   /* scratch in func_801663AC */

typedef struct S_801663AC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_801663AC_1;   /* arg1 in func_801663AC */

typedef struct S_801663AC_2 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x3];
    u8 unk_0F;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_801663AC_2;   /* arg2 in func_801663AC */

typedef struct S_801663AC_3 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_801663AC_3;   /* *(u8 **)D_80083160 in func_801663AC */

typedef struct S_801663AC_4 {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    u8 pad_10[0x64];
    u16 unk_74;
    u16 unk_76;
    u16 unk_78;
    u16 unk_7A;
    u16 unk_7C;
    u16 unk_7E;
    u16 unk_80;
    u16 unk_82;
    u16 unk_84;
    u16 unk_86;
    u16 unk_88;
    u16 unk_8A;
} S_801663AC_4;   /* arg0 in func_801663AC */

typedef struct S_801663AC_5 {
    u32 unk_00;
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    union { u16 u; s16 s; } unk_08;   /* accessed as both */
    union { u16 u; s16 s; } unk_0A;   /* accessed as both */
    u16 unk_0C;
    u16 unk_0E;
    u32 unk_10;
    u16 unk_14;
    u16 unk_16;
    union { u16 u16; u8 u8; } unk_18;   /* accessed as both */
    u16 unk_1A;
    u32 unk_1C;
    u16 unk_20;
    u16 unk_22;
    union { struct { u16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 pad_26[0x2];
    u32 unk_28;
    union { u16 u; s16 s; } unk_2C;   /* accessed as both */
    union { u16 u; s16 s; } unk_2E;   /* accessed as both */
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_30;   /* overlapping accesses */
} S_801663AC_5;   /* packet in func_801663AC */

typedef struct S_801663AC_6 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
} S_801663AC_6;   /* texture in func_801663AC */



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
extern void func_8006671C(void *);
extern u8 D_80083160[];

/* Transform a textured quad and add it to the ordering table if visible. */
void func_801663AC(void *quad, void *position, void *render_state, s16 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    s32 ot_index;
    u16 render_flags;
    u8 tex_flags;
    MATRIX view_matrix;

    ((S_801663AC_0 *)scratch)->unk_24.p = *(u8 **)D_80083160 + 0xB0;
    ((S_801663AC_0 *)scratch)->unk_88 = ((S_801663AC_1 *)position)->unk_02;
    ((S_801663AC_0 *)scratch)->unk_8C = ((S_801663AC_1 *)position)->unk_06;
    ((S_801663AC_0 *)scratch)->unk_90 = ((S_801663AC_1 *)position)->unk_0A;
    ((S_801663AC_2 *)render_state)->unk_14 |= 0x8000;

    func_800649A0();

    ((S_801663AC_0 *)scratch)->unk_3C = 0x2000;
    ((S_801663AC_0 *)scratch)->unk_38 = 0x2000;
    ((S_801663AC_0 *)scratch)->unk_34 = 0x2000;
    ((S_801663AC_0 *)scratch)->unk_A4 = ((S_801663AC_2 *)render_state)->unk_16;
    ((S_801663AC_0 *)scratch)->unk_A8 = ((S_801663AC_2 *)render_state)->unk_1A;
    ((S_801663AC_0 *)scratch)->unk_A6 = ((S_801663AC_2 *)render_state)->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&view_matrix);
    func_80064840(&view_matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture = ((S_801663AC_2 *)render_state)->unk_08;
    ((S_801663AC_0 *)scratch)->unk_28 = ((S_801663AC_2 *)render_state)->unk_14;
    ((S_801663AC_0 *)scratch)->unk_0C.s32 = texture[8];
    ((S_801663AC_0 *)scratch)->unk_10.s32 = texture[9];
    (*(s32 *)((u8 *)scratch + 0x14)) = texture[0xA];
    ((S_801663AC_0 *)scratch)->unk_18.s32 = texture[0xB];
    packet = ((S_801663AC_3 *)(*(u8 **)D_80083160))->unk_8D0;
    ((S_801663AC_3 *)(*(u8 **)D_80083160))->unk_8D0 = packet + 0x34;

    ((S_801663AC_0 *)scratch)->unk_B0 = ((S_801663AC_4 *)quad)->unk_74;
    ((S_801663AC_0 *)scratch)->unk_B8 = ((S_801663AC_4 *)quad)->unk_7A;
    ((S_801663AC_0 *)scratch)->unk_C0 = ((S_801663AC_4 *)quad)->unk_80;
    ((S_801663AC_0 *)scratch)->unk_C8 = ((S_801663AC_4 *)quad)->unk_86;
    ((S_801663AC_0 *)scratch)->unk_B2 = ((S_801663AC_4 *)quad)->unk_76;
    ((S_801663AC_0 *)scratch)->unk_BA = ((S_801663AC_4 *)quad)->unk_7C;
    ((S_801663AC_0 *)scratch)->unk_C2 = ((S_801663AC_4 *)quad)->unk_82;
    ((S_801663AC_0 *)scratch)->unk_CA = ((S_801663AC_4 *)quad)->unk_88;
    ((S_801663AC_0 *)scratch)->unk_B4 = ((S_801663AC_4 *)quad)->unk_78;
    ((S_801663AC_0 *)scratch)->unk_BC = ((S_801663AC_4 *)quad)->unk_7E;
    ((S_801663AC_0 *)scratch)->unk_C4 = ((S_801663AC_4 *)quad)->unk_84;
    ((S_801663AC_0 *)scratch)->unk_CC = ((S_801663AC_4 *)quad)->unk_8A;

    ot_index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                          scratch + 0xC0, scratch + 0xC8,
                          packet + 8, packet + 0x14,
                          packet + 0x20, packet + 0x2C,
                          scratch + 0xD0, scratch + 0xD4) - depth_bias - 6;
    ((S_801663AC_0 *)scratch)->unk_100 = ot_index;

    if ((u32)ot_index < 0x1E0) {
        if ((((u16)(((S_801663AC_5 *)packet)->unk_08.u + 0x20) < 0x181) &&
             ((u16)(((S_801663AC_5 *)packet)->unk_0A.u + 0x20) < 0x121)) |
            (((u16)(((S_801663AC_5 *)packet)->unk_14 + 0x20) < 0x181) &&
             ((u16)(((S_801663AC_5 *)packet)->unk_16 + 0x20) < 0x121)) |
            (((u16)(((S_801663AC_5 *)packet)->unk_20 + 0x20) < 0x181) &&
             ((u16)(((S_801663AC_5 *)packet)->unk_22 + 0x20) < 0x121)) |
            (((u16)(((S_801663AC_5 *)packet)->unk_2C.u + 0x20) < 0x181) &&
             ((u16)(((S_801663AC_5 *)packet)->unk_2E.u + 0x20) < 0x121))) {
            ((S_801663AC_2 *)render_state)->unk_14 &= 0x7FFF;

            ((S_801663AC_0 *)scratch)->unk_14.s32 += ((S_801663AC_0 *)scratch)->unk_0C.s32;
            if (((S_801663AC_0 *)scratch)->unk_14.s32 & 0x100) {
                ((S_801663AC_0 *)scratch)->unk_14.s32--;
            }
            ((S_801663AC_0 *)scratch)->unk_18.s32 += ((S_801663AC_0 *)scratch)->unk_10.s32;
            if (((S_801663AC_0 *)scratch)->unk_18.s32 & 0x100) {
                ((S_801663AC_0 *)scratch)->unk_18.s32--;
            }
            ((S_801663AC_0 *)scratch)->unk_10.s32 <<= 8;
            ((S_801663AC_0 *)scratch)->unk_18.s32 <<= 8;

            if (((S_801663AC_2 *)render_state)->unk_12) {
                if (((S_801663AC_0 *)scratch)->unk_28 & 0x100) {
                    ((S_801663AC_5 *)packet)->unk_0E = ((S_801663AC_2 *)render_state)->unk_12;
                } else {
                    ((S_801663AC_5 *)packet)->unk_0E = ((S_801663AC_2 *)render_state)->unk_12 +
                                              ((S_801663AC_6 *)texture)->unk_06;
                }
            } else {
                ((S_801663AC_5 *)packet)->unk_0E = ((S_801663AC_6 *)texture)->unk_06;
            }

            ((S_801663AC_5 *)packet)->unk_0C = ((S_801663AC_0 *)scratch)->unk_10.u16 +
                                      ((S_801663AC_0 *)scratch)->unk_0C.u16;
            ((S_801663AC_5 *)packet)->unk_18.u16 = ((S_801663AC_0 *)scratch)->unk_10.u16 +
                                       ((S_801663AC_0 *)scratch)->unk_14.u16;

            if (((S_801663AC_2 *)render_state)->unk_10) {
                ((S_801663AC_5 *)packet)->unk_1A = ((S_801663AC_2 *)render_state)->unk_10 +
                                           (((S_801663AC_6 *)texture)->unk_04 & 0xFF9F);
            } else {
                ((S_801663AC_5 *)packet)->unk_1A = ((S_801663AC_6 *)texture)->unk_04;
            }

            ((S_801663AC_5 *)packet)->unk_24.at00.v = ((S_801663AC_0 *)scratch)->unk_18.u16 +
                                       ((S_801663AC_0 *)scratch)->unk_0C.u16;
            ((S_801663AC_5 *)packet)->unk_30.at00.v = ((S_801663AC_0 *)scratch)->unk_18.u16 +
                                       ((S_801663AC_0 *)scratch)->unk_14.u16;

            if (((S_801663AC_5 *)packet)->unk_08.s > ((S_801663AC_5 *)packet)->unk_2C.s) {
                ((S_801663AC_5 *)packet)->unk_18.u8--;
                ((S_801663AC_5 *)packet)->unk_30.at00u.v--;
            }
            if (((S_801663AC_5 *)packet)->unk_0A.s > ((S_801663AC_5 *)packet)->unk_2E.s) {
                ((S_801663AC_5 *)packet)->unk_24.at01.v--;
                ((S_801663AC_5 *)packet)->unk_30.at01.v--;
            }

            ((S_801663AC_5 *)packet)->unk_04.at00.v = ((S_801663AC_4 *)quad)->unk_00;
            ((S_801663AC_5 *)packet)->unk_10 = ((S_801663AC_4 *)quad)->unk_04;
            ((S_801663AC_5 *)packet)->unk_1C = ((S_801663AC_4 *)quad)->unk_08;
            ((S_801663AC_5 *)packet)->unk_28 = ((S_801663AC_4 *)quad)->unk_0C;

            func_8006671C(packet);

            tex_flags = texture[1];
            ((S_801663AC_2 *)render_state)->unk_0F = tex_flags;
            render_flags = ((S_801663AC_0 *)scratch)->unk_28;
            if (render_flags & 8) {
                ((S_801663AC_2 *)render_state)->unk_0F = (render_flags & 4) ?
                    (tex_flags | 2) : (tex_flags & 0xFD);
            }

            ((S_801663AC_5 *)packet)->unk_04.at03.v |= ((S_801663AC_2 *)render_state)->unk_0F;
            ((S_801663AC_5 *)packet)->unk_00 = (((S_801663AC_5 *)packet)->unk_00 & 0xFF000000) |
                ((*(u32 *)((u8 *)(((S_801663AC_0 *)scratch)->unk_24.p2) + ((S_801663AC_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);

            (*(u32 *)((u8 *)(((S_801663AC_0 *)scratch)->unk_24.p2) + ((S_801663AC_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((S_801663AC_0 *)scratch)->unk_24.p2) + ((S_801663AC_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    func_80064A40();
}

