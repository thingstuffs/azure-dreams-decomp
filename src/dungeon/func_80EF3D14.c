#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

/* Partial action view: timer loads keep their observed signedness. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    union { s32 code; void *record; u8 *frames; s32 *word; } nextAction;
    Fixed1616 motionOffset;
    u8 pad_94[2];
    union { u16 unsignedTicks; s16 signedTicks; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[4];
    s16 frameParameter;
    u8 pad_A2[4];
    u16 effectTicks;
    union { s16 signedPhase; u16 phase; u16 startX; } effectState;
    union { u16 facing; u16 startY; } saved;
    u16 effectX;
    u16 effectY;
    u16 effectZ;
} ActorActionView;

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

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s32 D_8015FCE8;
extern u8 D_80162EE0[];

void func_80161514(ActorActionView *action, EntityRec *motion, ActorSpriteView *sprite, EntityRec *actor)
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
            func_8009C12C(call_actor, call_sprite, call_actor->facing, 1);
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        sprite->directionFrames = D_80162EE0;
        func_80047784(sprite,
            D_80162EE0[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
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
            func_800A56E0(0x804);
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
            func_8009C12C(call_actor, call_sprite, call_actor->facing, 1);
            return;
        }
        return;

    case 4:
        if (sprite->flags & 0xE000) {
            func_800AD594(actor, 0x100);
            action->nextAction.word = &D_8015FCE8;
            dungeonStatus.unk_0C = 0;
            func_800A4ACC(actor);
            actor->unk_46 &= 0x7FFF;
        }
    }
}
