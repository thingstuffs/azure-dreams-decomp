#include "common.h"

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
} StateBlock;

extern u8 D_80045340[];
extern s32 D_800814A0[3];
extern void func_800247C0() __attribute__((noreturn));
extern void func_8004491C(void *, void *);
extern void func_800478B8(void *);

void func_8183EE88(void *arg0, StateBlock *arg1, void *arg2) {
    void *temp_v1;
    s16 temp_v1_2;
    u16 temp_v0_2;
    u8 temp_v0;
    StateBlock *state = arg1;

    temp_v1 = *(void **)arg0;
    *(u16 *)((u8 *)temp_v1 + 0x52) |= 0x8000;
    temp_v1_2 = *(s16 *)((u8 *)arg0 + 0x4C);
    if (temp_v1_2 != 0) {
        if (temp_v1_2 != 1) {
            func_800247C0();
        }
        goto state_one;
    }

    temp_v0_2 = *(u16 *)((u8 *)arg0 + 0x48) - 1;
    *(u16 *)((u8 *)arg0 + 0x48) = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        func_8004491C((u8 *)arg0 - 0x20, D_80045340);
        *(u16 *)((u8 *)arg0 + 0x4C) += 1;
        func_800247C0();
    }
    return;

state_one:
    state->f0 += state->fC;
    state->f4 += state->f10;
    func_800478B8(arg2);

    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x6000) {
        *(u8 *)((u8 *)arg2 + 4) = 0;
        *(u8 *)((u8 *)arg2 + 5) = 0;
    }

    if ((s32)*(u8 *)((u8 *)arg2 + 0xC) <= *(s16 *)((u8 *)arg0 + 0x4A)) {
        *(s32 *)((u8 *)arg2 + 0xC) = 0;
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_800247C0();
    }

    temp_v0 = *(u8 *)((u8 *)arg2 + 0xD) - *(u8 *)((u8 *)arg0 + 0x4A);
    *(u8 *)((u8 *)arg2 + 0xD) = temp_v0;
    *(u8 *)((u8 *)arg2 + 0xC) = temp_v0;
    *(u8 *)((u8 *)arg2 + 0xE) -= *(u8 *)((u8 *)arg0 + 0x4A) * 2;
}
