#include "common.h"

#define VFIELD(p, type, offset) (*(volatile type *)((u8 *)(p) + (offset)))

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

typedef void (*Callback)(void *, void *, void *, void *);

typedef struct S_81874988_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
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
} S_81874988_0;   /* scratch in func_81874988 */

typedef struct S_81874988_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_81874988_1;   /* arg1 in func_81874988 */

typedef struct S_81874988_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_81874988_2;   /* global_value in func_81874988 */

typedef struct S_81874988_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_81874988_3;   /* arg2 in func_81874988 */

typedef struct S_81874988_4 {
    u8 pad_00[0x50];
    u16 unk_50;
    u16 unk_52;
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
} S_81874988_4;   /* arg0 in func_81874988 */

typedef struct S_81874988_5 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    union { u16 u; s16 s; } unk_08;   /* accessed as both */
    union { u16 u; s16 s; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    union { u16 u16; u8 u8; } unk_14;   /* accessed as both */
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
    union { struct { u16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_1C;   /* overlapping accesses */
    u8 pad_1E[0x2];
    union { u16 u; s16 s; } unk_20;   /* accessed as both */
    union { u16 u; s16 s; } unk_22;   /* accessed as both */
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_81874988_5;   /* packet in func_81874988 */


extern u8 *D_80083160;
extern void func_80024544(void) __attribute__((noreturn));
extern void func_8002454C(void) __attribute__((noreturn));
extern void func_8002459C(void) __attribute__((noreturn));
extern void func_800246D0(void) __attribute__((noreturn));
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);

/* Projects a textured quad and queues it for drawing, or invokes its texture callback. */
void func_81874988(void *quad, void *position, void *material, s16 depth_bias)
{
    u8 *render_state = D_80083160;
    u32 tex_attr;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    Callback callback;
    s32 depth_index;
    u16 draw_flags;
    s32 tex_adjust;
    u8 tex_flags;
    MATRIX view_matrix;

    ((S_81874988_0 *)scratch)->unk_24.p = render_state + 0xB0;
    ((S_81874988_0 *)scratch)->unk_88 = ((S_81874988_1 *)position)->unk_02;
    ((S_81874988_0 *)scratch)->unk_8C = ((S_81874988_1 *)position)->unk_06;
    ((S_81874988_0 *)scratch)->unk_90 = ((S_81874988_1 *)position)->unk_0A;

    packet = ((S_81874988_2 *)render_state)->unk_8D0;
    ((S_81874988_2 *)render_state)->unk_8D0 = packet + 0x28;

    ((S_81874988_3 *)material)->unk_14 |= 0x8000;
    func_800649A0();

    ((S_81874988_0 *)scratch)->unk_3C = 0x2000;
    ((S_81874988_0 *)scratch)->unk_38 = 0x2000;
    ((S_81874988_0 *)scratch)->unk_34 = 0x2000;
    ((S_81874988_0 *)scratch)->unk_A4 = ((S_81874988_3 *)material)->unk_16;
    ((S_81874988_0 *)scratch)->unk_A8 = ((S_81874988_3 *)material)->unk_1A;
    ((S_81874988_0 *)scratch)->unk_A6 = ((S_81874988_3 *)material)->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&view_matrix);
    func_80064840(&view_matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture = ((S_81874988_3 *)material)->unk_08;
    ((S_81874988_0 *)scratch)->unk_28 = ((S_81874988_3 *)material)->unk_14;

    if (texture[0] & 0x20) {
        goto callback_tail;
    }

    ((S_81874988_0 *)scratch)->unk_0C = texture[8];
    ((S_81874988_0 *)scratch)->unk_10 = texture[9];
    ((S_81874988_0 *)scratch)->unk_14 = texture[0xA];
    ((S_81874988_0 *)scratch)->unk_18 = texture[0xB];

    ((S_81874988_0 *)scratch)->unk_B0 = ((S_81874988_4 *)quad)->unk_50;
    ((S_81874988_0 *)scratch)->unk_B8 = ((S_81874988_4 *)quad)->unk_52;
    ((S_81874988_0 *)scratch)->unk_C0 = ((S_81874988_4 *)quad)->unk_54;
    ((S_81874988_0 *)scratch)->unk_C8 = ((S_81874988_4 *)quad)->unk_56;
    ((S_81874988_0 *)scratch)->unk_B2 = ((S_81874988_4 *)quad)->unk_58;
    ((S_81874988_0 *)scratch)->unk_BA = ((S_81874988_4 *)quad)->unk_5A;
    ((S_81874988_0 *)scratch)->unk_C2 = ((S_81874988_4 *)quad)->unk_5C;
    ((S_81874988_0 *)scratch)->unk_CA = ((S_81874988_4 *)quad)->unk_5E;
    ((S_81874988_0 *)scratch)->unk_B4 = ((S_81874988_4 *)quad)->unk_60;
    ((S_81874988_0 *)scratch)->unk_BC = ((S_81874988_4 *)quad)->unk_62;
    ((S_81874988_0 *)scratch)->unk_C4 = ((S_81874988_4 *)quad)->unk_64;
    ((S_81874988_0 *)scratch)->unk_CC = ((S_81874988_4 *)quad)->unk_66;

    depth_index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                          scratch + 0xC0, scratch + 0xC8,
                          packet + 8, packet + 0x10,
                          packet + 0x18, packet + 0x20,
                          scratch + 0xD0, scratch + 0xD4) - depth_bias - 6;
    ((S_81874988_0 *)scratch)->unk_100 = depth_index;

    if ((u32)depth_index >= 0x1E0) {
        goto done;
    }
    if (
            (((u16)(((S_81874988_5 *)packet)->unk_08.u + 0x20) < 0x181) &&
             ((u16)(((S_81874988_5 *)packet)->unk_0A.u + 0x20) < 0x121)) |
            (((u16)(((S_81874988_5 *)packet)->unk_10 + 0x20) < 0x181) &&
             ((u16)(((S_81874988_5 *)packet)->unk_12 + 0x20) < 0x121)) |
            (((u16)(((S_81874988_5 *)packet)->unk_18 + 0x20) < 0x181) &&
             ((u16)(((S_81874988_5 *)packet)->unk_1A + 0x20) < 0x121)) |
            (((u16)(((S_81874988_5 *)packet)->unk_20.u + 0x20) < 0x181) &&
             ((u16)(((S_81874988_5 *)packet)->unk_22.u + 0x20) < 0x121))
        ) {
        goto visible;
    }
    goto done;

visible:
    ((S_81874988_5 *)packet)->unk_00.at03.v = 9;
    ((S_81874988_5 *)packet)->unk_04.at03.v = 0x2C;
    ((S_81874988_3 *)material)->unk_14 &= 0x7FFF;

    ((S_81874988_0 *)scratch)->unk_14 += ((S_81874988_0 *)scratch)->unk_0C;
    if (((S_81874988_0 *)scratch)->unk_14 & 0x100) {
        ((S_81874988_0 *)scratch)->unk_14--;
    }
    ((S_81874988_0 *)scratch)->unk_18 += ((S_81874988_0 *)scratch)->unk_10;
    if (((S_81874988_0 *)scratch)->unk_18 & 0x100) {
        ((S_81874988_0 *)scratch)->unk_18--;
    }
    ((S_81874988_0 *)scratch)->unk_10 <<= 8;
    ((S_81874988_0 *)scratch)->unk_18 <<= 8;

    tex_adjust = ((S_81874988_3 *)material)->unk_12;
    if (tex_adjust) {
        if (((S_81874988_0 *)scratch)->unk_28 & 0x100) {
            ((S_81874988_5 *)packet)->unk_0E = tex_adjust;
            func_8002454C();
        }
        tex_attr = tex_adjust + (*(u16 *)((u8 *)texture + 6));
        ASM_TAILSLOT_PIN(tex_attr);   /* MATCH pin: retail delay-slot fill depends on it */
        func_80024544();
    }
    (*(u16 *)((u8 *)packet + 0xE)) = (*(u16 *)((u8 *)texture + 6));

    (*(u16 *)((u8 *)packet + 0xC)) = VFIELD(scratch, u16, 0x10) +
                              VFIELD(scratch, u16, 0xC);
    ((S_81874988_5 *)packet)->unk_14.u16 = VFIELD(scratch, u16, 0x10) +
                               VFIELD(scratch, u16, 0x14);

    tex_adjust = ((S_81874988_3 *)material)->unk_10;
    if (tex_adjust) {
        tex_attr = tex_adjust +
                       ((*(u16 *)((u8 *)texture + 4)) & 0xFF9F);
        ASM_TAILSLOT_PIN(tex_attr);   /* MATCH pin: retail delay-slot fill depends on it */
        func_8002459C();
    }
    (*(u16 *)((u8 *)packet + 0x16)) = (*(u16 *)((u8 *)texture + 4));

    ((S_81874988_5 *)packet)->unk_1C.at00.v = VFIELD(scratch, u16, 0x18) +
                               VFIELD(scratch, u16, 0xC);
    ((S_81874988_5 *)packet)->unk_24.at00.v = VFIELD(scratch, u16, 0x18) +
                               VFIELD(scratch, u16, 0x14);

    if (((S_81874988_5 *)packet)->unk_08.s > ((S_81874988_5 *)packet)->unk_20.s) {
        ((S_81874988_5 *)packet)->unk_14.u8--;
        ((S_81874988_5 *)packet)->unk_24.at00u.v--;
    }
    if (((S_81874988_5 *)packet)->unk_0A.s > ((S_81874988_5 *)packet)->unk_22.s) {
        ((S_81874988_5 *)packet)->unk_1C.at01.v--;
        ((S_81874988_5 *)packet)->unk_24.at01.v--;
    }

    tex_flags = texture[1];
    ((S_81874988_3 *)material)->unk_0C.at03.v = tex_flags;
    draw_flags = ((S_81874988_0 *)scratch)->unk_28;
    if (draw_flags & 8) {
        ((S_81874988_3 *)material)->unk_0C.at03.v = (draw_flags & 4) ?
            (tex_flags | 2) : (tex_flags & 0xFD);
    }

    ((S_81874988_5 *)packet)->unk_04.at00.v = ((S_81874988_3 *)material)->unk_0C.at00.v;
    ((S_81874988_5 *)packet)->unk_00.at00.v = (((S_81874988_5 *)packet)->unk_00.at00.v & 0xFF000000) |
        ((*(u32 *)((u8 *)(((S_81874988_0 *)scratch)->unk_24.p2) + ((S_81874988_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
    (*(u32 *)((u8 *)(((S_81874988_0 *)scratch)->unk_24.p2) + ((S_81874988_0 *)scratch)->unk_100 * 4)) =
        ((*(u32 *)((u8 *)(((S_81874988_0 *)scratch)->unk_24.p2) + ((S_81874988_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
        ((u32)packet & 0x00FFFFFF);
    func_800246D0();

callback_tail:
    callback = (*(Callback *)((u8 *)texture + 8));
    if (callback != 0) {
        callback(quad, position, material, texture);
    }

done:
    func_80064A40();
}
