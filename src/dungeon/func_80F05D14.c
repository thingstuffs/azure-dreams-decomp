#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/actor_action.h"

/* Partial action view: timer loads keep their observed signedness. */


typedef union TilePairView {
    struct { u8 x; u8 y; } tile;
    u16 packed;
} TilePairView;

typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 frame;
    u8 pad_05[3];
    s32 animationKey;
    u8 pad_0C[8];
    u16 flags;
    u8 pad_16[0xE];
    TilePairView position;
    union { s8 signedIndex; u8 unsignedIndex; } tileIndex;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSpriteView;

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

extern s32 D_8014DCE8;
extern u8 D_80150EE0[];

void update_actor_action_state_machine(ActorActionView *action, EntityRec *motion, ActorSpriteView *sprite, ActorRecord *actor)
{
    u8 state;
    ActorRecord *call_actor;
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
        sprite->directionFrames = D_80150EE0;
        select_sprite_entry(sprite,
            D_80150EE0[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->timer.unsignedTicks = 0;
        action->phase++;
        return;
    }

    case 1:
        if ((s16)++action->timer.unsignedTicks == 5) {
            action->timer.unsignedTicks = 0;
            action->phase++;
            sprite->flags |= 0x0800;
            return;
        }
        return;

    case 2:
        if ((s16)++action->timer.unsignedTicks == 6 ||
            (sprite->flags & 0xE000)) {
            action->timer.unsignedTicks = 0;
            action->phase++;
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x804);
            return;
        }
        return;

    case 3:
        if ((s16)++action->timer.unsignedTicks == 5 ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x0800;
        }
        if (action->timer.signedTicks == 12 ||
            (sprite->flags & 0xE000)) {
            action->timer.unsignedTicks = 0;
            action->phase++;
            sprite->flags &= 0xF7FF;
        }
        call_actor = actor;
        if (action->timer.signedTicks == 1 ||
            (sprite->flags & 0xE000)) {
            call_sprite = sprite;
            resolve_attack_damage_and_effects(call_actor, call_sprite, call_actor->facing, 1);
            return;
        }
        return;

    case 4:
        if (sprite->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            action->nextAction.word = &D_8014DCE8;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->action_flags &= 0x7FFF;
        }
    }
}
