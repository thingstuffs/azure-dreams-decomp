#include "common.h"

typedef struct {
    s32 x, y, z;
    s32 vx, vy, vz;
} VecState;

typedef struct S_800814A0 {
    s32 val;
    s32 pad[2];
} S_800814A0;

extern u8 D_80045340[];
extern S_800814A0 D_800814A0;

void func_80024DD8(void) __attribute__((noreturn));
extern void func_8004491C(void *, u8 *);
extern void func_800478B8(void *);

/* Updates effect motion, waits for its timer, then fades its sprite to black. */
void func_81845484(void *effect, VecState *motion, void *sprite) {
    void *owner = *(void **)effect;
    s32 z_velocity;
    s16 state;
    u16 timer;

    *(u16 *)((s8 *)owner + 0x52) |= 0x8000;

    z_velocity = motion->vz;
    if (z_velocity != 0) {
        z_velocity -= 0x20000;
    }
    motion->vz = z_velocity;
    motion->x += motion->vx;
    motion->y += motion->vy;
    motion->z += motion->vz;

    state = *(s16 *)((s8 *)effect + 0x4C);
    if (state != 0) {
        if (state == 1) {
            goto fade_sprite;
        }
        func_80024DD8();
    }

    timer = *(u16 *)((s8 *)effect + 0x48) - 1;
    *(u16 *)((s8 *)effect + 0x48) = timer;
    if ((s16)timer <= 0) {
        func_8004491C((s8 *)effect - 0x20, D_80045340);
        *(u16 *)((s8 *)effect + 0x4C) += 1;
        func_80024DD8();
    }
    return;

fade_sprite:
    func_800478B8(sprite);
    if (*(u16 *)((s8 *)sprite + 0x14) & 0x6000) {
        *(s8 *)((s8 *)sprite + 4) = 0;
        *(s8 *)((s8 *)sprite + 5) = 0;
    }
    if (*(u8 *)((s8 *)sprite + 0xC) <= *(s16 *)((s8 *)effect + 0x4A)) {
        *(u32 *)((s8 *)sprite + 0xC) = 0;
        *(u16 *)((s8 *)effect - 2) |= 0x8000;
        D_800814A0.val |= 0x8000;
        func_80024DD8();
    }
    {
        u8 brightness = *(u8 *)((s8 *)sprite + 0xE) - *(u8 *)((s8 *)effect + 0x4A);
        *(u8 *)((s8 *)sprite + 0xE) = brightness;
        *(u8 *)((s8 *)sprite + 0xD) = brightness;
        *(u8 *)((s8 *)sprite + 0xC) = brightness;
    }
}
