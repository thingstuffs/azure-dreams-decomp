#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

extern u8 D_801716F4[];
extern u8 D_80175584[];

typedef struct S_80172F94_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172F94_0;   /* arg0 in advance_timed_actor_animation */

typedef struct S_80172F94_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172F94_3;   /* arg1 in advance_timed_actor_animation */

/* Advances an actor's timed animation sequence and handles its completion. */
void advance_timed_actor_animation(void *action, void *motion, void *sprite, ActorRecord *actor)
{
    u8 state;

    state = ((S_80172F94_0 *)action)->unk_9B;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((S_80172F94_0 *)action)->unk_9B = 4;
            ((SpriteFrameState *)sprite)->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        ((S_80172F94_3 *)motion)->unk_14 = 0;
        ((S_80172F94_3 *)motion)->unk_10 = 0;
        ((S_80172F94_3 *)motion)->unk_0C = 0;
        ((S_80172F94_0 *)action)->unk_96.u = 0;
        ((S_80172F94_0 *)action)->unk_9B++;
        return;

    case 1:
        if ((s16)++((S_80172F94_0 *)action)->unk_96.u == 4 ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            ((SpriteFrameState *)sprite)->frameTable = D_80175584;
            select_sprite_entry(sprite,
                D_80175584[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((SpriteFrameState *)sprite)->flags |= 0x0800;
        }
        if (((S_80172F94_0 *)action)->unk_96.s == 7 ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            ((S_80172F94_0 *)action)->unk_96.u = 0;
            ((S_80172F94_0 *)action)->unk_9B++;
            return;
        }
        return;

    case 2:
        ((S_80172F94_0 *)action)->unk_96.u = 0;
        ((S_80172F94_0 *)action)->unk_9B++;

    case 3:
        if ((s16)++((S_80172F94_0 *)action)->unk_96.u == 7 ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        }

        if (((S_80172F94_0 *)action)->unk_96.s == 3) {
            play_sound_if_enabled(0x814);
        }
    case 4:
        if (((SpriteFrameState *)sprite)->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            ((S_80172F94_0 *)action)->unk_8C = D_801716F4;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->action_flags &= 0x7FFF;
        }
        return;
    }
}
