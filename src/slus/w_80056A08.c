#include "common.h"

/* Global-state initializer: resets D_80085FA8[32], D_80085458[count], D_80084960[16]
   tables and D_80073738; OR-accumulates flags from D_80073740 into a value passed
   to func_8005E97C. Matches gcc-2.7.2-cdk -O2 (code8.c TU). */
typedef struct { s16 f0; s16 pad[7]; } S_80073738;

typedef struct {
    s32 f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c;
    s32 f30, f34, f38, f3c, f40, f44;
    s8 f48; u8 f49; s8 f4a, f4b, f4c, f4d[3];
} S_80085FA8;

typedef struct {
    s16 f00, f02, f04; u16 f06;
    u8 pad08[0x10];
    s16 f18, f1a; s8 f1c, f1d;
    u8 pad1e[8];
    s8 f26, f27, f28; u8 pad29[3];
    s32 f2c, f30; u8 pad34[8];
    s32 f3c; u8 pad40[2];
    s8 f42, f43, f44; u8 pad45[3];
    s32 f48, f4c; u8 pad50[8];
    s32 f58; u8 pad5c[0x14];
    s32 f70, f74;
} S_80085458;

typedef struct {
    s32 f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c;
    s8 f30; u8 pad31[9];
    s16 f3a; u8 pad3c[4];
    s16 f40; u8 pad42[2];
    s32 f44, f48; u8 pad4c[4];
    s16 f50; u8 pad52[0xD];
    s8 f5f, f60, f61; u8 pad62[2];
    s32 f64, f68; u8 pad6c[0xE];
    s8 f7a, f7b, f7c; u8 pad7d[3];
    s32 f80, f84; u8 pad88[0xC];
    s32 f94; s8 f98; u8 pad99[3];
} S_80084960;

extern s32 D_80073734[4];
extern S_80073738 D_80073738;
extern s32 D_80073740[64];
extern S_80084960 D_80084960[16];
extern S_80085458 D_80085458[64];
extern S_80085FA8 D_80085FA8[32];

extern s32 func_80056DB4(s32 arg0);
extern void func_8005E97C(s32 arg0, s32 arg1);

void func_80056A08(void) {
    s32 acc;
    s32 i;
    s32 tmp;

    acc = 0;
    D_80073738.f0 = 0x7F;
    for (i = 0; i < 0x20; i++) {
        D_80085FA8[i].f00 = 0;
        D_80085FA8[i].f04 = 0;
        D_80085FA8[i].f08 = 0;
        D_80085FA8[i].f0c = 0;
        D_80085FA8[i].f10 = 0;
        D_80085FA8[i].f18 = 0;
        D_80085FA8[i].f1c = 0;
        D_80085FA8[i].f20 = 0;
        D_80085FA8[i].f24 = 0;
        D_80085FA8[i].f28 = 0;
        D_80085FA8[i].f2c = 1;
        D_80085FA8[i].f34 = 0;
        D_80085FA8[i].f38 = 0;
        D_80085FA8[i].f3c = 0x78;
        D_80085FA8[i].f40 = 0;
        D_80085FA8[i].f48 = 0;
        D_80085FA8[i].f49 = 0xFF;
        D_80085FA8[i].f4a = 0;
        D_80085FA8[i].f4c = 0;
    }

    for (i = 0; i < D_80073734[0]; i++) {
        if ((u16)D_80085458[i].f06 < 0x10) {
            D_80085458[i].f00 = i;
            D_80085458[i].f1a = 0;
            D_80085458[i].f18 = 0x40;
            D_80085458[i].f1d = 0;
            D_80085458[i].f27 = 0;
            D_80085458[i].f26 = 0;
            D_80085458[i].f28 = 0;
            D_80085458[i].f2c = 0;
            D_80085458[i].f30 = 0;
            D_80085458[i].f3c = 0;
            D_80085458[i].f43 = 0;
            D_80085458[i].f42 = 0;
            D_80085458[i].f44 = 0;
            D_80085458[i].f48 = 0;
            D_80085458[i].f4c = 0;
            D_80085458[i].f58 = 0;
            D_80085458[i].f70 = 0x40;
            D_80085458[i].f74 = 0x40;
            tmp = D_80073740[i];
            func_80056DB4(i);
            acc |= tmp;
            func_8005E97C(0, tmp);
        }
    }

    for (i = 0; i < 0x10; i++) {
        D_80084960[i].f0c = 0x7F;
        D_80084960[i].f04 = 0x40;
        D_80084960[i].f18 = 0;
        D_80084960[i].f1c = 0x40;
        D_80084960[i].f14 = 0x7F;
        D_80084960[i].f20 = 0x7F;
        D_80084960[i].f24 = 0x7F;
        D_80084960[i].f08 = 0;
        D_80084960[i].f3a = 0;
        D_80084960[i].f44 = 0;
        D_80084960[i].f40 = 0;
        D_80084960[i].f48 = 0;
        D_80084960[i].f94 = 0;
        D_80084960[i].f30 = 0;
        D_80084960[i].f60 = 0;
        D_80084960[i].f5f = 0;
        D_80084960[i].f61 = 0;
        D_80084960[i].f64 = 0;
        D_80084960[i].f68 = 0;
        D_80084960[i].f7b = 0;
        D_80084960[i].f7a = 0;
        D_80084960[i].f7c = 0;
        D_80084960[i].f80 = 0;
        D_80084960[i].f84 = 0;
        D_80084960[i].f28 = 0;
        D_80084960[i].f2c = 0;
        D_80084960[i].f50 = 0;
        D_80084960[i].f98 = 0;
    }

    func_8005E97C(0, acc);
}
