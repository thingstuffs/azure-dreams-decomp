#include "common.h"

typedef struct {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0c;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1c;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2c;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3c;
    s32 f40;
    s32 f44;
    s8 f48;
    u8 f49;
    u8 f4a;
    s8 f4b;
    s8 f4c;
    s8 f4d[3];
} S_80085FA8;

extern s32 func_800589B8(S_80085FA8 *a0);
extern s32 func_80058A04(S_80085FA8 *a0);
extern s32 func_80058ABC(S_80085FA8 *a0);
extern s32 func_80058E50(S_80085FA8 *a0, s32 a1);
extern s32 D_800737C8[];
extern S_80085FA8 D_80085FA8[];
extern u32 D_800869A8[];
extern u32 D_800869B4[];

void func_80058E6C(S_80085FA8 *arg0, s32 arg1)
{
    S_80085FA8 *p;
    s32 cmd;
    u32 count;
    u32 limit;
    u32 rate;
    u32 quot;
    u32 tmp;
    u32 i;
    u32 shifted;

    cmd = arg1 & 0xFF;
    if (cmd == 0x51) {
        goto case_51;
    }
    if (cmd < 0x52) {
        if (cmd < 0) {
            goto default_case;
        }
        if (cmd < 0x10) {
            goto default_case;
        }
        if (cmd == 0x2F) {
            goto case_2F;
        }
        goto default_case;
    }
    if (cmd == 0x58) {
        goto case_58;
    }
    if (cmd < 0x59) {
        if (cmd == 0x54) {
            goto case_54;
        }
        goto default_case;
    }
    if (cmd == 0x59) {
        goto case_59;
    }
    goto default_case;

case_2F:
        arg0->f2c = 1;
        goto block_34;
case_51:
        if (D_800737C8[0] == 1) {
            arg0->f20 = func_80058ABC(arg0) & 0xFFFFFF;
        } else {
            arg0->f20 = func_800589B8(arg0) << 0x10;
            arg0->f20 = arg0->f20 | (func_800589B8(arg0) << 8);
            arg0->f20 = arg0->f20 | func_800589B8(arg0);
        }
        quot = 0x03938700U / (u32) arg0->f20;
        arg0->f24 = quot;
        arg0->f20 = quot;
        cmd = arg0->f24;
        tmp = ((u32) cmd * 100U) / 115U;
        arg0->f24 = tmp;
        tmp = tmp < 0x100U;
        if (tmp == 0) {
            arg0->f24 = 0xFF;
        }
        tmp = D_800869A8[0];
        if (tmp != 0x1E) {
            if (tmp < 0x1FU) {
                i = 0;
                if (tmp != 0x18) {
                } else {
                    goto block_23;
                }
            } else {
                i = 0;
                if (tmp == 0x3C) {
block_23:
                    shifted = (u32) arg0->f24 >> 1;
                    goto block_25;
                }
            }
        } else {
            shifted = (u32) arg0->f24 >> 2;
block_25:
            arg0->f24 = shifted;
            i = 0;
        }
        count = arg0->f24;
        rate = D_800869B4[0];
        if (rate != 0) {
            limit = rate;
            p = D_80085FA8;
            do {
                p->f24 = count;
                p->f20 = count;
                p++;
            } while (++i < limit);
            return;
        }
        return;
case_54:
        func_800589B8(arg0);
        func_800589B8(arg0);
        func_800589B8(arg0);
        goto case_59;
case_58:
        func_800589B8(arg0);
        arg0->f34 = func_80058ABC(arg0);
        return;
case_59:
        func_800589B8(arg0);
        func_800589B8(arg0);
block_34:
        func_800589B8(arg0);
        return;
default_case:
        func_80058E50(arg0, func_80058A04(arg0));
}
