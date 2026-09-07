#include "common.h"

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

typedef struct S_80175594_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80175594_2;   /* arg1 in func_80175594 */

typedef struct S_80175594_3 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80175594_3;   /* state in func_80175594 */

typedef struct S_80175594_4 {
    u8 pad_00[0x8];
    u8 * unk_08;
    s32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
} S_80175594_4;   /* arg2 in func_80175594 */

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

void func_80175594(S_80175594_0 *arg0, S_80175594_2 *arg1, S_80175594_4 *arg2, s16 arg3)
{
    u8 **global = (u8 **)D_80083160;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *state;
    u8 *matrix;
    Packet *packet;
    Texture *texture;
    s32 value;
    s32 screen_x;
    s32 screen_y;
    s32 visible0;
    s32 visible1;
    s32 visible2;
    s32 visible3;
    s32 visible01;
    s32 visible012;

    if (arg0->unk_1C == 0) {
        return;
    }

    state = *global;
    ((S_80175594_1 *)scratch)->unk_EC = 0;
    ((S_80175594_1 *)scratch)->unk_8C = 0;
    ((S_80175594_1 *)scratch)->unk_84 = 0;
    ((S_80175594_1 *)scratch)->unk_7C = 0;
    ((S_80175594_1 *)scratch)->unk_74 = 0;
    ((S_80175594_1 *)scratch)->unk_20 = state + 0xB0;
    ((S_80175594_1 *)scratch)->unk_00 = arg1->unk_02;
    ((S_80175594_1 *)scratch)->unk_02 = arg1->unk_06;
    ((S_80175594_1 *)scratch)->unk_04 = arg1->unk_0A;
    packet = (Packet *)((S_80175594_3 *)state)->unk_8D0;
    ((S_80175594_1 *)scratch)->unk_C0 = func_80065420(
        scratch, scratch + 0xB8, scratch + 0x90, scratch + 0x94);

    arg2->unk_14 |= 0x8000;
    {
        u32 projected = *(volatile u32 *)(scratch + 0xC0);
        u32 adjusted;
        u32 bias_temp;
        adjusted = (bias_temp = projected - 6, bias_temp - (s16)arg3);
        matrix = D_8006CD30;
        ((S_80175594_5 *)matrix)->unk_1C = projected * 4;
        ((S_80175594_1 *)scratch)->unk_C0 = adjusted;
    }

    if ((u32)((S_80175594_1 *)scratch)->unk_C0 < 0x1E0U) {
        func_800649A0();
        ((S_80175594_1 *)scratch)->unk_B8 -= 0xA0;
        ((S_80175594_1 *)scratch)->unk_BA -= 0x78;
        ((S_80175594_1 *)scratch)->unk_30 = ((S_80175594_6 *)global)->unk_C4;
        ((S_80175594_1 *)scratch)->unk_34.s32 = ((S_80175594_6 *)global)->unk_C6;
        ((S_80175594_1 *)scratch)->unk_38.s32 = ((S_80175594_6 *)global)->unk_C8;

        ((S_80175594_1 *)scratch)->unk_100 = arg2->unk_16;
        ((S_80175594_1 *)scratch)->unk_104 =
            ((S_80175594_6 *)global)->unk_B8 +
            (arg2->unk_1A - ((S_80175594_1 *)scratch)->unk_34.u16);
        screen_x = (((S_80175594_1 *)scratch)->unk_38.u16 + 0x100) & 0x1FF;
        screen_y = arg2->unk_18 - 0x100;
        ((S_80175594_1 *)scratch)->unk_102 = screen_x + screen_y;

        ((S_80175594_1 *)scratch)->unk_108 = ((S_80175594_1 *)scratch)->unk_E4 =
            arg2->unk_20;
        ((S_80175594_1 *)scratch)->unk_10A = ((S_80175594_1 *)scratch)->unk_E8 =
            arg2->unk_22;
        func_80065820(scratch + 0x100, scratch + 0xD0);

        ((S_80175594_1 *)scratch)->unk_30 = arg2->unk_1C;
        ((S_80175594_1 *)scratch)->unk_34.s32 = arg2->unk_1E;
        ((S_80175594_1 *)scratch)->unk_38.s32 = 0x1000;
        func_80064BC0(scratch + 0xD0, scratch + 0x30);
        func_80064840(matrix, scratch + 0xD0, scratch + 0x50);
        func_80064D80(scratch + 0x50);
        func_80064CF0(scratch + 0x50);

        texture = (Texture *)arg2->unk_08;
        ((S_80175594_1 *)scratch)->unk_24 = arg2->unk_14;

        for (;;) {
            ((S_80175594_1 *)scratch)->unk_08.s32 = texture->f8;
            ((S_80175594_1 *)scratch)->unk_0C.s32 = texture->f9;
            ((S_80175594_1 *)scratch)->unk_10.s32 = texture->fA;
            ((S_80175594_1 *)scratch)->unk_14.s32 = texture->fB;

            value = (texture->x -
                     (s16)((S_80175594_1 *)scratch)->unk_108) *
                    arg0->unk_22;
            ((S_80175594_1 *)scratch)->unk_70.s = value >> 12;
            value = (texture->x -
                     (s16)((S_80175594_1 *)scratch)->unk_108) *
                    arg0->unk_2A;
            ((S_80175594_1 *)scratch)->unk_80 = value >> 12;
            value = ((s16)((S_80175594_1 *)scratch)->unk_70.u +
                     ((S_80175594_1 *)scratch)->unk_10.s32) *
                    arg0->unk_28;
            ((S_80175594_1 *)scratch)->unk_78 = value >> 12;
            value = ((s16)((S_80175594_1 *)scratch)->unk_70.u +
                     ((S_80175594_1 *)scratch)->unk_10.s32) *
                    arg0->unk_30;
            ((S_80175594_1 *)scratch)->unk_88 = value >> 12;

            value = (texture->y -
                     (s16)((S_80175594_1 *)scratch)->unk_10A) *
                    arg0->unk_24;
            ((S_80175594_1 *)scratch)->unk_72.s = value >> 12;
            value = (texture->y -
                     (s16)((S_80175594_1 *)scratch)->unk_10A) *
                    arg0->unk_28;
            ((S_80175594_1 *)scratch)->unk_7A = value >> 12;
            value = ((s16)((S_80175594_1 *)scratch)->unk_72.u +
                     ((S_80175594_1 *)scratch)->unk_14.s32) *
                    arg0->unk_2C;
            ((S_80175594_1 *)scratch)->unk_82 = value >> 12;
            {
                register void *call_y ASM_REG("$5") = scratch + 0x78;   /* MATCH pin: retail schedule: same instructions, different order without it */
                register void *call_z ASM_REG("$6") = scratch + 0x80;   /* MATCH pin: retail schedule: same instructions, different order without it */
                register void *call_w ASM_REG("$7") = scratch + 0x88;   /* MATCH pin: retail schedule: same instructions, different order without it */
                register void *call_out0 ASM_REG("$8");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
                s32 final_partial;
                register s32 final_coeff ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */

                final_partial = ((S_80175594_1 *)scratch)->unk_72.u;
                ASM_KEEP(final_partial);   /* MATCH pin: retail delay-slot fill depends on it */
                call_out0 = scratch + 0xF0;
                ASM_KEEP_DEP_NV(final_partial, call_out0);   /* MATCH pin: retail delay-slot fill depends on it */
                final_partial = (s16)final_partial +
                                ((S_80175594_1 *)scratch)->unk_14.s32;
                ASM_KEEP(final_partial);   /* MATCH pin: retail delay-slot fill depends on it */
                final_coeff = arg0->unk_30;
                value = final_partial * final_coeff;
                ((S_80175594_1 *)scratch)->unk_8A = value >> 12;

                func_800654B0(scratch + 0x70, call_y,
                              call_z, call_w,
                              call_out0, scratch + 0xF4,
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

            visible0 = 0;
            if ((u16)(((S_80175594_7 *)packet)->unk_08.u + 0x20) < 0x181U) {
                visible0 =
                    (u16)(((S_80175594_7 *)packet)->unk_0A.u + 0x20) < 0x121U;
            }
            visible1 = 0;
            if ((u16)(((S_80175594_7 *)packet)->unk_10.u + 0x20) < 0x181U) {
                visible1 =
                    (u16)(((S_80175594_7 *)packet)->unk_12.u + 0x20) < 0x121U;
            }
            visible01 = visible0 | visible1;
            visible2 = 0;
            if ((u16)(((S_80175594_7 *)packet)->unk_18.u + 0x20) < 0x181U) {
                visible2 =
                    (u16)(((S_80175594_7 *)packet)->unk_1A.u + 0x20) < 0x121U;
            }
            visible012 = visible01 | visible2;
            visible3 = 0;
            if ((u16)(((S_80175594_7 *)packet)->unk_20.u + 0x20) < 0x181U) {
                visible3 =
                    (u16)(((S_80175594_7 *)packet)->unk_22.u + 0x20) < 0x121U;
            }

            if ((visible012 | visible3) != 0) {
                ((S_80175594_1 *)scratch)->unk_10.s32 += ((S_80175594_1 *)scratch)->unk_08.s32;
                ((S_80175594_1 *)scratch)->unk_14.s32 =
                    (((S_80175594_1 *)scratch)->unk_0C.s32 +
                     ((S_80175594_1 *)scratch)->unk_14.s32) << 8;
                ((S_80175594_1 *)scratch)->unk_0C.s32 <<= 8;

                ((S_80175594_7 *)packet)->unk_0E =
                    arg2->unk_12 + texture->f6;
                ((S_80175594_7 *)packet)->unk_0C =
                    ((S_80175594_1 *)scratch)->unk_0C.u16 + ((S_80175594_1 *)scratch)->unk_08.u16;
                ((S_80175594_7 *)packet)->unk_14.u16 =
                    ((S_80175594_1 *)scratch)->unk_0C.u16 + ((S_80175594_1 *)scratch)->unk_10.u16;
                if (arg2->unk_10 != 0) {
                    ((S_80175594_7 *)packet)->unk_16 =
                        arg2->unk_10 +
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

                ((S_80175594_7 *)packet)->unk_04.at00.v = arg2->unk_0C;
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

    ((S_80175594_8 *)(*global))->unk_8D0 = packet;
}
