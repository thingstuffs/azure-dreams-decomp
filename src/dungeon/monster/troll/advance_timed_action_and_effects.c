#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801623C4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
} S_801623C4_0;   /* arg0 in advance_timed_action_and_effects */

typedef struct S_801623C4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801623C4_1;   /* arg1 in advance_timed_action_and_effects */

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);
extern void func_8015F21C(void *, void *, void *, void *);
extern void func_8015F4FC(void *, void *, void *, void *);

extern u8 D_801604BC[];
extern u8 D_80163DDC[8];
extern u8 D_80163DE4[8];
extern u8 D_80163DEC[8];

/* Advance the actor's timed action sequence and update its animation and effects. */
void advance_timed_action_and_effects(void *action, void *motion, void *animation, EntityRec *actor)
{
    s16 timer;
    u8 state;

    state = ((S_801623C4_0 *)action)->unk_9B;
    switch (state) {

    case 0:
        ((S_801623C4_1 *)motion)->unk_14 = 0;
        ((S_801623C4_1 *)motion)->unk_10 = 0;
        ((S_801623C4_1 *)motion)->unk_0C = 0;
        ((S_801623C4_0 *)action)->unk_96.s = 0;
        ((S_801623C4_0 *)action)->unk_9B++;
        if (!(((SpriteFrameState *)animation)->flags & 0x8000)) {
            return;
        }

    case 1:
        timer = ((S_801623C4_0 *)action)->unk_96.s + 1;
        ((S_801623C4_0 *)action)->unk_96.s = timer;
        if ((timer != 4) && !(((SpriteFrameState *)animation)->flags & 0x8000)) {
            return;
        }
        ((S_801623C4_0 *)action)->unk_96.s = 0;
        ((S_801623C4_0 *)action)->unk_9B++;
        switch (actor->unk_48) {
        case 13:
            ((SpriteFrameState *)animation)->frameTable = D_80163DDC;
            select_sprite_entry(animation,
                D_80163DDC[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 14:
            ((SpriteFrameState *)animation)->frameTable = D_80163DE4;
            select_sprite_entry(animation,
                D_80163DE4[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 15:
            ((SpriteFrameState *)animation)->frameTable = D_80163DEC;
            select_sprite_entry(animation,
                D_80163DEC[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_801623C4_0 *)action)->unk_9B = 5;
            play_sound_if_enabled(0x60C);
            return;
        default:
            return;
        }

    case 2:
        timer = ((S_801623C4_0 *)action)->unk_96.s + 1;
        ((S_801623C4_0 *)action)->unk_96.s = timer;
        if ((timer == 5) || (((SpriteFrameState *)animation)->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            ((S_801623C4_0 *)action)->unk_96.s = 0;
            ((S_801623C4_0 *)action)->unk_9B++;
        }
        if (((S_801623C4_0 *)action)->unk_96.u == 3) {
            play_sound_if_enabled(0x804);
            return;
        }
        return;

    case 3:
        if (((SpriteFrameState *)animation)->flags & 0xE000) {
            reduce_actor_food_meter(actor, 0x100);
            ((S_801623C4_0 *)action)->unk_8C = D_801604BC;
            g_dungeon_status.unk_0C = 0;
            advance_status_timers(actor);
            actor->unk_46 &= 0x7FFF;
        }
        return;

    case 5:
        timer = ((S_801623C4_0 *)action)->unk_96.s + 1;
        ((S_801623C4_0 *)action)->unk_96.s = timer;
        if ((timer == 10) || (((SpriteFrameState *)animation)->flags & 0x8000)) {
            ((SpriteFrameState *)animation)->flags |= 0x0800;
            play_sound_if_enabled(0x804);
            func_8015F21C(action, motion, animation, actor);
            func_8015F4FC(action, motion, animation, actor);
        }
        if ((((S_801623C4_0 *)action)->unk_96.u == 12) ||
            (((SpriteFrameState *)animation)->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, animation, actor->facing,
                ((S_801623C4_0 *)action)->unk_AA);
        }
        if ((((S_801623C4_0 *)action)->unk_96.u != 20) &&
            !(((SpriteFrameState *)animation)->flags & 0x8000)) {
            break;
        }
        ((SpriteFrameState *)animation)->flags &= 0xF7FF;
        ((S_801623C4_0 *)action)->unk_96.s = 0;
        ((S_801623C4_0 *)action)->unk_9B = 3;

    case 4:
    default:
        break;
    }
}
