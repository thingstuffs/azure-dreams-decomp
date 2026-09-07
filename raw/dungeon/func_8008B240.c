#include "common.h"

typedef struct {
    u16 unk0;
    u16 flags;
    s32 unk4;
    s16 unk8;
    s16 unkA;
} Status;

typedef void (*StateFunc)(void *, void *, void *, void *);

extern void func_80048A44(void *, u8, s32, s32);
extern void func_8008ACDC(void *, void *, void *, void *);
extern void func_80090B94(void *, void *);
extern s32 func_80094EA4(void);

extern u8 D_80083160[];
extern Status D_80083460;
extern s32 D_8008ACDC;
extern u8 D_800DD008[8];
extern u8 D_800DD010[8];
extern StateFunc D_800DD168[];

void func_800909A0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 *data = D_80083160;
    s32 state;
    Status *status;

    state = *(u8 *)((u8 *)arg0 + 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
        if (*(u16 *)((u8 *)arg2 + 0x14) & 0xE000) {
            *(u8 **)((u8 *)arg2 + 0x2C) = D_800DD008;
            func_80048A44(arg2,
                D_800DD008[((*(s16 *)(data + 0xC8) +
                    *(s16 *)((u8 *)arg3 + 0x2A) + 0x100) >> 9) & 7], 0, 1);
            *(u8 *)((u8 *)arg0 + 0x9B) += 1;
        }
        return;

state_1:
        if (*(u16 *)(data + 8) != 0) {
            *(u8 **)((u8 *)arg2 + 0x2C) = D_800DD010;
            func_80048A44(arg2,
                D_800DD010[((*(s16 *)(data + 0xC8) +
                    *(s16 *)((u8 *)arg3 + 0x2A) + 0x100) >> 9) & 7], 0, 1);
            *(u8 *)((u8 *)arg0 + 0x9B) += 1;

            status = &D_80083460;
            status->flags &= 0xFEFF;
            if ((s16)func_80094EA4() != 0) {
                if (status->unkA != 0) {
                    status->flags |= 4;
                }
                func_8008ACDC(arg0, arg1, arg2, arg3);
                if (*(u8 *)((u8 *)arg0 + 0x9A) != 0x17) {
                    func_80090B94(arg0, arg1);
                }
            }
        }
        return;

state_2:
        if ((s16)func_80094EA4() != 0) {
            if (D_80083460.unkA != 0) {
                D_80083460.flags |= 4;
            }
            func_8008ACDC(arg0, arg1, arg2, arg3);
            if (*(u8 *)((u8 *)arg0 + 0x9A) != 0x17) {
                D_800DD168[*(volatile u8 *)((u8 *)arg0 + 0x9A)](arg0, arg1, arg2, arg3);
                return;
            }
        }

        if (*(u16 *)((u8 *)arg2 + 0x14) & 0xE000) {
            *(u8 *)((u8 *)arg0 + 0x9A) = 0xE;
            *(s16 *)((u8 *)arg0 + 0xA4) = 0;
            *(s32 *)((u8 *)arg0 + 0x8C) = (s32)&D_8008ACDC;
        }
}
