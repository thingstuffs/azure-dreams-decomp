#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern void func_80047784(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);

extern s32 D_80171728;
extern u8 D_80174E1C[];


typedef struct S_80172FD8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172FD8_0;   /* arg0 in advance_timed_animation_and_cleanup */


typedef struct S_80172FD8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172FD8_3;   /* arg1 in advance_timed_animation_and_cleanup */

/* Advances an actor's timed animation sequence and performs its final cleanup. */
void advance_timed_animation_and_cleanup(void *sequence, void *motion, void *sprite, EntityRec *actor)
{
    u8 state;

    state = ((S_80172FD8_0 *)sequence)->unk_9B;
    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80172FD8_0 *)sequence)->unk_9B = 4;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        ((S_80172FD8_3 *)motion)->unk_14 = 0;
        ((S_80172FD8_3 *)motion)->unk_10 = 0;
        ((S_80172FD8_3 *)motion)->unk_0C = 0;
        ((S_80172FD8_0 *)sequence)->unk_96.u = 0;
        ((S_80172FD8_0 *)sequence)->unk_9B++;
        return;

    case 1:
        if ((s16)++((S_80172FD8_0 *)sequence)->unk_96.u == 4 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            (*(u8 **)((u8 *)sprite + 0x2C)) = D_80174E1C;
            func_80047784(sprite,
                D_80174E1C[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172FD8_0 *)sequence)->unk_96.u = 0;
            ((S_80172FD8_0 *)sequence)->unk_9B++;
            return;
        }
        return;

    case 2:
        if ((s16)++((S_80172FD8_0 *)sequence)->unk_96.u == 9 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            ((S_80172FD8_0 *)sequence)->unk_96.u = 0;
            ((S_80172FD8_0 *)sequence)->unk_9B++;
        }
        if (((S_80172FD8_0 *)sequence)->unk_96.s == 6) {
            play_sound_if_enabled(0x808);
            return;
        }
        return;

    case 3:
        if ((s16)++((S_80172FD8_0 *)sequence)->unk_96.u == 6) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x0800;
        }
        if (((S_80172FD8_0 *)sequence)->unk_96.s == 15 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            ((S_80172FD8_0 *)sequence)->unk_96.u = 0;
            ((S_80172FD8_0 *)sequence)->unk_9B++;
            return;
        }
        return;

    case 4:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            reduce_actor_food_meter(actor, 0x100);
            ((S_80172FD8_0 *)sequence)->unk_8C = &D_80171728;
            g_dungeon_status.unk_0C = 0;
            advance_status_timers(actor);
            actor->unk_46 &= 0x7FFF;
        }
    default:
        return;
    }
}
