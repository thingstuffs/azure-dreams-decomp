#include "common.h"

typedef struct S_80085458 {
    s16 f00, f02, f04;
    u16 f06;
    u8 pad08[2];
    u16 f0a;
    u8 pad0c[0xC];
    s16 f18;
    u16 f1a;
    s8 f1c, f1d;
    u8 pad1e[8];
    s8 f26, f27, f28;
    u8 pad29[3];
    s32 f2c, f30;
    u8 pad34[8];
    s32 f3c;
    u8 pad40[2];
    s8 f42, f43, f44;
    u8 pad45[3];
    s32 f48, f4c;
    u8 pad50[8];
    s32 f58;
    u8 pad5c[0x14];
    s32 f70, f74;
} S_80085458;

extern S_80085458 D_80085458[64];
extern s32 D_80073740[];
extern s32 D_80085F98[3];

extern s32 func_80056D44(s32 arg0, S_80085458 *arg1);
extern void func_80056DB4(s32 arg0);
extern void func_8005E97C(s32 arg0, s32 arg1);
extern s32 func_8005EB78(s32 arg0);

/* Activates one SPU slot, services it until completion, then clears busy. */
s32 func_8005C4D0(s16 arg0)
{
    u8 *access = (u8 *)D_80085F98;
    u8 *base = (u8 *)D_80085458;
    s32 idx = arg0;
    s32 tmp;
    u8 *ent;
    s32 ret;
    u16 active;

    ent = base + idx * 0x78;
    active = *(u16 *)(ent + 0x1A);
    *(s32 *)access = 1;
    if (active == 0) {
        goto fail;
    }
    if (*(u16 *)(ent + 6) < 0x10) {
        goto fail;
    }

    tmp = D_80073740[idx];
    access = ent;
    *(u16 *)(access + 0x1A) = 0;
    *(u16 *)(access + 0x0A) = 0;
    func_80056D44(idx, (S_80085458 *)access);
    func_80056DB4(idx);
    func_8005E97C(0, D_80073740[idx]);
    do {
        func_8005E97C(0, tmp);
        ret = func_8005EB78(tmp);
        if (ret == 2) {
            goto success;
        }
    } while (ret != 0);
    goto success;

fail:
    D_80085F98[0] = 0;
    return -1;

success:
    D_80085F98[0] = 0;
    return 0;
}
