#include "common.h"

extern void func_800C768C(s16);
extern s16 func_800BCB04(u16, u16, s16);
extern u8 D_800DF63C[];
extern u8 D_800E3D20[];
extern u16 D_800E58F8[];

void func_800C75D0(void *arg0) {
    struct S_80083178 *sp = &D_80083178;
    s16 temp_a0;
    s16 temp_v0;
    s16 temp_v0_3;
    u16 *temp_v0_2;
    void *temp_v1;

    temp_v1 = *(void **)((char *)arg0 + 0x34);
    if ((temp_v1 != 0) && (*(u16 *)((char *)temp_v1 + 0x1E) & 0x8000)) {
        u16 *e = D_800E58F8;
        *(void **)((char *)arg0 + 0x34) = 0;
        e[1] = *(u16 *)((char *)*(void **)((char *)arg0 + 0xC) + 2);
        e[3] = *(u16 *)((char *)*(void **)((char *)arg0 + 0xC) + 6);
        e[5] = *(u16 *)((char *)*(void **)((char *)arg0 + 0xC) + 0xA);
        *(void **)((char *)arg0 + 0xC) = e;
    }
    temp_a0 = *(s16 *)((char *)arg0 + 0x24);
    if (temp_a0 > 0) {
        *(u16 *)((char *)sp + 0x98) = (u16)*(s16 *)((char *)sp + 0x98) +
            (*(s16 *)((char *)arg0 + 0x26) - *(s16 *)((char *)sp + 0x98)) / temp_a0;
        func_800C768C(temp_a0);
        return;
    }
    D_800E3D20[0] = 0;
    temp_v0 = *(s16 *)((char *)arg0 + 0x24) - 1;
    *(s16 *)((char *)arg0 + 0x24) = temp_v0;
    if (temp_v0 < -0x80) {
        *(s16 *)((char *)arg0 + 0x24) = -0x80;
    }
    *(u16 *)((char *)arg0 + 4) = *(u16 *)((char *)*(void **)((char *)arg0 + 0xC) + 2);
    *(u16 *)((char *)arg0 + 6) = *(u16 *)((char *)*(void **)((char *)arg0 + 0xC) + 6);
    temp_v0_2 = *(u16 **)((char *)arg0 + 0xC);
    temp_v0_3 = func_800BCB04(temp_v0_2[1], temp_v0_2[3], (s16)(temp_v0_2[5] - 0x20));
    *(s16 *)((char *)arg0 + 8) = temp_v0_3;
    if (temp_v0_3 >= 0x201) {
        *(s16 *)((char *)arg0 + 8) = *(u16 *)((char *)*(void **)((char *)arg0 + 0xC) + 0xA);
    }
    *(s16 *)((char *)sp + 0xA4) = (u16)*(s16 *)((char *)sp + 0xA4) + ((s32)((s16)*(u16 *)((char *)arg0 + 4) - *(s16 *)((char *)sp + 0xA4)) >> 2);
    *(s16 *)((char *)sp + 0xA6) = (u16)*(s16 *)((char *)sp + 0xA6) + ((s32)((s16)*(u16 *)((char *)arg0 + 6) - *(s16 *)((char *)sp + 0xA6)) >> 2);
    if (D_800DF63C[0] != 0) {
        *(s16 *)((char *)sp + 0xA8) = (u16)*(s16 *)((char *)sp + 0xA8) + ((s32)(*(s16 *)((char *)arg0 + 8) - *(s16 *)((char *)sp + 0xA8)) >> 2);
    }
    D_800DF63C[0] = (s8)(*(s16 *)((char *)sp + 0xA8) != *(s16 *)((char *)arg0 + 8));
    *(u16 *)((char *)sp + 0x94) = (s32)(*(u16 *)((char *)sp + 0x94) << 0x10) >> 0x12;
    *(u16 *)((char *)sp + 0x96) = (s32)(*(u16 *)((char *)sp + 0x96) << 0x10) >> 0x12;
}
