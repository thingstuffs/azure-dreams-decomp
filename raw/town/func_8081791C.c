#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
extern void func_80053DA8(s32);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_80093864(void);
extern void func_80093C70(void);
extern void func_80093CEC(void *);
extern void func_80093D48(void *, void *, void *);
extern void func_800C15C0(s32, s32);
extern s16 func_800C2AE8(void *);

void func_8002191C(void *arg0)
{
    TownDraw32 draw;
    TownPos pos;
    s32 color[2];
    u8 *global = (u8 *)&D_800834B8;
    u8 *work;
    void *root = FIELD(arg0, void *, 4);
    void *compare = FIELD(root, void *, 8);
    u8 *part = (u8 *)root + 0x20;
    s16 mode = FIELD(arg0, s16, 0x36);
    u16 value;
    u16 flags;
    s32 i;

    switch (mode) {
    case 0: {
        u8 *motion;
        u16 t6;
        s32 t10;

        func_80053DA8(0xB1);
        motion = D_80083780;
        FIELD(arg0, u16, 0x30) = FIELD(motion, u16, 2);
        t6 = FIELD(motion, u16, 6);
        FIELD(arg0, u16, 0x28) = 4;
        FIELD(arg0, s16, 0x36) = 1;
        FIELD(arg0, u16, 0x32) = t6;
        FIELD(motion, s32, 0x14) = (s32)0xFFE00000;
        FIELD(motion, s32, 0x10) = 0;
        FIELD(motion, s32, 0x0C) = 0;
        D_800834B8 = (s32)D_80097D2C;
        FIELD(global, void *, 4) = D_80022C2C;
        t10 = FIELD(global, s16, 0x10);
        FIELD(global, s16, 0x10) = (t10 + 0x1000) & 0xFE00;
    }
        /* fall through */

    case 1: {
        u8 *motion;

        FIELD(global, s16, 0x10) = (FIELD(global, u16, 0x10) + 0x200) & 0xFFF;
        value = FIELD(arg0, u16, 0x28) - 1;
        FIELD(arg0, u16, 0x28) = value;
        if ((s16)value > 0) {
            goto finish;
        }
        FIELD(arg0, u16, 0x28) = 0x10;
        FIELD(arg0, s16, 0x36) = 2;
        motion = D_80083780;
        FIELD(motion, s32, 0x0C) =
            ((0x420 - FIELD(arg0, s16, 0x30)) << 16) /
            FIELD(arg0, s16, 0x28);
        {
            s32 n2 = (0x460 - FIELD(arg0, s16, 0x32)) << 16;
            s32 d2 = FIELD(arg0, s16, 0x28);

            FIELD(motion, s32, 0x14) = (s32)0xFFF40000;
            FIELD(motion, s32, 0x10) = n2 / d2;
        }
        goto finish;
    }

    case 2: {
        u8 *motion = D_80083780;
        register s32 h2 ASM_REG("$3");
        register u16 rmw ASM_REG("$2");

        rmw = FIELD(global, u16, 0x10);
        h2 = FIELD(motion, s16, 2);
        FIELD(global, s16, 0x10) = (rmw + 0x200) & 0xFFF;
        if (h2 < 0x420) {
            FIELD(motion, u16, 2) = 0x420;
        }
        value = FIELD(arg0, u16, 0x28) - 1;
        FIELD(arg0, u16, 0x28) = value;
        if ((s16)value > 0) {
            goto finish;
        }
        FIELD(motion, s32, 0x10) = 0;
        FIELD(motion, s32, 0x0C) = 0;
        FIELD(arg0, s16, 0x36) = 3;
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
        FIELD(global, s16, 0x10) = (FIELD(global, u16, 0x10) + 0x200) & 0xFFF;
        i = func_800C2AE8(work);
        if (FIELD(work, s16, 0x0A) < i) {
            goto finish;
        }
    }
        if (FIELD(global, s16, 0x10) != 0x800) {
            goto finish;
        }
        func_800C15C0(0x24, 0x200);
        FIELD(arg0, s16, 0x36) = 4;
        func_8002082C(arg0);
        func_80093D48(global, work, D_80082E80);
        goto finish;

    case 4:
        if (FIELD(part, s16, 0x68) == 7) {
            FIELD(arg0, s16, 0x36) = 5;
        }
        goto finish;

    case 5: {
        u8 *motion;

        if (FIELD(global, s16, 0x10) >= 0xA00) {
            FIELD(global, s16, 0x10) = FIELD(global, u16, 0x10) - 0x200;
        } else if (FIELD(global, s16, 0x10) < 0x601) {
            FIELD(global, s16, 0x10) = FIELD(global, u16, 0x10) + 0x200;
        }
        func_80043FB8(D_8002003C, FIELD(global, s16, 0x10));
        if (func_800352FC() != 0) {
            goto finish;
        }
        if (FIELD(part, s16, 0x68) != 8) {
            goto finish;
        }
        FIELD(global, s16, 0x10) = 0x800;
        func_80093C70();
        func_80093CEC(D_800D0128);
        motion = D_80083780;
        FIELD(arg0, u16, 0x30) = FIELD(motion, u16, 2);
        FIELD(arg0, u16, 0x32) = FIELD(motion, u16, 6);
        FIELD(arg0, u16, 0x2C) = 0;
        FIELD(arg0, u16, 0x2A) &= 0x7FFF;
        FIELD(arg0, s16, 0x36) = 6;
        goto finish;
    }

    case 6: {
        s32 magnitude;
        u16 old_flags;
        u16 selected_flags;

        if (FIELD(arg0, s16, 0x2A) & 0x8000) {
            FIELD(arg0, u16, 0x2C) -= 0x20;
        } else {
            FIELD(arg0, u16, 0x2C) += 0x20;
        }
        magnitude = FIELD(arg0, s16, 0x2C);
        if (magnitude < 0) {
            magnitude = -magnitude;
        }
        if (magnitude >= 0x200) {
            old_flags = FIELD(arg0, u16, 0x2A);
            if ((s16)FIELD(arg0, u16, 0x2A) & 0x8000) {
                selected_flags = old_flags & 0x7FFF;
            } else {
                selected_flags = old_flags | 0x8000;
            }
            FIELD(arg0, u16, 0x2A) = selected_flags;
        }
        pos.h0C = 0;
        pos.h04 = 0;
        pos.h00 = FIELD(arg0, u16, 0x30);
        pos.h02 = FIELD(arg0, u16, 0x32);
        pos.h08 = FIELD(arg0, u16, 0x30) +
                  func_800644B8(FIELD(arg0, s16, 0x2C)) / 24;
        {
            s32 t = func_80064584(FIELD(arg0, s16, 0x2C));

            color[1] = 0x202020;
            color[0] = 0x202020;
            pos.h0A = FIELD(arg0, u16, 0x32) - t / 24;
        }
        if (FIELD(part, s16, 0x68) == 9) {
            func_80093C70();
            func_80093CEC(D_800D0128);
            func_80020948(D_80022454, &pos, color, arg0);
            FIELD(arg0, u16, 0x28) = 0x200;
            FIELD(arg0, u16, 0x2E) = 0;
            FIELD(arg0, s16, 0x36) = 7;
            FIELD(arg0, u16, 0x2A) &= 0x7FFF;
        } else {
            func_80020948(D_8002241C, &pos, color, arg0);
        }
        goto finish;
    }

    case 7: {
        s32 magnitude;
        u16 old_flags;
        u16 selected_flags;

        if (FIELD(arg0, s16, 0x2A) & 0x8000) {
            FIELD(arg0, u16, 0x2E) -= 4;
        } else {
            FIELD(arg0, u16, 0x2E) += 4;
        }
        magnitude = FIELD(arg0, s16, 0x2E);
        if (magnitude < 0) {
            magnitude = -magnitude;
        }
        if (magnitude >= 0x100) {
            old_flags = FIELD(arg0, u16, 0x2A);
            if ((s16)FIELD(arg0, u16, 0x2A) & 0x8000) {
                selected_flags = old_flags & 0x7FFF;
            } else {
                selected_flags = old_flags | 0x8000;
            }
            FIELD(arg0, u16, 0x2A) = selected_flags;
        }
        FIELD(arg0, u16, 0x28) =
            (FIELD(arg0, u16, 0x28) + FIELD(arg0, u16, 0x2E) + 0x1000) & 0xFFF;
        func_80022494(arg0);
        if (FIELD(part, s16, 0x68) != 0xA) {
            goto finish;
        }
        func_80093864();
        FIELD(global, void *, 0) = D_800930E4;
        draw.h14 = FIELD(arg0, s16, 0x34) * 0x10 + 0x64;
        draw.h16 = 0xB6;
        draw.h18 = 3;
        draw.w10 = 0x808080;
        draw.h1A = 0x7C80;
        draw.h1C &= 0xFFFE;
        draw.p04 = &D_800272B0[FIELD(arg0, s16, 0x34)];
        draw.p08 = &D_800272A0[FIELD(arg0, s16, 0x34)];
        draw.h00 = 0;
        draw.h02 = 0;
        draw.p0C = arg0;
        func_800206F4(D_80020618, &draw);
        FIELD(arg0, s16, 0x36) = 8;
        goto finish;
    }

    case 8:
        i = 7;
        global = (u8 *)D_800272A0;
        work = (u8 *)arg0 + 0x1C;
        do {
            void *node = FIELD(work, void *, 8);
            u8 *node_part = (u8 *)node + 0x20;
            u16 node_flags = FIELD(node_part, u16, 8);
            void *node_pos = FIELD(node, void *, 8);

            if ((node_flags & 3) == 0) {
                s32 delta0;
                s32 delta1;
                s32 x0;
                s32 y0;
                s32 y1;

                x0 = FIELD(node_pos, s16, 2);
                ASM_KEEP(x0);
                y0 = FIELD(compare, s16, 2);
                delta0 = x0 - y0;
                y0 = FIELD(node_pos, s16, 6);
                y1 = FIELD(compare, s16, 6);
                if (delta0 < 0) {
                    delta0 = -delta0;
                }
                delta1 = y0 - y1;
                if (delta1 < 0) {
                    delta1 = -delta1;
                }
                if (delta0 + delta1 < 0x20) {
                    FIELD(node_part, u16, 8) = node_flags | 1;
                    ((s16 *)global)[FIELD(arg0, s16, 0x34)]++;
                    if (((s16 *)global)[FIELD(arg0, s16, 0x34)] < 7) {
                        func_80053DA8(0x702);
                    } else {
                        func_80053DA8(0x703);
                    }
                }
            }
            i--;
            work -= 4;
        } while (i >= 0);
        if (FIELD(part, s16, 0x68) == 0xB) {
            FIELD(arg0, u16, 0x28) = 0x1E;
            FIELD(arg0, s16, 0x36) = 9;
        }
        goto finish;

    case 9:
        value = FIELD(arg0, u16, 0x28) - 1;
        FIELD(arg0, u16, 0x28) = value;
        if ((s16)value <= 0) {
            FIELD(arg0, s16, 0x36) = 0xA;
        }
        goto finish;

    case 10:
        flags = FIELD(arg0, u16, 0x2A);
        if ((flags & 2) == 0) {
            goto finish;
        }
        FIELD(arg0, u16, 0x2A) = flags & 0xFFFD;
        func_80093864();
        value = FIELD(arg0, u16, 0x34) + 1;
        FIELD(arg0, u16, 0x34) = value;
        if ((s16)value == 8) {
            func_80053DA8(0xB1);
            FIELD(arg0, u16, 0x28) = 0x78;
            FIELD(arg0, s16, 0x36) = 0xFF;
        } else {
            func_8002082C(arg0);
            FIELD(arg0, s16, 0x36) = 4;
        }
        goto finish;

    case 0xFF:
        value = FIELD(arg0, u16, 0x28) - 1;
        FIELD(arg0, u16, 0x28) = value;
        if ((s16)value <= 0) {
            func_800C15C0(0x20, 0x200);
            FIELD(arg0, u16, 0x2A) |= 1;
            FIELD(arg0, u16, 0x36)++;
        }
        goto finish;

    case 0x100:
        func_80033B78(0xA5);
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto finish;

    default:
        goto finish;
    }

finish:
    if (FIELD(arg0, s16, 0x36) >= 4) {
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
