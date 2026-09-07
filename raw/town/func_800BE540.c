#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_80033BC0(s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 rand(void);

extern s32 D_80045340;
extern s32 D_800814A0;
extern u8 D_80083498[];
extern u8 D_800BC00C[];
extern u8 D_800F1654[];

void func_800BBCA0(void *arg0, void *arg1)
{
    register void *self ASM_REG("$21") = arg0;
    register void *origin ASM_REG("$20") = arg1;
    register u16 nextState ASM_REG("$2");
    s32 state;
    u16 timer;
    s32 count;
    s32 random;
    u8 *object;
    u8 *sprite;
    u8 *motion;
    register s32 *position ASM_REG("$4");
    s32 *velocity;
    u8 *objectType;
    u8 *spriteType;

    ASM_KEEP(self);
    ASM_KEEP(origin);
    ASM_KEEP(nextState);
    timer = FIELD(self, u16, 0x48) - 1;
    state = FIELD(self, s16, 0x4C);
    FIELD(self, u16, 0x48) = timer;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        count = 7;
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    objectType = D_800BC00C;
    spriteType = D_800F1654;
    do {
        object = func_8003FD64(0x312, D_80083498);
        if (object != 0) {
            FIELD(object, u8 *, 0x10) = objectType;
            func_8004491C(object, &D_80045340);
            sprite = FIELD(object, u8 *, 0xC);
            motion = object + 0x20;

            random = rand();
            position = FIELD(object, s32 *, 8);
            position[0] = FIELD(origin, s32, 0) + (((random & 0x1FF) - 0x100) << 13);
            random = rand();
            position = FIELD(object, s32 *, 8);
            position[1] = FIELD(origin, s32, 4) + (((random & 0x1FF) - 0x100) << 13);
            random = rand();
            position = FIELD(object, s32 *, 8);
            position[2] = FIELD(origin, s32, 8) + (((random & 0x1FF) - 0x100) << 13);
            ASM_KEEP(position);

            FIELD(motion, u16, 0xC) = FIELD(origin, u16, 2);
            FIELD(motion, u16, 0xE) = FIELD(origin, u16, 6);
            FIELD(motion, u16, 0x10) = FIELD(origin, u16, 0xA);
            FIELD(sprite, s16, 0x1E) = 0x100;
            FIELD(sprite, s16, 0x1C) = 0x100;
            FIELD(sprite, s16, 0x10) = 0x20;
            FIELD(sprite, u16, 0x14) |= 0xC;
            FIELD(motion, s16, 0x48) = 6;
            FIELD(sprite, u8 *, 0) = spriteType;
            FIELD(sprite, s32, 8) = FIELD(spriteType, s32, 4);
            FIELD(sprite, s8, 4) = 0;
            FIELD(sprite, s8, 5) = 0;
            FIELD(sprite, s32, 0xC) = 0x101010;
        }
        count--;
    } while (count >= 0);
    if (func_80033BC0(0x97) != 0) {
        nextState = FIELD(self, u16, 0x4C);
        nextState++;
        goto store_state;
    }
    goto done;

state_one:
    count = 0x64;
    objectType = D_800BC00C;
    spriteType = D_800F1654;
    do {
        object = func_8003FD64(0x312, D_80083498);
        motion = object + 0x20;
        if (object != 0) {
            FIELD(object, u8 *, 0x10) = objectType;
            func_8004491C(object, &D_80045340);
            sprite = FIELD(object, u8 *, 0xC);

            random = rand();
            position = FIELD(object, s32 *, 8);
            position[0] = FIELD(origin, s32, 0) + (((random & 0x1FF) - 0x100) << 10);
            random = rand();
            position = FIELD(object, s32 *, 8);
            position[1] = FIELD(origin, s32, 4) + (((random & 0x1FF) - 0x100) << 10);
            random = rand();
            position = FIELD(object, s32 *, 8);
            position[2] = FIELD(origin, s32, 8) + (((random & 0x1FF) - 0x100) << 10);
            random = rand();
            velocity = FIELD(object, s32 *, 8);
            velocity[3] = ((random & 0x1FF) - 0x100) << 14;
            random = rand();
            velocity = FIELD(object, s32 *, 8);
            velocity[4] = ((random & 0x1FF) - 0x100) << 14;
            random = rand();
            velocity = FIELD(object, s32 *, 8);
            velocity[5] = ((random & 0x1FF) - 0x100) << 12;

            FIELD(sprite, s16, 0x1E) = 0x200;
            FIELD(sprite, s16, 0x1C) = 0x200;
            FIELD(sprite, s16, 0x10) = 0x20;
            FIELD(sprite, u16, 0x14) |= 0xC;
            FIELD(motion, s16, 0x48) = 0xF;
            FIELD(motion, s16, 0x4C) = 1;
            FIELD(sprite, u8 *, 0) = spriteType;
            FIELD(sprite, s32, 8) = FIELD(spriteType, s32, 4);
            FIELD(sprite, s8, 4) = 0;
            FIELD(sprite, s8, 5) = 0;
            FIELD(sprite, s32, 0xC) = 0x808080;
        }
        count--;
    } while (count >= 0);
    nextState = FIELD(self, u16, 0x4C);
    FIELD(self, u16, 0x48) = 0x10;
    nextState++;

store_state:
    FIELD(self, u16, 0x4C) = nextState;
    goto done;

state_two:
    if ((s16)timer < 0) {
        FIELD(self, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    return;
}
