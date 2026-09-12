#include "common.h"
#include "records/Rec_func_800D6DC0_arg1.h"
#include "records/Rec_func_800D6DC0_arg2.h"

typedef struct S_80175594_0 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    u8 pad_1E[0x4];
    s16 unk_22;
    s16 unk_24;
    u8 pad_26[0x2];
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x2];
    s16 unk_30;
} S_80175594_0;   /* arg0 in func_80175594 */

typedef struct S_80175594_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    union { s32 s32; u16 u16; } unk_08;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_0C;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_10;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_14;   /* accessed as both */
    u8 pad_18[0x8];
    u8 * unk_20;
    u16 unk_24;
    u8 pad_26[0xA];
    s32 unk_30;
    union { s32 s32; u16 u16; } unk_34;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_38;   /* accessed as both */
    u8 pad_3C[0x34];
    union { s16 s; u16 u; } unk_70;   /* accessed as both */
    union { s16 s; u16 u; } unk_72;   /* accessed as both */
    s16 unk_74;
    u8 pad_76[0x2];
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    u8 pad_86[0x2];
    s16 unk_88;
    s16 unk_8A;
    s16 unk_8C;
    u8 pad_8E[0x2A];
    u16 unk_B8;
    u16 unk_BA;
    u8 pad_BC[0x4];
    s32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u16 unk_F0;
    u16 unk_F2;
    u16 unk_F4;
    u16 unk_F6;
    u16 unk_F8;
    u16 unk_FA;
    u16 unk_FC;
    u16 unk_FE;
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
    u8 pad_106[0x2];
    u16 unk_108;
    u16 unk_10A;
} S_80175594_1;   /* scratch in func_80175594 */


typedef struct S_80175594_3 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80175594_3;   /* state in func_80175594 */


typedef struct S_80175594_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80175594_5;   /* matrix in func_80175594 */

typedef struct S_80175594_6 {
    u8 pad_00[0xB8];
    u16 unk_B8;
    u8 pad_BA[0xA];
    s16 unk_C4;
    s16 unk_C6;
    s16 unk_C8;
} S_80175594_6;   /* global in func_80175594 */

