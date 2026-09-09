#include "common.h"

typedef struct S_8002191C_0 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x20];
    union { u16 s; s16 u; } unk_28;   /* accessed as both */
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    union { u16 s; s16 u; } unk_2C;   /* accessed as both */
    union { u16 s; s16 u; } unk_2E;   /* accessed as both */
    union { u16 s; s16 u; } unk_30;   /* accessed as both */
    union { s16 s; u16 u; } unk_32;   /* accessed as both */
    union { s16 s; u16 u; } unk_34;   /* accessed as both */
    union { s16 s; u16 u; } unk_36;   /* accessed as both */
} S_8002191C_0;   /* arg0 in func_8002191C */

typedef struct S_8002191C_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8002191C_1;   /* root in func_8002191C */

typedef struct S_8002191C_2 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8002191C_2;   /* motion in func_8002191C */

typedef struct S_8002191C_3 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x8];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
} S_8002191C_3;   /* global in func_8002191C */

typedef struct S_8002191C_4 {
    u8 pad_00[0x8];
    union { struct { void * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_8002191C_4;   /* work in func_8002191C */

typedef struct S_8002191C_5 {
    u8 pad_00[0x68];
    s16 unk_68;
} S_8002191C_5;   /* part in func_8002191C */

typedef struct S_8002191C_6 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8002191C_6;   /* node_part in func_8002191C */

typedef struct S_8002191C_7 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8002191C_7;   /* node in func_8002191C */

typedef struct S_8002191C_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_8002191C_8;   /* node_pos in func_8002191C */

typedef struct S_8002191C_9 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_8002191C_9;   /* compare in func_8002191C */



typedef struct TownDraw32 {
    s16 h00;
    s16 h02;
    void *p04;
    void *p08;
    void *p0C;
    s32 w10;
    s16 h14;
    s16 h16;
    s16 h18;
    s16 h1A;
    u16 h1C;
    s16 h1E;
    u8 pad20[0x10];
} TownDraw32;

typedef struct TownPos {
    u16 h00;
    u16 h02;
    s16 h04;
    s16 h06;
    s16 h08;
    s16 h0A;
    s16 h0C;
    s16 h0E;
} TownPos;

extern u8 D_8002003C[];
extern u8 D_80020618[];
extern u8 D_8002241C[];
extern u8 D_80022454[];
extern u8 D_80022C2C[];
extern s16 D_800272A0[];
extern s16 D_800272B0[];
extern s32 D_800814A0;
extern u8 D_80082E80[];
extern s32 D_800834B8;
extern u8 D_80083780[];
extern u8 D_800930E4[];
extern s32 D_80097D2C[3];
extern u8 D_800D0128[];

extern void func_800206F4(void *, TownDraw32 *);
extern void func_8002082C(void *);
extern void func_80020948(void *, TownPos *, s32 *, void *);
extern void func_80022494(void *);
extern void func_80033B78(s32);
extern s32 func_800352FC(void);
extern void func_80043FB8(void *, s32);
extern void SD_Call(s32);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_80093864(void);
extern void func_80093C70(void);
extern void func_80093CEC(void *);
extern void func_80093D48(void *, void *, void *);
extern void tw_sd_sq_ld_call(s32, s32);
extern s16 func_800C2AE8(void *);

void func_8002191C(void *arg0)
{
    TownDraw32 draw;
    TownPos pos;
    s32 color[2];
    u8 *global = (u8 *)&D_800834B8;
    u8 *work;
    void *root = ((S_8002191C_0 *)arg0)->unk_04;
    void *compare = ((S_8002191C_1 *)root)->unk_08;
    u8 *part = (u8 *)root + 0x20;
    s16 mode = ((S_8002191C_0 *)arg0)->unk_36.s;
    u16 value;
    u16 flags;
    s32 i;

    switch (mode) {
    case 0: {
        u8 *motion;
        u16 t6;
        s32 t10;

        SD_Call(0xB1);
        motion = D_80083780;
        ((S_8002191C_0 *)arg0)->unk_30.s = ((S_8002191C_2 *)motion)->unk_02.s;
        t6 = ((S_8002191C_2 *)motion)->unk_06;
        ((S_8002191C_0 *)arg0)->unk_28.s = 4;
        ((S_8002191C_0 *)arg0)->unk_36.s = 1;
        (*(u16 *)((u8 *)arg0 + 0x32)) = t6;
        ((S_8002191C_2 *)motion)->unk_14 = (s32)0xFFE00000;
        (*(s32 *)((u8 *)motion + 0x10)) = 0;
        (*(s32 *)((u8 *)motion + 0x0C)) = 0;
        D_800834B8 = (s32)D_80097D2C;
        ((S_8002191C_3 *)global)->unk_04 = D_80022C2C;
        t10 = ((S_8002191C_3 *)global)->unk_10.s;
        ((S_8002191C_3 *)global)->unk_10.s = (t10 + 0x1000) & 0xFE00;
    }
        /* fall through */

    case 1: {
        u8 *motion;

        ((S_8002191C_3 *)global)->unk_10.s = (((S_8002191C_3 *)global)->unk_10.u + 0x200) & 0xFFF;
        value = ((S_8002191C_0 *)arg0)->unk_28.s - 1;
        ((S_8002191C_0 *)arg0)->unk_28.s = value;
        if ((s16)value > 0) {
            goto finish;
        }
        ((S_8002191C_0 *)arg0)->unk_28.s = 0x10;
        ((S_8002191C_0 *)arg0)->unk_36.s = 2;
        motion = D_80083780;
        ((S_8002191C_2 *)motion)->unk_0C =
            ((0x420 - ((S_8002191C_0 *)arg0)->unk_30.u) << 16) /
            ((S_8002191C_0 *)arg0)->unk_28.u;
        {
            s32 n2 = (0x460 - ((S_8002191C_0 *)arg0)->unk_32.s) << 16;
            s32 d2 = ((S_8002191C_0 *)arg0)->unk_28.u;

            ((S_8002191C_2 *)motion)->unk_14 = (s32)0xFFF40000;
            ((S_8002191C_2 *)motion)->unk_10 = n2 / d2;
        }
        goto finish;
    }

    case 2: {
        u8 *motion = D_80083780;
        s32 h2;
        register u16 rmw ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        rmw = ((S_8002191C_3 *)global)->unk_10.u;
        h2 = ((S_8002191C_2 *)motion)->unk_02.u;
        ((S_8002191C_3 *)global)->unk_10.s = (rmw + 0x200) & 0xFFF;
        if (h2 < 0x420) {
            ((S_8002191C_2 *)motion)->unk_02.s = 0x420;
        }
        value = ((S_8002191C_0 *)arg0)->unk_28.s - 1;
        ((S_8002191C_0 *)arg0)->unk_28.s = value;
        if ((s16)value > 0) {
            goto finish;
        }
        ((S_8002191C_2 *)motion)->unk_10 = 0;
        ((S_8002191C_2 *)motion)->unk_0C = 0;
        ((S_8002191C_0 *)arg0)->unk_36.s = 3;
        goto finish;
    }

    case 3: {
        s32 lim = 0x044FFFFF;
        s32 m1;

        work = D_80083780;
        if (((s32 *)work)[1] <= lim) {
            ((s32 *)work)[1] += (0x04500000 - ((s32 *)work)[1]) >> 1;
        }
        m1 = ((s32 volatile *)work)[1];
        if (m1 > 0x04700000) {
            ((s32 *)work)[1] = m1 + ((0x04700000 - m1) >> 1);
        }
        ((S_8002191C_3 *)global)->unk_10.s = (((S_8002191C_3 *)global)->unk_10.u + 0x200) & 0xFFF;
        i = func_800C2AE8(work);
        if (((S_8002191C_4 *)work)->unk_08.at02.v < i) {
            goto finish;
        }
    }
        if (((S_8002191C_3 *)global)->unk_10.s != 0x800) {
            goto finish;
        }
        tw_sd_sq_ld_call(0x24, 0x200);
        ((S_8002191C_0 *)arg0)->unk_36.s = 4;
        func_8002082C(arg0);
        func_80093D48(global, work, D_80082E80);
        goto finish;

    case 4:
        if (((S_8002191C_5 *)part)->unk_68 == 7) {
            ((S_8002191C_0 *)arg0)->unk_36.s = 5;
        }
        goto finish;

    case 5: {
        u8 *motion;

        if (((S_8002191C_3 *)global)->unk_10.s >= 0xA00) {
            ((S_8002191C_3 *)global)->unk_10.s = ((S_8002191C_3 *)global)->unk_10.u - 0x200;
        } else if (((S_8002191C_3 *)global)->unk_10.s < 0x601) {
            ((S_8002191C_3 *)global)->unk_10.s = ((S_8002191C_3 *)global)->unk_10.u + 0x200;
        }
        func_80043FB8(D_8002003C, ((S_8002191C_3 *)global)->unk_10.s);
        if (func_800352FC() != 0) {
            goto finish;
        }
        if (((S_8002191C_5 *)part)->unk_68 != 8) {
            goto finish;
        }
        ((S_8002191C_3 *)global)->unk_10.s = 0x800;
        func_80093C70();
        func_80093CEC(D_800D0128);
        motion = D_80083780;
        ((S_8002191C_0 *)arg0)->unk_30.s = ((S_8002191C_2 *)motion)->unk_02.s;
        ((S_8002191C_0 *)arg0)->unk_32.u = ((S_8002191C_2 *)motion)->unk_06;
        ((S_8002191C_0 *)arg0)->unk_2C.s = 0;
        ((S_8002191C_0 *)arg0)->unk_2A.s &= 0x7FFF;
        ((S_8002191C_0 *)arg0)->unk_36.s = 6;
        goto finish;
    }

    case 6: {
        s32 magnitude;
        u16 old_flags;
        u16 selected_flags;

        if (((S_8002191C_0 *)arg0)->unk_2A.u & 0x8000) {
            ((S_8002191C_0 *)arg0)->unk_2C.s -= 0x20;
        } else {
            ((S_8002191C_0 *)arg0)->unk_2C.s += 0x20;
        }
        magnitude = ((S_8002191C_0 *)arg0)->unk_2C.u;
        if (magnitude < 0) {
            magnitude = -magnitude;
        }
        if (magnitude >= 0x200) {
            old_flags = ((S_8002191C_0 *)arg0)->unk_2A.s;
            if ((s16)((S_8002191C_0 *)arg0)->unk_2A.s & 0x8000) {
                selected_flags = old_flags & 0x7FFF;
            } else {
                selected_flags = old_flags | 0x8000;
            }
            ((S_8002191C_0 *)arg0)->unk_2A.s = selected_flags;
        }
        pos.h0C = 0;
        pos.h04 = 0;
        pos.h00 = ((S_8002191C_0 *)arg0)->unk_30.s;
        pos.h02 = ((S_8002191C_0 *)arg0)->unk_32.u;
        pos.h08 = ((S_8002191C_0 *)arg0)->unk_30.s +
                  func_800644B8(((S_8002191C_0 *)arg0)->unk_2C.u) / 24;
        {
            s32 t = func_80064584(((S_8002191C_0 *)arg0)->unk_2C.u);

            color[1] = 0x202020;
            color[0] = 0x202020;
            pos.h0A = ((S_8002191C_0 *)arg0)->unk_32.u - t / 24;
        }
        if (((S_8002191C_5 *)part)->unk_68 == 9) {
            func_80093C70();
            func_80093CEC(D_800D0128);
            func_80020948(D_80022454, &pos, color, arg0);
            ((S_8002191C_0 *)arg0)->unk_28.s = 0x200;
            ((S_8002191C_0 *)arg0)->unk_2E.s = 0;
            ((S_8002191C_0 *)arg0)->unk_36.s = 7;
            ((S_8002191C_0 *)arg0)->unk_2A.s &= 0x7FFF;
        } else {
            func_80020948(D_8002241C, &pos, color, arg0);
        }
        goto finish;
    }

    case 7: {
        s32 magnitude;
        u16 old_flags;
        u16 selected_flags;

        if (((S_8002191C_0 *)arg0)->unk_2A.u & 0x8000) {
            ((S_8002191C_0 *)arg0)->unk_2E.s -= 4;
        } else {
            ((S_8002191C_0 *)arg0)->unk_2E.s += 4;
        }
        magnitude = ((S_8002191C_0 *)arg0)->unk_2E.u;
        if (magnitude < 0) {
            magnitude = -magnitude;
        }
        if (magnitude >= 0x100) {
            old_flags = ((S_8002191C_0 *)arg0)->unk_2A.s;
            if ((s16)((S_8002191C_0 *)arg0)->unk_2A.s & 0x8000) {
                selected_flags = old_flags & 0x7FFF;
            } else {
                selected_flags = old_flags | 0x8000;
            }
            ((S_8002191C_0 *)arg0)->unk_2A.s = selected_flags;
        }
        ((S_8002191C_0 *)arg0)->unk_28.s =
            (((S_8002191C_0 *)arg0)->unk_28.s + ((S_8002191C_0 *)arg0)->unk_2E.s + 0x1000) & 0xFFF;
        func_80022494(arg0);
        if (((S_8002191C_5 *)part)->unk_68 != 0xA) {
            goto finish;
        }
        func_80093864();
        ((S_8002191C_3 *)global)->unk_00 = D_800930E4;
        draw.h14 = ((S_8002191C_0 *)arg0)->unk_34.s * 0x10 + 0x64;
        draw.h16 = 0xB6;
        draw.h18 = 3;
        draw.w10 = 0x808080;
        draw.h1A = 0x7C80;
        draw.h1C &= 0xFFFE;
        draw.p04 = &D_800272B0[((S_8002191C_0 *)arg0)->unk_34.s];
        draw.p08 = &D_800272A0[((S_8002191C_0 *)arg0)->unk_34.s];
        draw.h00 = 0;
        draw.h02 = 0;
        draw.p0C = arg0;
        func_800206F4(D_80020618, &draw);
        ((S_8002191C_0 *)arg0)->unk_36.s = 8;
        goto finish;
    }

    case 8:
        i = 7;
        global = (u8 *)D_800272A0;
        work = (u8 *)arg0 + 0x1C;
        do {
            void *node = ((S_8002191C_4 *)work)->unk_08.at00.v;
            u8 *node_part = (u8 *)node + 0x20;
            u16 node_flags = ((S_8002191C_6 *)node_part)->unk_08;
            void *node_pos = ((S_8002191C_7 *)node)->unk_08;

            if ((node_flags & 3) == 0) {
                s32 delta0;
                s32 delta1;
                s32 x0;
                s32 y0;
                s32 y1;

                x0 = ((S_8002191C_8 *)node_pos)->unk_02;
                ASM_KEEP(x0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                y0 = ((S_8002191C_9 *)compare)->unk_02;
                delta0 = x0 - y0;
                y0 = ((S_8002191C_8 *)node_pos)->unk_06;
                y1 = ((S_8002191C_9 *)compare)->unk_06;
                if (delta0 < 0) {
                    delta0 = -delta0;
                }
                delta1 = y0 - y1;
                if (delta1 < 0) {
                    delta1 = -delta1;
                }
                if (delta0 + delta1 < 0x20) {
                    ((S_8002191C_6 *)node_part)->unk_08 = node_flags | 1;
                    ((s16 *)global)[((S_8002191C_0 *)arg0)->unk_34.s]++;
                    if (((s16 *)global)[((S_8002191C_0 *)arg0)->unk_34.s] < 7) {
                        SD_Call(0x702);
                    } else {
                        SD_Call(0x703);
                    }
                }
            }
            i--;
            work -= 4;
        } while (i >= 0);
        if (((S_8002191C_5 *)part)->unk_68 == 0xB) {
            ((S_8002191C_0 *)arg0)->unk_28.s = 0x1E;
            ((S_8002191C_0 *)arg0)->unk_36.s = 9;
        }
        goto finish;

    case 9:
        value = ((S_8002191C_0 *)arg0)->unk_28.s - 1;
        ((S_8002191C_0 *)arg0)->unk_28.s = value;
        if ((s16)value <= 0) {
            ((S_8002191C_0 *)arg0)->unk_36.s = 0xA;
        }
        goto finish;

    case 10:
        flags = ((S_8002191C_0 *)arg0)->unk_2A.s;
        if ((flags & 2) == 0) {
            goto finish;
        }
        ((S_8002191C_0 *)arg0)->unk_2A.s = flags & 0xFFFD;
        func_80093864();
        value = ((S_8002191C_0 *)arg0)->unk_34.u + 1;
        ((S_8002191C_0 *)arg0)->unk_34.u = value;
        if ((s16)value == 8) {
            SD_Call(0xB1);
            ((S_8002191C_0 *)arg0)->unk_28.s = 0x78;
            ((S_8002191C_0 *)arg0)->unk_36.s = 0xFF;
        } else {
            func_8002082C(arg0);
            ((S_8002191C_0 *)arg0)->unk_36.s = 4;
        }
        goto finish;

    case 0xFF:
        value = ((S_8002191C_0 *)arg0)->unk_28.s - 1;
        ((S_8002191C_0 *)arg0)->unk_28.s = value;
        if ((s16)value <= 0) {
            tw_sd_sq_ld_call(0x20, 0x200);
            ((S_8002191C_0 *)arg0)->unk_2A.s |= 1;
            ((S_8002191C_0 *)arg0)->unk_36.u++;
        }
        goto finish;

    case 0x100:
        func_80033B78(0xA5);
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto finish;

    default:
        goto finish;
    }

finish:
    if (((S_8002191C_0 *)arg0)->unk_36.s >= 4) {
        s32 *motion = (s32 *)D_80083780;

        if (motion[0] <= 0x03CFFFFF) {
            motion[0] = 0x03D00000;
        }
        if (motion[1] <= 0x044FFFFF) {
            motion[1] = 0x04500000;
        }
        if (motion[0] > 0x04700000) {
            motion[0] = 0x04700000;
        }
        if (motion[1] > 0x04700000) {
            motion[1] = 0x04700000;
        }
    }
}
