#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_80047784();
extern void func_8009C12C();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern void func_800AD594();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228[];
extern s32 D_8008346C[];
extern void *D_800E3DE8[];
extern u8 D_80170E54;
extern u8 D_80174140;
extern u8 D_80174170;


typedef struct S_8017284C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_8017284C_0;   /* arg0 in func_8017284C */




/* Updates staged movement and animation, then places the actor on its destination tile. */
void func_8017284C(S_8017284C_0 *action, Rec_D_800E3D7C *motion, Rec_D_80082E80 *sprite, void *actor)
{
    s16 timer;
    s32 direction_y;
    s32 direction;
    s32 wrap_base;
    s32 x_velocity;
    s32 y_velocity;
    s32 z_velocity;
    s32 speed_component;
    s32 facing;
    s32 state;
    register u8 next_state ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    state = action->unk_9B;
    if (state == 1) {
        goto state1;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state0;
        }
        goto done;
    }
    if (state == 2) {
        goto state2;
    }
    if (state == 3) {
        goto state3;
    }
    goto done;

state0:
    if (sprite->unk_14.at00_u16.v & 0x8000) {
        action->unk_9B = 3;
        action->unk_96.s = 0;
        sprite->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
        goto done;
    }

    facing = ((u16)((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 9) & 7;
    direction = facing + 4;
    wrap_base = direction;
    if (direction < 0) {
        wrap_base = facing + 11;
    }
    direction -= wrap_base & 0x18;
    motion->unk_0C.as_s32 =
        (*(s16 *)((u8 *)(&D_8006CCD8) + (direction * 2))) * 0x60000;
    direction_y = (*(s16 *)((u8 *)(&D_8006CCE8) + (direction * 2)));
    motion->unk_14.as_s32 = 0;
    motion->unk_10.at00_s32.v = direction_y * 0x60000;
    sprite->unk_2C.as_pv = &D_80174140;
    func_80047784(sprite,
        (*(u8 *)((u8 *)(&D_80174140) + (((D_80083228[0] + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7))),
        0);
    next_state = action->unk_9B;
    action->unk_96.s = 0;
    goto increment_state;

state1:
    x_velocity = motion->unk_0C.as_s32;
    y_velocity = motion->unk_10.at00_s32.v;
    motion->unk_0C.as_s32 = x_velocity - (x_velocity >> 2);
    motion->unk_10.at00_s32.v = y_velocity - (y_velocity >> 2);
    if (sprite->unk_14.at00_u16.v & 0xE000) {
        sprite->unk_2C.as_pv = &D_80174170;
        func_80047784(sprite,
            (*(u8 *)((u8 *)(&D_80174170) + (((D_80083228[0] + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7))),
            0);
        next_state = action->unk_9B;
        action->unk_96.s = 0x14;
        goto increment_state;
    }
    goto done;

state2:
    timer = action->unk_96.u - 1;
    z_velocity = motion->unk_14.as_s32;
    action->unk_96.s = timer;
    if (timer < 12) {
        z_velocity += 0x1400;
    } else {
        z_velocity += 0x20000;
    }
    motion->unk_14.as_s32 = z_velocity;
    action->unk_90 += z_velocity;

    if (action->unk_96.s == 0x11) {
        func_800A56E0(0x808);
        direction = ((u16)((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 >> 9) & 7;
        speed_component = (*(s16 *)((u8 *)(&D_8006CCD8) + (direction * 2))) * 0x30000;
        motion->unk_0C.as_s32 = speed_component + (speed_component >> 2);
        speed_component = (*(s16 *)((u8 *)(&D_8006CCE8) + (direction * 2))) * 0x30000;
        motion->unk_10.at00_s32.v = speed_component + (speed_component >> 2);
    }

    if (((sprite->unk_04.as_s8 == 3) &&
         (sprite->unk_14.at00_u16.v & 0x1000)) ||
        (sprite->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
    }

    if (((sprite->unk_04.as_s8 == 5) &&
         (sprite->unk_14.at00_u16.v & 0x1000)) ||
        (sprite->unk_14.at00_u16.v & 0x8000)) {
        motion->unk_0C.as_s32 =
            ((((sprite->unk_24 << 6) + 0x20) << 16) -
             motion->unk_00.at00_s32.v) / action->unk_96.s;
        motion->unk_10.at00_s32.v =
            ((((sprite->unk_25 << 6) + 0x20) << 16) -
             motion->unk_04.at00_s32.v) / action->unk_96.s;
    }

    if ((action->unk_96.s <= 0) ||
        (sprite->unk_14.at00_u16.v & 0x8000)) {
        next_state = action->unk_9B;
        goto increment_state;
    }
    goto done;

increment_state:
    next_state++;
    action->unk_9B = next_state;
    goto done;

state3:
    if ((action->unk_96.s <= 0) ||
        (sprite->unk_14.at00_u16.v & 0x8000)) {
        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800A2B04(motion, sprite->unk_24, sprite->unk_25);
        func_800AD594(actor, 0x100);
        action->unk_8C = &D_80170E54;
        D_8008346C[0] = 0;
        action->unk_98 &= 0xFFF7;
        func_800A4ACC(actor);
        if (((Rec_D_800E3D7C *)actor)->unk_6D.as_s8 == 0) {
            ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
            goto done;
        }
        D_800E3DE8[0] = (u8 *)actor - 0x20;
    }
    goto done;

done:
    return;
}
