#include "common.h"

#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_80037534(void *arg0, s32 arg1, void *arg2);
extern void func_80036C7C(s32 *arg0, void *arg1, void *arg2);

extern u8 D_8006A988[];
extern u8 D_8006A994[];
extern u8 D_8006A9A0[];
extern u8 D_8006A9AC[];
extern u8 D_8006A9B8[];
extern u8 D_8006A9C4[];
extern u32 D_8006A9D0[];
extern u8 D_80081E90[];
extern u8 D_80081EA0[];
extern u8 D_80082B80[];
extern u8 D_80082B90[];
extern u8 D_80082BA0[];
extern u8 D_80082BB0[];

void func_80037394(void *arg0, s32 arg1, void *arg2) {
    u8 temp_a0;
    s8 *temp_v0;
    s16 temp_v1;

    if (func_80037534(arg0, arg1, arg2) != 0) {
        return;
    }

    func_80036C7C(M2C_FIELD(arg0, s32 **, 0x44) + 3, D_8006A988, D_80082B80);
    func_80036C7C(M2C_FIELD(arg0, s32 **, 0x44) + 3, D_8006A994, D_80082B90);
    func_80036C7C(M2C_FIELD(arg0, s32 **, 0x44) + 3, D_8006A9A0, D_80082BA0);
    func_80036C7C(M2C_FIELD(arg0, s32 **, 0x44) + 3, D_8006A9AC, D_80082BB0);
    func_80036C7C(M2C_FIELD(arg0, s32 **, 0x44) + 3, D_8006A9B8, D_80081E90);
    func_80036C7C(M2C_FIELD(arg0, s32 **, 0x44) + 3, D_8006A9C4, D_80081EA0);

    temp_v0 = (s8 *)M2C_FIELD(arg0, s32 **, 0x44);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x4A);
    temp_a0 = M2C_FIELD(temp_v0 + temp_v1, u8 *, 0x4C);
    if (temp_a0 & 0x80) {
        M2C_FIELD(arg0, u16 *, 0x64) = M2C_FIELD(arg0, u16 *, 0x64) + 1;
        if (M2C_FIELD(arg0, volatile u16 *, 0x64) & 1) {
            M2C_FIELD(arg2, s32 *, 0xC) = 0xC0C0C0;
        } else {
            M2C_FIELD(arg2, s32 *, 0xC) = 0;
        }
    } else {
        M2C_FIELD(arg2, s32 *, 0xC) = 0xC0C0C0;
    }

    M2C_FIELD(arg2, u32 *, 8) =
        D_8006A9D0[(temp_a0 & 0x7F) + M2C_FIELD(arg0, s16 *, 0x66)];
}
