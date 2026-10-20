#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

/* The action record shares its timer bytes between signed tests and unsigned updates. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    void *nextBehavior;
    s32 scratch;
    u8 pad_94[2];
    union { u16 raw; s16 signedValue; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[2];
    s16 idleElapsed;
    s16 idleDelay;
    u8 pad_A2[0xA];
    union { u16 raw; s16 signedValue; } startHeight;
} ActorActionView;

/* Sprite state passed to the frame selector; the tile pair is also compared as one halfword. */
typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 framePhase;
    u8 pad_05[0xF];
    u16 flags;
    u8 pad_16[6];
    u16 scaleX;
    u16 scaleY;
    u8 pad_20[4];
    union { struct { u8 x, y; } bytes; u16 packed; } tile;
    union { u8 raw; s8 signedValue; } room;
    u8 pad_27[5];
    u8 *frameTable;
} ActorSpriteView;

extern void select_sprite_entry();
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern s32 advance_status_timers(void *);
extern s32 play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);

extern void update_actor_dungeon_behavior(void *, void *, void *, void *);
extern u8 D_8016EEE0[];

/* Advance a timed sprite flashing sequence and clean up the actor when it finishes. */
void advance_flashing_sprite_sequence(ActorActionView *action, EntityRec *motion, ActorSpriteView *sprite, EntityRec *actor)
{
    u8 state;
    EntityRec *call_actor;
    void *call_sprite;

    state = action->phase;
    switch (state) {
    default:
        return;

    case 0:
    {
        call_actor = actor;
        if (sprite->flags & 0x8000) {
            action->phase = 4;
            call_sprite = sprite;
            ((ActorSpriteView *)call_sprite)->flags |= 0x6000;
            resolve_attack_damage_and_effects(call_actor, call_sprite, call_actor->facing, 1);
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        (sprite->frameTable) = D_8016EEE0;
        select_sprite_entry(sprite,
            D_8016EEE0[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->timer.raw = 0;
        action->phase++;
        return;
    }

    case 1:
        if ((s16)++action->timer.raw == 5) {
            action->timer.raw = 0;
            action->phase++;
            sprite->flags |= 0x0800;
            return;
        }
        return;

    case 2:
        if ((s16)++action->timer.raw == 6 ||
            (sprite->flags & 0xE000)) {
            action->timer.raw = 0;
            action->phase++;
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x804);
            return;
        }
        return;

    case 3:
        if ((s16)++action->timer.raw == 5 ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x0800;
        }
        if (action->timer.signedValue == 12 ||
            (sprite->flags & 0xE000)) {
            action->timer.raw = 0;
            action->phase++;
            sprite->flags &= 0xF7FF;
        }
        call_actor = actor;
        if (action->timer.signedValue == 1 ||
            (sprite->flags & 0xE000)) {
            call_sprite = sprite;
            resolve_attack_damage_and_effects(call_actor, call_sprite, call_actor->facing, 1);
            return;
        }
        return;

    case 4:
        if (sprite->flags & 0xE000) {
            reduce_actor_food_meter(actor, 0x100);
            action->nextBehavior = &update_actor_dungeon_behavior;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->unk_46 &= 0x7FFF;
        }
    }
}
