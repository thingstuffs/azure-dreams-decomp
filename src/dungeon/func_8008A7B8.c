#include "common.h"

extern void *D_80088848[];
void func_80048A44();
s32 func_80094F74();
s32 func_80099F04();
s32 func_80099F70();
s32 func_800A2B04();
extern s16 D_80083228;
extern s32 D_80083460;
extern s16 D_80083464;
extern s32 D_8008ACDC;
extern s32 D_8008EAC8;
extern u8 D_800DD040[];
extern u8 D_800DD058[];
extern u8 D_800DD0C8[];

void func_8008FF18(u8 *a0, s32 *a1, u16 *a2, s32 *a3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    u8 *arg0 = a0;
    s32 *arg1 = a1;
    register u16 *arg2 ASM_REG("$18") = a2;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 *arg3 ASM_REG("$19") = a3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 *var_s4;
    s32 var_v0;
    u8 temp_v1;
    s32 temp_v1_3;
    s16 temp_v0;
    u8 *var_v0_2;
    u8 *var_v0_3;
    u16 *var_v1_2;

    temp_v1 = *(u8 *)(arg0 + 0x9B);
    if (temp_v1 >= 0xDU) {
        goto block_25;
    }
    (void)jt_keep; goto *D_80088848[(u32)(temp_v1)];
jt_c0:
jt_c8:
jt_c10:
    if (!(*(u16 *)((u8 *)arg2 + 0x14) & 0x6000)) {
        goto block_25;
    }
    temp_v1 = *(u8 *)(arg0 + 0x9B);
    var_v0 = 8;
    if (temp_v1 == 0) {
        var_v0 = 0xFFF00000;
    } else {
        if (temp_v1 != var_v0) {
            var_v0 = 0xFFEC0000;
        } else {
            var_v0 = 0xFFF80000;
        }
    }
    *(s32 *)((u8 *)arg1 + 0x14) = var_v0;
    if (!(*(s32 *)((u8 *)arg3 + 0x1C) & 0x100000)) {
        goto block_9;
    }
    var_v0_2 = D_800DD0C8;
    goto block_10;
block_9:
    var_v0_2 = D_800DD040;
block_10:
    *(u8 **)((u8 *)arg2 + 0x2C) = var_v0_2;
    func_80099F70(*(s32 *)((u8 *)arg3 + 0x5C));
    func_80099F04(*(s32 *)((u8 *)arg3 + 0x5C));
    var_v1_2 = (u16 *)&D_80083460;
    var_v1_2[1] = (u16) (var_v1_2[1] | 0x812);
    *(u16 *)((u8 *)arg0 + 0x98) = (u16) (*(u16 *)((u8 *)arg0 + 0x98) & 0xFFF3);
    func_80048A44(arg2, *(*(u8 **)((u8 *)arg2 + 0x2C) + (((s32) (D_80083228 + *(s16 *)((u8 *)arg3 + 0x2A) + 0x100) >> 9) & 7)), 0, 1);
    goto block_19;
jt_c1:
jt_c9:
jt_c11:
    var_s4 = (s16 *)&D_80083460;
    if (var_s4[2] != 0) {
        s32 div_v0;
        s32 div_v1;
        div_v0 = *(u8 *)((u8 *)arg2 + 0x24);
        div_v0 <<= 6;
        div_v1 = *(s16 *)((u8 *)arg1 + 2);
        div_v1 -= 0x20;
        *(s32 *)((u8 *)arg1 + 0xC) = ((div_v0 - div_v1) << 0x10) / (s16) var_s4[2];
        temp_v1_3 = *(s16 *)((u8 *)arg1 + 6) - 0x20;
        *(s32 *)((u8 *)arg1 + 0x10) = (s32) ((s32) ((*(u8 *)((u8 *)arg2 + 0x25) << 6) - temp_v1_3) << 0x10) / (s16) var_s4[2];
    }
    temp_v0 = (u16) var_s4[2] - 1;
    var_s4[2] = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_25;
    }
    var_s4[2] = 0;
    *(s32 *)((u8 *)arg1 + 0x10) = 0;
    *(s32 *)((u8 *)arg1 + 0xC) = 0;
    func_800A2B04(arg1, *(u8 *)((u8 *)arg2 + 0x24), *(u8 *)((u8 *)arg2 + 0x25));
    if (!(*(s32 *)((u8 *)arg3 + 0x1C) & 0x100000)) {
        goto block_17;
    }
    if ((func_80094F74(arg0, arg1, arg2, arg3) << 0x10) <= 0) {
        goto block_25;
    }
    var_v0_3 = (u8 *)&D_8008EAC8;
    goto block_24;
block_17:
    if ((u8) *(u8 *)(arg0 + 0x9B) < 0xAU) {
        goto block_22;
    }
    *(u8 **)((u8 *)arg2 + 0x2C) = D_800DD058;
    func_80048A44(arg2, *(*(u8 **)((u8 *)arg2 + 0x2C) + (((s32) (D_80083228 + *(s16 *)((u8 *)arg3 + 0x2A) + 0x100) >> 9) & 7)), 0, 1);
    var_s4[2] = 1;
block_19:
    *(u8 *)(arg0 + 0x9B) = (u8) (*(u8 *)(arg0 + 0x9B) + 1);
    return;
jt_c12:
    if (!(*(u16 *)((u8 *)arg2 + 0x14) & 0x6000)) {
        goto block_25;
    }
    D_80083464 = 0;
block_22:
    if ((func_80094F74(arg0, arg1, arg2, arg3) << 0x10) <= 0) {
        goto block_25;
    }
    var_v0_3 = (u8 *)&D_8008ACDC;
block_24:
    *(u8 **)((u8 *)arg0 + 0x8C) = var_v0_3;
block_25:
    return;
}
