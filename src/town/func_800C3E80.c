#include "common.h"

typedef struct {
    u8 pad0[0x18];
    s16 state;
    s16 index;
} TownState;

extern TownState D_8006ADBC;
extern u8 D_800D4094[];
extern u16 D_800D4244[];
extern u16 D_800D4268[];

extern s32 func_800C0F60(s16 arg0);
extern s32 func_800B28A0(void);
extern void func_8004437C(s32 arg0, s32 arg1);
extern void func_80053DA8(s32 arg0);
extern s32 func_800C16E0(u16 arg0);

s32 func_800C15E0(s32 arg0) {
    s32 temp_a1;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u8 *temp_s0;
    u8 *temp_base;
    u16 *temp_u16_base;
    u16 *temp_u16_entry;
    s32 temp_row;

    temp_a1 = func_800C0F60(D_8006ADBC.index);
    if (D_8006ADBC.state == 12) {
        u16 *output;

        output = D_800D4268;
        temp_base = D_800D4094;
        temp_s0 = temp_base + (temp_a1 * 10);
        temp_v0 = *(volatile u16 *)(temp_s0 + 6);
        output[2] = temp_v0;
        if ((s16)temp_v0 != -1) {
            func_8004437C(*(s16 *)(temp_s0 + 6), 0);
        }
        temp_v0_2 = *(u16 *)(temp_s0 + 8);
        output[3] = temp_v0_2;
        if ((s16)temp_v0_2 != -1) {
            return func_800C16E0(*(u16 *)(temp_s0 + 8) | arg0);
        }
        return 1;
    }
    temp_row = func_800B28A0();
    temp_u16_base = D_800D4244;
    temp_u16_entry = temp_u16_base + (temp_row * 2);
    temp_v0_3 = temp_u16_entry[0];
    D_800D4268[2] = temp_v0_3;
    func_8004437C((s16)temp_v0_3, 0);
    temp_v0_4 = temp_u16_entry[1];
    ((volatile u16 *)D_800D4268)[3] = temp_v0_4;
    func_80053DA8((temp_v0_4 | arg0) & 0xFFFF);
    return 1;
}
