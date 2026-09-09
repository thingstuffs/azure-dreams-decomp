#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 func_80033B2C();
extern void *func_8009C390();
extern s16 func_800C2AE8();
extern void func_8008F01C();
extern void func_8009B218();
extern void func_800C2E84();
extern void func_800A6328();

extern s8 D_80083498[];
extern s8 D_800A6684[];
extern s32 D_800D0C60[];
extern s32 D_800D0C78[];
extern s8 D_800D0C90[];
extern s8 D_800D0CAC[];
extern s8 D_800D0CC4[];
extern s8 D_800D0CE8[];
extern s8 D_800D0D0C[];
extern s8 D_800D0D30[];
extern s8 D_800D0D54[];
extern s32 D_80100E20;
extern void *D_80100E24;
extern void *D_80100E28;
extern void *D_80100E24_R;

__asm__(".set D_80100E24_R, 0x80100E24");

void func_800A64C0(void) {
    s8 *temp_obj;
    s8 *temp_s0;
    s8 *temp_s1;
    s32 *temp_s2;
    s32 temp_s4;
    s32 *temp_v0;
    s32 temp_v1;
    s32 temp_v0_3;
    s32 temp_v0_4;

    if (func_80033B2C(0xD) != 0) {
        if (func_80033B2C(0xE) != 0) {
            D_80100E24 = D_800D0D0C;
            D_80100E28 = D_800D0D30;
            D_80100E20 = 0x260000;
        } else {
            D_80100E24 = D_800D0CC4;
            D_80100E28 = D_800D0CE8;
            D_80100E20 = 0x1C0000;
        }
        temp_obj = func_8009C390(D_80083498, 0, D_800A6684, 0);
        if (temp_obj != NULL) {
            temp_s0 = *(s8 **)(temp_obj + 8);
            temp_s4 = *(s32 *)(temp_obj + 0xC);
            temp_s2 = D_800D0C78;
            *(s32 *)(temp_s0 + 0) = D_800D0C78[0];
            temp_s1 = temp_obj + 0x20;
            *(s32 *)(temp_s0 + 4) = temp_s2[1];
            *(s32 *)(temp_s0 + 8) = temp_s2[2];
            *(s16 *)(temp_s0 + 0xA) = func_800C2AE8(temp_s0);

            if ((u32)(*(s32 *)(temp_s0 + 8) + 0x300000) > 0x400000U) {
                temp_v0 = D_800D0C60;
                temp_v1 = temp_v0[0];
                D_800D0C78[0] = temp_v1;
                *(s32 *)(temp_s0 + 0) = temp_v1;
                temp_v1 = temp_v0[1];
                temp_s2[1] = temp_v1;
                *(s32 *)(temp_s0 + 4) = temp_v1;
                temp_v0_3 = temp_v0[2];
                temp_s2[2] = temp_v0_3;
                *(s32 *)(temp_s0 + 8) = temp_v0_3;
            }

            temp_v0_4 = *(s32 *)(temp_s0 + 4);
            *(s32 *)(temp_s1 + 0xA4) = temp_v0_4;
            *(s32 *)(temp_s1 + 0xA0) = temp_v0_4;
            func_8008F01C(temp_s1, temp_s0, D_800D0CAC);
            func_8009B218(temp_s1, temp_s0, temp_s4, D_800D0C90);
            func_800C2E84(temp_s1, temp_s4, D_80100E24_R);
            *(s8 **)(temp_s1 - 0x10) = D_800A6684;
            func_800A6328(D_800D0D54, 0);
        }
    }
}
