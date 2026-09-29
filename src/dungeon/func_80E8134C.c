#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80154B4C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_80154B4C_0;   /* arg0 in func_80154B4C */






extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_801536F4[];
extern u8 D_80157554[];
extern u8 D_80157574[];
extern u8 D_8015757C[];

/* Updates actor movement and animation states and completes the timed action. */
void func_80154B4C(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 state;
    s32 move_frames;
    s32 target_x;
    s32 world_x;
    s32 height;
    s32 height_offset;
    s32 world_y;
    s32 move_count;
    s32 action_timer;
    s32 actor_flags;
    s32 facing_aux;
    DungeonGlobalStatus *dungeon_state;
    u8 *idle_anims;

    state = ((S_80154B4C_0 *)action)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto decrement_timer;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto decrement_timer;

state_zero:
{
    u8 *state_anims;

    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
        goto decrement_timer;
    }
    state_anims = D_80157574;
    (*(u8 * *)((u8 *)sprite + 0x2C)) = state_anims;
    func_80047784(sprite,
        state_anims[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
    ((Rec_D_80082E80 *)sprite)->unk_1C.at02_s16.v = 0x1000;
    ((S_80154B4C_0 *)action)->unk_98 |= 8;
    actor->flags1C &= 0xF7FFFFFF;
    ((S_80154B4C_0 *)action)->unk_9E.s = 5;
    ((S_80154B4C_0 *)action)->unk_A4 = 0;
    ((S_80154B4C_0 *)action)->unk_9B++;
}

state_one:
    move_frames = ((S_80154B4C_0 *)action)->unk_9E.s;
    ((S_80154B4C_0 *)action)->unk_90 -= ((S_80154B4C_0 *)action)->unk_A4;
    if (move_frames != 0) {
        target_x = ((Rec_D_80082E80 *)sprite)->unk_24;
        world_x = motion->x.w.i;
        target_x <<= 6;
        world_x -= 0x20;
        motion->unk_0C = ((target_x - world_x) << 16) / move_frames;

        world_y = motion->y.w.i;
        world_y -= 0x20;
        motion->unk_10 =
            (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - world_y) << 16) /
            ((S_80154B4C_0 *)action)->unk_9E.s;

        ((S_80154B4C_0 *)action)->unk_A4 =
            (-func_800644B8(((S_80154B4C_0 *)action)->unk_9E.s * 0x199)) << 10;
    }

    height = ((S_80154B4C_0 *)action)->unk_90;
    height_offset = ((S_80154B4C_0 *)action)->unk_A4;
    move_count = ((S_80154B4C_0 *)action)->unk_9E.u;
    height += height_offset;
    move_count -= 1;
    ((S_80154B4C_0 *)action)->unk_9E.u = move_count;
    ((S_80154B4C_0 *)action)->unk_90 = height;
    if ((move_count << 16) >= 0) {
        goto state_two;
    }

    ((S_80154B4C_0 *)action)->unk_90 = 0;
    ((S_80154B4C_0 *)action)->unk_98 &= 0xFFF7;
    actor->flags1C |= 0x08000000;
    ((S_80154B4C_0 *)action)->unk_9B++;

state_two:
{
    u8 *state_anims;

    if (actor->flags1C & 0x08000000) {
        ((S_80154B4C_0 *)action)->unk_98 &= 0xFFF7;
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        state_anims = D_8015757C;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = state_anims;
        func_80047784(sprite,
            state_anims[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_D_80082E80 *)sprite)->unk_1C.at02_s16.v = 0xC00;
        ((S_80154B4C_0 *)action)->unk_9B++;
        goto decrement_timer;
    }
    goto decrement_timer;
}

state_three:
    idle_anims = D_80157554;
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != idle_anims) {
        (*(u8 * *)((u8 *)sprite + 0x2C)) = idle_anims;
        func_80047784(sprite,
            idle_anims[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_D_80082E80 *)sprite)->unk_1C.at02_s16.v = 0x1000;
    }

decrement_timer:
    action_timer = ((S_80154B4C_0 *)action)->unk_96 - 1;
    ((S_80154B4C_0 *)action)->unk_96 = action_timer;
    if ((action_timer << 16) > 0) {
        return;
    }

    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    ((Rec_D_80082E80 *)sprite)->unk_1C.at02_s16.v = 0x1000;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 3);
    func_800A4ACC(actor);

    dungeon_state = &dungeonStatus;
    if (dungeon_state->unk_08 != 0) {
        (*(u16 *)&dungeon_state->unk_08)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->unk_46 & 0x8000) {
            actor->unk_46 &= 0x7FFF;
        }
        goto collision_check;
    }
    if (actor_flags & 0x410) {
        goto collision_check;
    }
    if (!(actor_flags & 0x20000)) {
        goto collision_check;
    }
    actor->facing = func_800A0818(
        ((Rec_D_80082E80 *)sprite)->unk_24,
        ((Rec_D_80082E80 *)sprite)->unk_25,
        D_80082E80.tileX,
        D_80082E80.tileY,
        &facing_aux);

collision_check:
    if ((func_800AD9B4(sprite, actor) << 16) > 0) {
        ((S_80154B4C_0 *)action)->unk_8C = D_801536F4;
        func_800A9A04(actor);
    }
}
