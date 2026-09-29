#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

extern s32 func_8003DB94();
extern s32 func_8009A180();
extern s32 func_800A2C34();
extern void func_800A9A04();
extern void func_800A9A0C();
extern void func_800AA258();
extern s32 func_800AA6B4();
extern void func_800AA888();
extern void func_800DA660();

extern u8 D_800D8C64[];
extern void *D_800E262C[];

#define U8_AT(p, n)  (*(u8 *)((u8 *)(p) + (n)))
#define S8_AT(p, n)  (*(s8 *)((u8 *)(p) + (n)))
#define U16_AT(p, n) (*(u16 *)((u8 *)(p) + (n)))
#define S16_AT(p, n) (*(s16 *)((u8 *)(p) + (n)))
#define S32_AT(p, n) (*(s32 *)((u8 *)(p) + (n)))
#define PTR_AT(p, n) (*(void **)((u8 *)(p) + (n)))

/* Advance the actor action state, updating its animation and the dungeon action count. */
void func_800DA398(void *controller, s32 context, void *sprite, void *actor) {
    s32 actor_flags;
    s32 state;

    state = U8_AT(controller, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state >= 2) {
        goto state_high;
    }
    if (state == 0) {
        goto state_zero;
    }
    return;

state_high:
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    if (!(U16_AT(sprite, 0x14) & 0xE000)) {
        return;
    }
    dungeonStatus.unk_0A--;
    PTR_AT(sprite, 0x2C) = D_800E262C;
    func_8003DB94(sprite,
        *(void **)((u8 *)D_800E262C +
            (((gameWork.view.viewAngle + S16_AT(actor, 0x2A) + 0x100) >> 7) & 0x1C)),
        0);
    goto advance_state;

state_one:
    if (dungeonStatus.flags & 0x1000) {
        return;
    }
    if (S16_AT(actor, 0x64) != 0) {
        if (func_800AA6B4(controller, context, sprite, 0) != 0) {
            return;
        }
    }
    if ((func_800A2C34(actor) << 0x10) != 0) {
        return;
    }
    actor_flags = S32_AT(actor, 0x1C);
    if (actor_flags & 0x100) {
        func_800AA258(controller, context, sprite, actor);
        return;
    }
    if (actor_flags & 0x80000) {
        func_800AA888(controller, context, sprite, actor);
        func_800DA660(controller, context, sprite, actor);
        return;
    }
    if (S8_AT(actor, 0x6D) == 0) {
        return;
    }
    if ((func_800A2C34(actor) << 0x10) == 0) {
        goto permitted;
    }
    if ((func_8009A180(actor,
            *(s32 *)((u8 *)D_800814A8 + 0x58) + 0x20) << 0x10) != 0) {
        return;
    }

permitted:
    func_800A9A0C(actor);
    func_800A9A04(actor);
    if (U8_AT(actor, 0x25) == 0) {
        return;
    }
    PTR_AT(sprite, 0x2C) = D_800E262C;
    func_8003DB94(sprite,
        *(void **)((u8 *)D_800E262C +
            (((gameWork.view.viewAngle + S16_AT(actor, 0x2A) + 0x100) >> 7) & 0x1C)),
        0);
    S32_AT(actor, 0x1C) |= 0x40000;
    dungeonStatus.unk_0A++;

advance_state:
    U8_AT(controller, 0x9B)++;
    return;

state_two:
    if (!(U16_AT(sprite, 0x14) & 0xE000)) {
        return;
    }
    dungeonStatus.unk_0A--;
    S32_AT(actor, 0x1C) &= ~0x208;
    PTR_AT(controller, 0x8C) = D_800D8C64;

    return;
}
