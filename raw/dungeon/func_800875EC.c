#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

M2C_UNK func_80048A44();
M2C_UNK func_80094ED4();
M2C_UNK func_8009A21C();
M2C_UNK func_8009A3D0();
s32 func_8009ADB8();
s32 func_8009B25C();
M2C_UNK func_8009F644();
M2C_UNK func_800A56E0();

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228[5];
extern u8 D_80083460[9];
extern u8 D_800DCFB8[];
extern u8 D_800DD018[];

void func_8008CD4C(void *arg0, M2C_UNK arg1, void *arg2, void *arg3, s32 arg4) {
    register void *actor ASM_REG("$20") = arg3;
    register s32 state ASM_REG("$3");
    s32 offset;
    s32 x;
    s32 y;
    s32 ent;
    u16 *xstep;
    u16 *ystep;
    u8 *control;

    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD018;
    state = arg4;
    M2C_FIELD(arg0, u8 *, 0x9A) = 0x18;
    M2C_FIELD(arg0, u8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;

    if ((s16)state != -2) {
        offset = ((M2C_FIELD(actor, u16 *, 0x2A) >> 8) & 0xE);
        xstep = (u16 *)((u8 *)D_8006CCD8 + offset);
        x = M2C_FIELD(arg2, u8 *, 0x24) + *xstep;
        ystep = (u16 *)((u8 *)D_8006CCE8 + offset);
        y = M2C_FIELD(arg2, u8 *, 0x25) + *ystep;
        ent = func_8009B25C(actor, x & 0xFFFF, y & 0xFFFF,
                            M2C_FIELD(actor, s16 *, 0x88));
        if (ent != 0) {
            if ((func_8009ADB8(actor, ent, (s16)x, (s16)y,
                               M2C_FIELD(actor, s16 *, 0x88)) << 16) != 0) {
                M2C_FIELD(arg0, s32 *, 0x124) = ent;
                func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24),
                              M2C_FIELD(arg2, u8 *, 0x25), 0x300);
                M2C_FIELD(arg2, u8 *, 0x24) =
                    M2C_FIELD(arg2, u8 *, 0x24) + *(u8 *)xstep;
                M2C_FIELD(arg2, volatile u8 *, 0x25) =
                    M2C_FIELD(arg2, u8 *, 0x25) + *(u8 *)ystep;
                func_8009A21C(M2C_FIELD(arg2, u8 *, 0x24),
                              M2C_FIELD(arg2, volatile u8 *, 0x25), 0x300);

                M2C_FIELD(actor, s32 *, 0x1C) |= 0x40000000;
                control = D_80083460;
                M2C_FIELD(control, s16 *, 4) = 0x20;
                M2C_FIELD(control, u16 *, 2) |= 8;
                M2C_FIELD(arg0, u8 *, 0x9B) = 0x10;
                M2C_FIELD(arg2, u8 **, 0x2C) = D_800DCFB8;
                M2C_FIELD(arg0, s16 *, 0x96) = 4;
                func_8009F644(actor, 8, 0, 0);
                func_800A56E0(0x50B);
                func_80094ED4(arg0, arg1, arg2, actor);
            }
        }
    }

    func_80048A44(
        arg2,
        M2C_FIELD(arg2, u8 **, 0x2C)
            [((D_80083228[0] + M2C_FIELD(actor, s16 *, 0x2A) + 0x100) >> 9) & 7],
        0, 1);
    ASM_KEEP(actor);
}
