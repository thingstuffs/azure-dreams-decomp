#include "common.h"

#define NULL ((void *)0)

s32 func_800A6D30(void *, void *, s32, s32);
s32 func_800A0818(u8, u8, u8, u8, void *);
void func_800B4C7C(s32, void *, s32, s32);
s32 func_800990FC(void);
s32 func_80099194(void *, s32);
s32 func_8003AD08(s32, s32);
s32 func_80099734(void *, s32);
void func_80099290(s32);
void func_800A5720(s32);

extern u8 D_80088CAC[];
extern u8 D_800E0D51[];
extern u8 D_800E0D6D[];

void func_8009BFF8(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    int sp18;
    s32 s0;
    s16 s3;
    s32 s0_2;
    s32 temp;
    u8 *v0;
    void *v0_2;
    void *v1;

    v0 = *(u8 **)((s8 *)arg0 + 0x50);
    if (v0 != NULL && *v0 == 0xB && !(func_800A6D30(arg0, arg1, arg2, arg3) & 3)) {
        s0 = ((s32)(*(u16 *)((s8 *)arg0 + 0x64) << 0x10)) >> 0x12;
        s3 = s0;
        *(u16 *)((s8 *)arg1 + 0x64) += s0;
        if (s3 != 0) {
            v0_2 = *(void **)((s8 *)arg0 - 0x14);
            v1 = *(void **)((s8 *)arg1 - 0x14);
            *(void **)((s8 *)arg1 + 0x60) = arg0;
            *(s16 *)((s8 *)arg1 + 0x6A) = func_800A0818(
                *(u8 *)((s8 *)v0_2 + 0x24),
                *(u8 *)((s8 *)v0_2 + 0x25),
                *(u8 *)((s8 *)v1 + 0x24),
                *(u8 *)((s8 *)v1 + 0x25),
                &sp18
            );
            func_800B4C7C(3, arg1, -s0, 0);
            temp = func_800990FC();
            s0_2 = temp;
            temp = func_80099194(D_800E0D51, s0_2);
            temp = func_8003AD08(-s3, temp);
            temp = func_80099194(D_800E0D6D, temp);
            temp = func_80099734(arg1, temp);
            temp = func_80099194(D_80088CAC, temp);
            func_80099290(temp);
            func_800A5720(s0_2);
        }
    }
}
