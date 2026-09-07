#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u8 pad[0x24];
    u8 coord0;
    u8 coord1;
} Coord;

typedef struct {
    u8 pad0[0x1C];
    u32 flags;
    u8 pad1[0x68];
    u16 value;
} ArgObj;

typedef struct {
    u8 pad[8];
    u16 value;
} Entry;

extern s16 D_800DCED4[];
extern s32 D_80083460[3];
extern u8 D_80082E80[];
extern u8 D_800C1EC4;

extern void *func_8003FC64(s32);
extern s32 func_800429E4(void *);
extern void func_8009A3D0(u8, u8, s32);
extern s32 func_8009B88C(s32, u8, u8, s16 *, s16 *);
extern u16 func_800BCB04(s32, s32, s16);
extern void func_800C542C(void *, s16, s16, s32);
extern void func_8009A21C(u8, u8, s32);

void *func_800C1F28(void *arg0, s16 arg1) {
    s16 sp18;
    s16 sp1A;
    s32 var_a2;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u8 temp_v1_3;
    void *temp_v1;
    u8 *temp_s0;
    u8 *temp_s1;
    void *temp_v0;
    u8 *d83460;
    u8 *d82e80;
    s32 idx;
    u8 coord0;
    u8 coord1;

    temp_v0 = func_8003FC64(2);
    if (temp_v0 != NULL) {
        idx = func_800429E4(arg0);
        func_800C542C(arg0, D_800DCED4[idx], arg1, 3);
        var_a2 = 0x3000;
        d83460 = (u8 *)D_80083460;
        *(u16 *)(d83460 + 0xA) = (u16)(*(u16 *)(d83460 + 0xA) + 1);
        temp_s0 = *(u8 **)((u8 *)arg0 - 0x14);
        temp_s1 = (u8 *)temp_v0 + 0x20;
        coord0 = temp_s0[0x24];
        coord1 = temp_s0[0x25];
        if (FIELD(arg0, u32, 0x1C) & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(coord0, coord1, var_a2);
        d82e80 = D_80082E80;
        if ((func_8009B88C(0, d82e80[0x24], d82e80[0x25], &sp18, &sp1A) << 16) == 0) {
            sp18 = ((Coord *)temp_s0)->coord0;
            temp_v0_3 = ((ArgObj *)arg0)->value;
            temp_v1_3 = ((Coord *)temp_s0)->coord1;
            sp1A = temp_v1_3;
            ((Entry *)temp_s1)->value = temp_v0_3;
        } else {
            temp_v0_2 = func_800BCB04(((sp18 << 6) + 0x20) & 0xFFE0,
                                       ((sp1A << 6) + 0x20) & 0xFFE0,
                                       (s16)(FIELD(arg0, u16, 0x88) - 0x20));
            *(u16 *)(temp_s1 + 8) = temp_v0_2;
            if ((s16)temp_v0_2 >= 0x201) {
                *(u16 *)(temp_s1 + 8) = func_800BCB04(((sp18 << 6) + 0x20) & 0xFFE0,
                                                       ((sp1A << 6) + 0x20) & 0xFFE0,
                                                       -0x400);
            }
        }
        temp_s0[0x24] = (u8)sp18;
        temp_s0[0x25] = (u8)sp1A;
        FIELD(arg0, u16, 0x88) = *(u16 *)(temp_s1 + 8);
        *(void **)((u8 *)temp_v0 + 0x10) = &D_800C1EC4;
        *(void **)(temp_s1 + 0xC) = arg0;
        *(s16 *)(temp_s1 + 2) = 0x20;
        *(s16 *)(temp_s1 + 4) = temp_s0[0x24];
        temp_v1 = *(void **)(temp_s1 + 0xC);
        *(s16 *)(temp_s1 + 6) = temp_s0[0x25];
        func_8009A21C(temp_s0[0x24], temp_s0[0x25],
                      (FIELD(temp_v1, s32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
    }
    return temp_v0;
}
