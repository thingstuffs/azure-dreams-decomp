#include "common.h"

/* D_80085458[64]: same table layout inferred in src/w_80056A08.c (S_80085458). */
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
} S_80056C30_85458;

/* D_80085014 == &D_80084960[11] (D_80084960[16] is the array declared in
   src/w_80056A08.c as S_80084960); declared here as a standalone instance of
   the same struct family with only the touched fields given exact offsets. */
typedef struct {
    u8 pad00[0x04];
    s32 f04;
    s32 f08;
    s32 f0c;
    u8 pad10[0x04];
    s32 f14;
    s32 f18;
    s32 f1c;
    s32 f20;
    s32 f24;
    u8 pad28[0x50 - 0x28];
    s16 f50;
    u8 pad52[0x94 - 0x52];
    s32 f94;
} S_80056C30_85014;

extern s32 D_80073734[4];
extern s32 D_80073740[64];
extern S_80056C30_85458 D_80085458[64];
extern S_80056C30_85014 D_80085014;

extern void func_80056A08(void);
extern s32 func_80056DB4(s32 arg0);
extern void func_8005E97C(s32 arg0, s32 arg1);

/* Resets global state, re-registers active slots, and initializes the shared request with their combined flags. */
void func_80056C30(void) {
    s32 slot;
    s32 all_flags;
    s32 slot_flags;

    func_80056A08();

    all_flags = 0;
    for (slot = 0; slot < D_80073734[0]; slot++) {
        D_80085458[slot].f00 = slot;
        D_80085458[slot].f1a = 0;
        D_80085458[slot].f18 = 0x40;
        D_80085458[slot].f70 = 0x40;
        D_80085458[slot].f74 = 0x40;
        slot_flags = D_80073740[slot];
        func_80056DB4(slot);
        all_flags |= slot_flags;
        func_8005E97C(0, slot_flags);
    }

    D_80085014.f0c = 0x7F;
    D_80085014.f04 = 0x40;
    D_80085014.f18 = 0;
    D_80085014.f1c = 0x40;
    D_80085014.f14 = 0x7F;
    D_80085014.f20 = 0x7F;
    D_80085014.f24 = 0x7F;
    D_80085014.f08 = 0;
    D_80085014.f94 = 0;
    D_80085014.f50 = 0;
    func_8005E97C(0, all_flags);
}
