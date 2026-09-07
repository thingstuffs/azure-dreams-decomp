#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80048A44();
extern void func_8008F7DC(void) __attribute__((noreturn));
M2C_UNK func_8009A66C();
M2C_UNK func_8009F644();
s32 func_800A44E0();
s32 func_800A7234();
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_80081485;
extern s16 D_80083228;
extern u16 D_80083460[];
extern u8 D_800DD0D0[];

void func_8008F6EC(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 sp18;
    s16 sp1A;
    s16 sp1C;
    s32 temp_v1;
    register s32 var_s1 ASM_REG("$17");

    var_s1 = 0;
    if (D_80081485 == 0x13) {
        var_s1 = (func_8009A66C(M2C_FIELD(arg3, s16 *, 0x2A), arg2, arg3, 0x20) << 0x10) > 0;
        ASM_TAILSLOT_PIN_TIED(var_s1);
        func_8008F7DC();
    }
    if ((func_800A44E0(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg3, s16 *, 0x88), M2C_FIELD(arg3, s16 *, 0x2A)) << 0x10) == 0) {
        temp_v1 = ((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE;
        if ((func_800A7234((s16) (M2C_FIELD(arg2, u8 *, 0x24) + *(u16 *)(D_8006CCD8 + temp_v1)), (s16) (M2C_FIELD(arg2, u8 *, 0x25) + *(u16 *)(D_8006CCE8 + temp_v1)), M2C_FIELD(arg3, s16 *, 0x88), &sp18, &sp1A, &sp1C) << 0x10) != 0) {
            do { var_s1 = 1; } while (0);
        }
    }
    if (var_s1 != 0) {
        M2C_FIELD(arg0, s8 *, 0x9A) = 0x1F;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD0D0;
        func_80048A44(arg2, D_800DD0D0[(((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100)) >> 9) & 7], 0, 1);
        D_80083460[5] = D_80083460[5] + 1;
        func_8009F644(arg3, 0x28, 0, 0);
    }
}
