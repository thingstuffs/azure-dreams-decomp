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
extern s32 func_80094EA4(void);

extern u8 D_80083160[];
extern Status D_80083460;
extern s32 D_8008ACDC;
extern u8 D_800DD008[8];
extern u8 D_800DD010[8];
extern StateFunc D_800DD168[];

/* Advances the camera reset animation and resumes actor state handling. */
void to_camera_zero_00(void *actor, void *context, void *animation, void *transform)
{
    u8 *camera = D_80083160;
    s32 phase;
    Status *status;

    phase = *(u8 *)((u8 *)actor + 0x9B);
    if (phase == 1) {
        goto state_1;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto state_0;
        }
        return;
    }
    if (phase == 2) {
        goto state_2;
    }
    return;

state_0:
    if (*(u16 *)((u8 *)animation + 0x14) & 0xE000) {
        *(u8 **)((u8 *)animation + 0x2C) = D_800DD008;
        func_80048A44(animation,
            D_800DD008[((*(s16 *)(camera + 0xC8) +
                *(s16 *)((u8 *)transform + 0x2A) + 0x100) >> 9) & 7], 0, 1);
        *(u8 *)((u8 *)actor + 0x9B) += 1;
    }
    return;

state_1:
    if (*(u16 *)(camera + 8) != 0) {
        *(u8 **)((u8 *)animation + 0x2C) = D_800DD010;
        func_80048A44(animation,
            D_800DD010[((*(s16 *)(camera + 0xC8) +
                *(s16 *)((u8 *)transform + 0x2A) + 0x100) >> 9) & 7], 0, 1);
        *(u8 *)((u8 *)actor + 0x9B) += 1;

        status = &D_80083460;
        status->flags &= 0xFEFF;
        if ((s16)func_80094EA4() != 0) {
            if (status->unkA != 0) {
                status->flags |= 4;
            }
            func_8008ACDC(actor, context, animation, transform);
            if (*(u8 *)((u8 *)actor + 0x9A) != 0x17) {
                D_800DD168[*(volatile u8 *)((u8 *)actor + 0x9A)](actor, context, animation, transform);
            }
        }
    }
    return;

state_2:
    if ((s16)func_80094EA4() != 0) {
        if (D_80083460.unkA != 0) {
            D_80083460.flags |= 4;
        }
        func_8008ACDC(actor, context, animation, transform);
        if (*(u8 *)((u8 *)actor + 0x9A) != 0x17) {
            D_800DD168[*(volatile u8 *)((u8 *)actor + 0x9A)](actor, context, animation, transform);
            return;
        }
    }

    if (*(u16 *)((u8 *)animation + 0x14) & 0xE000) {
        *(u8 *)((u8 *)actor + 0x9A) = 0xE;
        *(s16 *)((u8 *)actor + 0xA4) = 0;
        *(s32 *)((u8 *)actor + 0x8C) = (s32)&D_8008ACDC;
    }
}
