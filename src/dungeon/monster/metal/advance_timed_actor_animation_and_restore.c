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
extern void reduce_actor_food_meter(void *, s32);

extern u8 D_80171650[];
extern u8 D_801742F0[];

typedef struct S_80172E04_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172E04_0;   /* arg0 in advance_timed_actor_animation_and_restore */

typedef struct S_80172E04_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172E04_3;   /* arg1 in advance_timed_actor_animation_and_restore */

/* Advance the timed actor animation sequence and restore actor state on completion. */
void advance_timed_actor_animation_and_restore(void *action, void *motion, void *sprite, EntityRec *actor)
{
    u8 state;

    state = ((S_80172E04_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((S_80172E04_0 *)action)->unk_9B = 4;
            ((SpriteFrameState *)sprite)->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        ((S_80172E04_3 *)motion)->unk_14 = 0;
        ((S_80172E04_3 *)motion)->unk_10 = 0;
        ((S_80172E04_3 *)motion)->unk_0C = 0;
        ((S_80172E04_0 *)action)->unk_96.u = 0;
        ((S_80172E04_0 *)action)->unk_9B++;
        return;

    case 1:
        if ((s16)++((S_80172E04_0 *)action)->unk_96.u == 4 ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            ((SpriteFrameState *)sprite)->frameTable = D_801742F0;
            select_sprite_entry(sprite,
                D_801742F0[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((SpriteFrameState *)sprite)->flags |= 0x0800;
        }
        if (((S_80172E04_0 *)action)->unk_96.s == 7 ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            ((S_80172E04_0 *)action)->unk_96.u = 0;
            ((S_80172E04_0 *)action)->unk_9B++;
            return;
        }
        return;

    case 2:
        if ((s16)++((S_80172E04_0 *)action)->unk_96.u == 2) {
            ((SpriteFrameState *)sprite)->flags |= 0x0800;
        }
        if (((S_80172E04_0 *)action)->unk_96.s == 8 ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            play_sound_if_enabled(0x808);
            ((S_80172E04_0 *)action)->unk_96.u = 0;
            ((S_80172E04_0 *)action)->unk_9B++;
            return;
        }
        return;

    case 3:
        if ((s16)++((S_80172E04_0 *)action)->unk_96.u == 2) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            ((S_80172E04_0 *)action)->unk_9B++;
        }

    case 4:
        if (((SpriteFrameState *)sprite)->flags & 0xE000) {
            reduce_actor_food_meter(actor, 0x100);
            ((S_80172E04_0 *)action)->unk_8C = D_80171650;
            g_dungeon_status.unk_0C = 0;
            advance_status_timers(actor);
            actor->unk_46 &= 0x7FFF;
        }
    }
}
