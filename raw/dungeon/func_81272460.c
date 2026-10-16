#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009A028(s32);                         /* extern */
extern s32 D_80155F90;
extern s32 D_80155FBC;
extern s32 D_80156710;
extern s32 D_80156714;
extern s16 D_80156718;

void func_80155C60(void) {
    s16 var_s1;
    s16 var_v0;
    s32 temp_a0;
    s32 temp_s0;
    s32 var_v1;
    void *temp_a1;
    void *temp_v1;

    var_s1 = 0;
    temp_a1 = D_80156710 + 0x20;
    M2C_FIELD(temp_a1, s8 *, 0xBA) = 1;
    D_80156718 = 0;
    *(u16 *)0x8001371A = 0;
    *(u16 *)0x80013718 = 0;
    *(u16 *)0x80013716 = 0;
    *(u16 *)0x8001371C = (s32) D_80155F90;
    *(u16 *)0x80013714 = (*(u16 *)0x80013714 | 9) & 0xFFEF;
    M2C_FIELD(temp_a1, s16 *, 0xB8) = 0;
    D_80156714 = D_80155FBC;
    var_v1 = 0 << 0x10;
    do {
        temp_s0 = var_v1 >> 0xE;
        temp_a0 = M2C_FIELD((temp_s0 + *(s32 *)0x800E3D7C), s32 *, 0xAC);
        var_v0 = var_s1 + 1;
        if (temp_a0 != 0) {
            func_8009A028(temp_a0);
            temp_v1 = M2C_FIELD((temp_s0 + *(s32 *)0x800E3D7C), s32 *, 0xAC) - 0x20;
            M2C_FIELD(temp_v1, s32 *, 0x10) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x10) | 0x80000000);
            var_v0 = var_s1 + 1;
        }
        var_s1 = var_v0;
        var_v1 = var_s1 << 0x10;
    } while (var_v0 < 2);
}
