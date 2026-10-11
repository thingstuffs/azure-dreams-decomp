#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct SinkActionWork {
    u8 pad_00[0x8C];
    s32 * handler;
    s32 heightOffset;
    u8 pad_94[0x2];
    union { u16 value; s16 signedValue; } phaseTicks;
    u16 actionFlags;
    u8 pad_9A[0x1];
    u8 phase;
    u8 pad_9C[0x4];
    s32 sinkOffset;
    u8 pad_A4[0xA];
    s16 recoveryTicks;
} SinkActionWork;

extern u8 D_8015BFD0[];
extern u8 D_8015BFB8[];
extern s32 D_80158F68;
void func_800A2B04();
s16 func_800A48F0();
s32 func_800A4ACC();
s32 func_800A56E0();
s32 func_800A6D30();
extern u8 D_8015BFD8[];
extern u8 D_8015BFE0[];

/* Run the actor's eight-step sink animation, advancing its phase and swapping the sprite each step. */
void func_8015BC5C(SinkActionWork *work, EntityRec *motion, Rec_D_80082E80 *sprite, EntityRec *actor) {
    s32 sinkStep;
    u16 flags;
    s32 phase;
    s32 height;
    s32 ticksLeft;

    phase = work->phase;
    work->phaseTicks.value = (u16) (work->phaseTicks.value - 1);
    switch (phase) {
    case 0:
    case 4:
        func_800A56E0(0x51C);
        flags = sprite->unk_14.at00_u16.v;
        if (flags & 0x8000) {
            work->phase = 7;
            return;
        }
        if (!(flags & 0xE000)) {
            return;
        }
        sprite->unk_2C.as_pu8 = D_8015BFD8;
        func_80047784(sprite, D_8015BFD8[((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        work->actionFlags = (u16) (work->actionFlags | 8);
        /* This motion word supplies the sink acceleration. */
        motion->flags14 = 0xFFF00000;
        actor->flags1C = (s32) (actor->flags1C & 0xF7FFFFFF);
        work->sinkOffset = 0;
        work->phaseTicks.value = 10;
        work->phase++;
        return;
    case 1:
    case 5:
        height = work->heightOffset;
        sinkStep = work->sinkOffset;
        ticksLeft = work->phaseTicks.signedValue;
        work->heightOffset = height - sinkStep;
        if (ticksLeft != 0) {
            height = sinkStep;
            sinkStep = motion->flags14;
            work->sinkOffset = (s32) (height + sinkStep);
            motion->flags14 = (s32) (motion->flags14 + 0x30000);
        }
        height = work->heightOffset;
        sinkStep = work->sinkOffset;
        ticksLeft = work->phaseTicks.signedValue;
        work->heightOffset = height + sinkStep;
        if (ticksLeft > 0) {
            return;
        }
        work->heightOffset = 0;
        work->actionFlags = (u16) (work->actionFlags & 0xFFF7);
        actor->flags1C = (s32) (actor->flags1C | 0x8000000);
        work->phase++;
        return;
    case 2:
    case 6:
        work->actionFlags = (u16) (work->actionFlags & 0xFFF7);
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, sprite->unk_24, sprite->unk_25);
        sprite->unk_2C.as_pu8 = D_8015BFE0;
        func_80047784(sprite, D_8015BFE0[((s32)(gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        work->phase++;
        return;
    case 3:
        if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        sprite->unk_2C.as_pu8 = D_8015BFD0;
        func_80047784(sprite, D_8015BFD0[((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        work->phase++;
        return;
    case 7:
        if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        sprite->unk_2C.as_pu8 = D_8015BFB8;
        func_80047784(sprite, D_8015BFB8[((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
        func_800A4ACC(actor);
        actor->unk_6D = 0;
        actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
        work->handler = &D_80158F68;
        work->actionFlags = (u16) (work->actionFlags | 0x8000);
        work->recoveryTicks = (s16) ((func_800A6D30() & 7) + 8);
        func_800A48F0(actor, 0x1A, (s8) work->recoveryTicks);
        return;
    default:
        return;
    }
}
