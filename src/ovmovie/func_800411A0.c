#include "modules/ovmovie_libpress.h"
/* Reset the decoder and optionally upload its quantization and coefficient tables. */
static void func_801779A0(s32 mode) {
    switch (mode) {
    case 0:
        *(volatile u32 *)D_80178380 = 0x80000000;
        *(volatile u32 *)D_80178354 = 0;
        *(volatile u32 *)D_80178360 = 0;
        *(volatile u32 *)D_80178380 = 0x60000000;
        func_80177A9C((s32 *)&D_8017823C, 0x20);
        func_80177A9C((s32 *)&D_801782C0, 0x20);
        return;
    case 1:
        *(volatile u32 *)D_80178380 = 0x80000000;
        *(volatile u32 *)D_80178354 = 0;
        *(volatile u32 *)D_80178360 = 0;
        (void)*(volatile s32 *)D_80178360;
        *(volatile u32 *)D_80178380 = 0x60000000;
        return;
    default:
        printf(&D_80176800, mode);
        return;
    }
}
