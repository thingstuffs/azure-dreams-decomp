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

/* Waits for the effect delay, then moves and fades the sprite until it expires. */
void func_8183EE88(void *effect, StateBlock *motion, void *sprite) {
    void *owner;
    s16 phase;
    u16 delay;
    u8 shade;
    StateBlock *position = motion;

    owner = *(void **)effect;
    *(u16 *)((u8 *)owner + 0x52) |= 0x8000;
    phase = *(s16 *)((u8 *)effect + 0x4C);
    if (phase != 0) {
        if (phase != 1) {
            func_800247C0();
        }
        goto update_sprite;
    }

    delay = *(u16 *)((u8 *)effect + 0x48) - 1;
    *(u16 *)((u8 *)effect + 0x48) = delay;
    if ((delay << 0x10) <= 0) {
        func_8004491C((u8 *)effect - 0x20, D_80045340);
        *(u16 *)((u8 *)effect + 0x4C) += 1;
        func_800247C0();
    }
    return;

update_sprite:
    position->f0 += position->fC;
    position->f4 += position->f10;
    func_800478B8(sprite);

    if (*(u16 *)((u8 *)sprite + 0x14) & 0x6000) {
        *(u8 *)((u8 *)sprite + 4) = 0;
        *(u8 *)((u8 *)sprite + 5) = 0;
    }

    if ((s32)*(u8 *)((u8 *)sprite + 0xC) <= *(s16 *)((u8 *)effect + 0x4A)) {
        *(s32 *)((u8 *)sprite + 0xC) = 0;
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_800247C0();
    }

    shade = *(u8 *)((u8 *)sprite + 0xD) - *(u8 *)((u8 *)effect + 0x4A);
    *(u8 *)((u8 *)sprite + 0xD) = shade;
    *(u8 *)((u8 *)sprite + 0xC) = shade;
    *(u8 *)((u8 *)sprite + 0xE) -= *(u8 *)((u8 *)effect + 0x4A) * 2;
}
