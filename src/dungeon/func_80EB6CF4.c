#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801724F4_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801724F4_1;   /* arg0 in update_directional_movement_and_settle */


extern void func_80047784(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);

extern void *D_800E3DE8;
extern s32 D_801711A4;
extern u8 D_8017419C[];
extern u8 D_801741A4[];

/* Updates directional movement and animation, then settles the actor on its destination tile. */
void update_directional_movement_and_settle(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 dir_x;
    s32 dir_y;
    s32 dir_offset;
    s32 ticks_left;
    s32 state;

    dir_offset = ((u16)((u16)actor->facing) >> 8) & 0xE;
    dir_x = *(s16 *)((u8 *)((s8 *)dir_step_x) + dir_offset);
    dir_y = *(s16 *)((u8 *)((s8 *)dir_step_y) + dir_offset);
    state = ((S_801724F4_1 *)action)->unk_9B;
    ticks_left = ((S_801724F4_1 *)action)->unk_96 - 1;
    ((S_801724F4_1 *)action)->unk_96 = ticks_left;

    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_801724F4_1 *)action)->unk_9B = 0xFF;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_8017419C;
        func_80047784(sprite,
            D_8017419C[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_801724F4_1 *)action)->unk_9B++;
        return;
    case 1:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_801741A4;
            func_80047784(sprite,
                D_801741A4[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            motion->unk_0C = (dir_x << 18) + (dir_x << 17);
            motion->unk_10 = (dir_y << 18) + (dir_y << 17);
            ((S_801724F4_1 *)action)->unk_96 = 8;
            play_sound_if_enabled(0x607);
            ((S_801724F4_1 *)action)->unk_9B++;
        }
        return;
    case 2:
        if ((ticks_left << 16) <= 0) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            ((S_801724F4_1 *)action)->unk_9B = 0xFF;
        }
        return;
    case 0xFF:
    {
        s32 target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
        s32 current_x = motion->x.w.i - 0x20;
        motion->unk_0C = ((target_x - current_x) << 0xF) >> 1;
    }
        {
            s32 target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
            s32 current_y = motion->y.w.i - 0x20;
            motion->unk_10 = ((target_y - current_y) << 0xF) >> 1;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            (*(u32 *)&actor->flags1C) |= 0x40000;
            set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            reduce_actor_food_meter(actor, 0x100);
            ((S_801724F4_1 *)action)->unk_8C = &D_801711A4;
            g_dungeon_status.unk_0C = 0;
            advance_status_timers(actor);
            if (actor->unk_6D == 0) {
                actor->unk_46 &= 0x7FFF;
            } else {
                D_800E3DE8 = (u8 *)actor - 0x20;
            }
        }
    }
}
