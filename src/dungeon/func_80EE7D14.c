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

extern void func_80047784();
extern void dungeonResolveAttackDamageAndEffects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern s32 dungeonAdvanceStatusTimers(void *);
extern s32 func_800A56E0(s32);
extern void dungeonReduceActorFoodMeter(void *, s32);

extern void func_8016BCE8(void *, void *, void *, void *);
extern u8 D_8016EEE0[];

/* Advance a timed sprite flashing sequence and clean up the actor when it finishes. */
void dungeonAdvanceFlashingSpriteSequence(ActorActionView *action, EntityRec *motion, ActorSpriteView *sprite, EntityRec *actor)
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
            dungeonResolveAttackDamageAndEffects(call_actor, call_sprite, call_actor->facing, 1);
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        (sprite->frameTable) = D_8016EEE0;
        func_80047784(sprite,
            D_8016EEE0[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
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
            func_800A56E0(0x804);
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
            dungeonResolveAttackDamageAndEffects(call_actor, call_sprite, call_actor->facing, 1);
            return;
        }
        return;

    case 4:
        if (sprite->flags & 0xE000) {
            dungeonReduceActorFoodMeter(actor, 0x100);
            action->nextBehavior = &func_8016BCE8;
            dungeonStatus.unk_0C = 0;
            dungeonAdvanceStatusTimers(actor);
            actor->unk_46 &= 0x7FFF;
        }
    }
}