typedef struct S_80175594_7 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u16 unk_0C;
    u16 unk_0E;
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    union { u16 u16; u8 u8; } unk_14;   /* accessed as both */
    u16 unk_16;
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
    union { struct { u16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_1C;   /* overlapping accesses */
    u8 pad_1E[0x2];
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    union { s16 s; u16 u; } unk_22;   /* accessed as both */
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
} S_80175594_7;   /* packet in func_80175594 */

typedef struct S_80175594_8 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80175594_8;   /* *global in func_80175594 */



extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_800654B0(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_800666F4(void *);
extern u8 D_8006CD30[];
extern u8 D_80083160[];

typedef struct {
    s32 tag;
    s32 color;
    s16 x0;
    s16 y0;
    u16 uv0;
    u16 clut;
    s16 x1;
    s16 y1;
    u16 uv1;
    u16 tpage;
    s16 x2;
    s16 y2;
    u16 uv2;
    u16 pad2;
    s16 x3;
    s16 y3;
    u16 uv3;
    u16 pad3;
} Packet;

typedef struct {
    s8 flag;
    u8 pad;
    s8 x;
    s8 y;
    u16 f4;
    u16 f6;
    u8 f8;
    u8 f9;
    u8 fA;
    u8 fB;
} Texture;

/* Projects textured sprite quads and queues visible packets for depth-sorted drawing. */
void func_80175594(S_80175594_0 *sprite, Rec_func_800D6DC0_arg1 *position, Rec_func_800D6DC0_arg2 *render, s16 depth_bias)
{
    u8 **render_globals = (u8 **)D_80083160;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *state;
    u8 *matrix;
    Packet *packet;
    Texture *texture;
    s32 scaled_coord;
    s32 view_angle;
    s32 angle_offset;
    s32 visible_0;
    s32 visible_1;
    s32 visible_2;
    s32 visible_3;
    s32 visible_01;
    s32 visible_012;

    if (sprite->unk_1C == 0) {
        return;
    }

    state = *render_globals;
    ((S_80175594_1 *)scratch)->unk_EC = 0;
    ((S_80175594_1 *)scratch)->unk_8C = 0;
    ((S_80175594_1 *)scratch)->unk_84 = 0;
    ((S_80175594_1 *)scratch)->unk_7C = 0;
    ((S_80175594_1 *)scratch)->unk_74 = 0;
    ((S_80175594_1 *)scratch)->unk_20 = state + 0xB0;
    ((S_80175594_1 *)scratch)->unk_00 = position->unk_02;
    ((S_80175594_1 *)scratch)->unk_02 = position->unk_06;
    ((S_80175594_1 *)scratch)->unk_04 = position->unk_0A;
    packet = (Packet *)((S_80175594_3 *)state)->unk_8D0;
    ((S_80175594_1 *)scratch)->unk_C0 = func_80065420(
        scratch, scratch + 0xB8, scratch + 0x90, scratch + 0x94);

    render->unk_14 |= 0x8000;
    {
        u32 depth = *(volatile u32 *)(scratch + 0xC0);
        u32 sort_depth;
        u32 biased_depth;
        sort_depth = (biased_depth = depth - 6, biased_depth - (s16)depth_bias);
        matrix = D_8006CD30;
        ((S_80175594_5 *)matrix)->unk_1C = depth * 4;
        ((S_80175594_1 *)scratch)->unk_C0 = sort_depth;
    }

    if ((u32)((S_80175594_1 *)scratch)->unk_C0 < 0x1E0U) {
        func_800649A0();
        ((S_80175594_1 *)scratch)->unk_B8 -= 0xA0;
        ((S_80175594_1 *)scratch)->unk_BA -= 0x78;
        ((S_80175594_1 *)scratch)->unk_30 = ((S_80175594_6 *)render_globals)->unk_C4;
        ((S_80175594_1 *)scratch)->unk_34.s32 = ((S_80175594_6 *)render_globals)->unk_C6;
        ((S_80175594_1 *)scratch)->unk_38.s32 = ((S_80175594_6 *)render_globals)->unk_C8;

        ((S_80175594_1 *)scratch)->unk_100 = render->unk_16;
        ((S_80175594_1 *)scratch)->unk_104 =
            ((S_80175594_6 *)render_globals)->unk_B8 +
            (render->unk_1A - ((S_80175594_1 *)scratch)->unk_34.u16);
        view_angle = (((S_80175594_1 *)scratch)->unk_38.u16 + 0x100) & 0x1FF;
        angle_offset = render->unk_18 - 0x100;
        ((S_80175594_1 *)scratch)->unk_102 = view_angle + angle_offset;

        ((S_80175594_1 *)scratch)->unk_108 = ((S_80175594_1 *)scratch)->unk_E4 =
            render->unk_20;
        ((S_80175594_1 *)scratch)->unk_10A = ((S_80175594_1 *)scratch)->unk_E8 =
            render->unk_22;
        func_80065820(scratch + 0x100, scratch + 0xD0);

        ((S_80175594_1 *)scratch)->unk_30 = render->unk_1C;
        ((S_80175594_1 *)scratch)->unk_34.s32 = render->unk_1E;
        ((S_80175594_1 *)scratch)->unk_38.s32 = 0x1000;
        func_80064BC0(scratch + 0xD0, scratch + 0x30);
        func_80064840(matrix, scratch + 0xD0, scratch + 0x50);
        func_80064D80(scratch + 0x50);
        func_80064CF0(scratch + 0x50);

        texture = (Texture *)render->unk_08;
        ((S_80175594_1 *)scratch)->unk_24 = render->unk_14;

        for (;;) {
            ((S_80175594_1 *)scratch)->unk_08.s32 = texture->f8;
            ((S_80175594_1 *)scratch)->unk_0C.s32 = texture->f9;
            ((S_80175594_1 *)scratch)->unk_10.s32 = texture->fA;
            ((S_80175594_1 *)scratch)->unk_14.s32 = texture->fB;

            scaled_coord = (texture->x -
                     (s16)((S_80175594_1 *)scratch)->unk_108) *
                    sprite->unk_22;
            ((S_80175594_1 *)scratch)->unk_70.s = scaled_coord >> 12;
            scaled_coord = (texture->x -
                     (s16)((S_80175594_1 *)scratch)->unk_108) *
                    sprite->unk_2A;
            ((S_80175594_1 *)scratch)->unk_80 = scaled_coord >> 12;
            scaled_coord = ((s16)((S_80175594_1 *)scratch)->unk_70.u +
                     ((S_80175594_1 *)scratch)->unk_10.s32) *
                    sprite->unk_28;
            ((S_80175594_1 *)scratch)->unk_78 = scaled_coord >> 12;
            scaled_coord = ((s16)((S_80175594_1 *)scratch)->unk_70.u +
                     ((S_80175594_1 *)scratch)->unk_10.s32) *
                    sprite->unk_30;
            ((S_80175594_1 *)scratch)->unk_88 = scaled_coord >> 12;

            scaled_coord = (texture->y -
                     (s16)((S_80175594_1 *)scratch)->unk_10A) *
                    sprite->unk_24;
            ((S_80175594_1 *)scratch)->unk_72.s = scaled_coord >> 12;
            scaled_coord = (texture->y -
                     (s16)((S_80175594_1 *)scratch)->unk_10A) *
                    sprite->unk_28;
            ((S_80175594_1 *)scratch)->unk_7A = scaled_coord >> 12;
            scaled_coord = ((s16)((S_80175594_1 *)scratch)->unk_72.u +
                     ((S_80175594_1 *)scratch)->unk_14.s32) *
                    sprite->unk_2C;
            ((S_80175594_1 *)scratch)->unk_82 = scaled_coord >> 12;
            {
                register void *vertex_1 ASM_REG("$5") = scratch + 0x78;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                register void *vertex_2 ASM_REG("$6") = scratch + 0x80;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                register void *vertex_3 ASM_REG("$7") = scratch + 0x88;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                register void *screen_0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                s32 bottom_y;
                register s32 bottom_scale ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

                bottom_y = ((S_80175594_1 *)scratch)->unk_72.u;
                screen_0 = scratch + 0xF0;
                bottom_y = (s16)bottom_y +
                                ((S_80175594_1 *)scratch)->unk_14.s32;
                ASM_KEEP(bottom_y);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                bottom_scale = sprite->unk_30;
                scaled_coord = bottom_y * bottom_scale;
                ((S_80175594_1 *)scratch)->unk_8A = scaled_coord >> 12;

                func_800654B0(scratch + 0x70, vertex_1,
                              vertex_2, vertex_3,
                              screen_0, scratch + 0xF4,
                              scratch + 0xF8, scratch + 0xFC,
                              scratch + 0x90, scratch + 0x94);
            }

            ((S_80175594_7 *)packet)->unk_08.s =
                ((S_80175594_1 *)scratch)->unk_F0 + ((S_80175594_1 *)scratch)->unk_B8;
            ((S_80175594_7 *)packet)->unk_0A.s =
                ((S_80175594_1 *)scratch)->unk_F2 + ((S_80175594_1 *)scratch)->unk_BA;
            ((S_80175594_7 *)packet)->unk_10.s =
                ((S_80175594_1 *)scratch)->unk_F4 + ((S_80175594_1 *)scratch)->unk_B8;
            ((S_80175594_7 *)packet)->unk_12.s =
                ((S_80175594_1 *)scratch)->unk_F6 + ((S_80175594_1 *)scratch)->unk_BA;
            ((S_80175594_7 *)packet)->unk_18.s =
                ((S_80175594_1 *)scratch)->unk_F8 + ((S_80175594_1 *)scratch)->unk_B8;
            ((S_80175594_7 *)packet)->unk_1A.s =
                ((S_80175594_1 *)scratch)->unk_FA + ((S_80175594_1 *)scratch)->unk_BA;
            ((S_80175594_7 *)packet)->unk_20.s =
                ((S_80175594_1 *)scratch)->unk_FC + ((S_80175594_1 *)scratch)->unk_B8;
            ((S_80175594_7 *)packet)->unk_22.s =
                ((S_80175594_1 *)scratch)->unk_FE + ((S_80175594_1 *)scratch)->unk_BA;

            visible_0 = 0;
            if ((u16)(((S_80175594_7 *)packet)->unk_08.u + 0x20) < 0x181U) {
                visible_0 =
                    (u16)(((S_80175594_7 *)packet)->unk_0A.u + 0x20) < 0x121U;
            }
            visible_1 = 0;
            if ((u16)(((S_80175594_7 *)packet)->unk_10.u + 0x20) < 0x181U) {
                visible_1 =
                    (u16)(((S_80175594_7 *)packet)->unk_12.u + 0x20) < 0x121U;
            }
            visible_01 = visible_0 | visible_1;
            visible_2 = 0;
            if ((u16)(((S_80175594_7 *)packet)->unk_18.u + 0x20) < 0x181U) {
                visible_2 =
                    (u16)(((S_80175594_7 *)packet)->unk_1A.u + 0x20) < 0x121U;
            }
            visible_012 = visible_01 | visible_2;
            visible_3 = 0;
            if ((u16)(((S_80175594_7 *)packet)->unk_20.u + 0x20) < 0x181U) {
                visible_3 =
                    (u16)(((S_80175594_7 *)packet)->unk_22.u + 0x20) < 0x121U;
            }

            if ((visible_012 | visible_3) != 0) {
                ((S_80175594_1 *)scratch)->unk_10.s32 += ((S_80175594_1 *)scratch)->unk_08.s32;
                ((S_80175594_1 *)scratch)->unk_14.s32 =
                    (((S_80175594_1 *)scratch)->unk_0C.s32 +
                     ((S_80175594_1 *)scratch)->unk_14.s32) << 8;
                ((S_80175594_1 *)scratch)->unk_0C.s32 <<= 8;

                ((S_80175594_7 *)packet)->unk_0E =
                    render->unk_12 + texture->f6;
                ((S_80175594_7 *)packet)->unk_0C =
                    ((S_80175594_1 *)scratch)->unk_0C.u16 + ((S_80175594_1 *)scratch)->unk_08.u16;
                ((S_80175594_7 *)packet)->unk_14.u16 =
                    ((S_80175594_1 *)scratch)->unk_0C.u16 + ((S_80175594_1 *)scratch)->unk_10.u16;
                if (render->unk_10 != 0) {
                    ((S_80175594_7 *)packet)->unk_16 =
                        render->unk_10 +
                        (texture->f4 & 0xFF9F);
                } else {
                    ((S_80175594_7 *)packet)->unk_16 = texture->f4;
                }
                ((S_80175594_7 *)packet)->unk_1C.at00.v =
                    ((S_80175594_1 *)scratch)->unk_14.u16 + ((S_80175594_1 *)scratch)->unk_08.u16;
                ((S_80175594_7 *)packet)->unk_24.at00.v =
                    ((S_80175594_1 *)scratch)->unk_14.u16 + ((S_80175594_1 *)scratch)->unk_10.u16;

                if (((S_80175594_7 *)packet)->unk_14.u8 == 0) {
                    ((S_80175594_7 *)packet)->unk_14.u8--;
                    ((S_80175594_7 *)packet)->unk_24.at00u.v--;
                }
                if (((S_80175594_7 *)packet)->unk_1C.at01.v == 0) {
                    ((S_80175594_7 *)packet)->unk_1C.at01.v--;
                    ((S_80175594_7 *)packet)->unk_24.at01.v--;
                }

                ((S_80175594_7 *)packet)->unk_04.at00.v = render->unk_0C;
                func_800666F4(packet);
                if (((S_80175594_1 *)scratch)->unk_24 & 8) {
                    ((S_80175594_7 *)packet)->unk_04.at03.v |= 2;
                }

                func_8006658C(((S_80175594_1 *)scratch)->unk_20 +
                                  ((S_80175594_1 *)scratch)->unk_C0 * 4,
                              packet);
                packet++;
            }

            if (texture->flag < 0) {
                break;
            }
            texture++;
        }

        func_80064A40();
    }

    ((S_80175594_8 *)(*render_globals))->unk_8D0 = packet;
}
