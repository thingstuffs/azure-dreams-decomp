#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80172830_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172830_0;   /* arg0 in func_80172830 */





extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern void *D_800E3DE8[];
extern u8 D_80170E7C;
extern u8 D_80174C34[];
extern u8 D_80174C64[];
extern u8 D_80174C6C[];

/* Updates an actor's staged movement, animation, and return to its tile. */
void func_80172830(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 state;
    s32 direction_offset;
    s32 vertical_speed;
    u16 ticks_left;

    state = ((S_80172830_0 *)action)->unk_9B;
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
    if (state == 3) {
        goto state_3;
    }
    return;

state_0:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172830_0 *)action)->unk_9B = 3;
        ((S_80172830_0 *)action)->unk_96 = 0;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
        return;
    }

    direction_offset = (((((u16)actor->facing) >> 9) & 7) + 4) % 8;
    motion->unk_0C =
        dirStepX[direction_offset] * 3 << 16;
    motion->unk_10 =
        dirStepY[direction_offset] * 3 << 16;
    motion->flags14 = 0;
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174C34;
    func_80047784(sprite,
        D_80174C34[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
    {
        s32 next_state;

        next_state = ((S_80172830_0 *)action)->unk_9B;
        ((S_80172830_0 *)action)->unk_96 = 0;
        next_state++;
        ((S_80172830_0 *)action)->unk_9B = next_state;
        return;
    }

state_1:
    motion->unk_0C -= motion->unk_0C >> 2;
    motion->unk_10 -= motion->unk_10 >> 2;
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174C64;
    func_80047784(sprite,
        D_80174C64[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
    {
        s32 next_state;

        next_state = ((S_80172830_0 *)action)->unk_9B;
        ((S_80172830_0 *)action)->unk_96 = 4;
        next_state++;
        ((S_80172830_0 *)action)->unk_9B = next_state;
        return;
    }

state_2:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    func_800A56E0(0x808);
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174C6C;
    func_80047784(sprite,
        D_80174C6C[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
    ((S_80172830_0 *)action)->unk_96 = 0x14;
    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    {
        s32 next_state;

        next_state = ((S_80172830_0 *)action)->unk_9B;
        next_state++;
        ((S_80172830_0 *)action)->unk_9B = next_state;
        return;
    }

state_3:
    ticks_left = ((S_80172830_0 *)action)->unk_96;
    vertical_speed = motion->flags14;
    ticks_left--;
    ((S_80172830_0 *)action)->unk_96 = ticks_left;
    if ((s16)ticks_left < 12) {
        vertical_speed += 0x1400;
    } else {
        vertical_speed += 0x20000;
    }
    motion->flags14 = vertical_speed;
    ((S_80172830_0 *)action)->unk_90 += vertical_speed;

    if ((s16)((S_80172830_0 *)action)->unk_96 == 0x11) {
        s32 direction_step;
        s16 *x_steps;
        s16 *x_step;
        s16 *y_step;

        direction_offset = ((u16)actor->facing) >> 8;
        x_steps = dirStepX;
        x_step = (s16 *)((u8 *)x_steps + (direction_offset & 0xE));
        direction_step = *x_step;
        motion->unk_0C =
            (direction_step * 3 << 16) + ((direction_step * 3 << 16) >> 2);
        y_step = (s16 *)((u8 *)&dirStepY + (direction_offset & 0xE));
        direction_step = *y_step;
        motion->flags14 = 0xFFF70000;
        motion->unk_10 =
            (direction_step * 3 << 16) + ((direction_step * 3 << 16) >> 2);
        ((S_80172830_0 *)action)->unk_90 = 0;
        ((S_80172830_0 *)action)->unk_98 |= 8;
    }

    if (((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 3) &&
         (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(actor, sprite, actor->facing, 1);
    }

    if (((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 5) &&
         (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        motion->unk_0C =
            ((((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 16) -
             motion->x.v) / (s16)((S_80172830_0 *)action)->unk_96;
        motion->unk_10 =
            ((((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 16) -
             motion->y.v) / (s16)((S_80172830_0 *)action)->unk_96;
    }

    if (((s16)((S_80172830_0 *)action)->unk_96 > 0) &&
        !(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        return;
    }
    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 0x100);
    (*(u8 * *)((u8 *)action + 0x8C)) = &D_80170E7C;
    dungeonStatus.unk_0C = 0;
    (*(u16 *)((u8 *)action + 0x98)) &= 0xFFF7;
    func_800A4ACC(actor);
    if (actor->unk_6D == 0) {
        actor->unk_46 &= 0x7FFF;
        return;
    }
    D_800E3DE8[0] = (u8 *)actor - 0x20;

    return;
}
