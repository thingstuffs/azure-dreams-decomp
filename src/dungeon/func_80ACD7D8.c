#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s32 D_8016B728;
extern u8 D_8016EE1C[];

typedef struct AnimationSequenceState {
    u8 pad_00[0x8C];
    s32 * nextBehavior;
    u8 pad_90[0x6];
    union { u16 unsignedTicks; s16 signedTicks; } timer;
    u8 pad_98[0x3];
    u8 phase;
} AnimationSequenceState;

typedef struct MotionResetView {
    u8 pad_00[0xC];
    s32 velocityX;
    s32 velocityY;
    s32 motionFlags;
} MotionResetView;

void func_8016CFD8(void *sequence, void *motion, void *sprite, EntityRec *actor)
{
    u8 state;

    state = ((AnimationSequenceState *)sequence)->phase;
    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((AnimationSequenceState *)sequence)->phase = 4;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(actor, sprite, actor->facing, 1);
            return;
        }
        ((MotionResetView *)motion)->motionFlags = 0;
        ((MotionResetView *)motion)->velocityY = 0;
        ((MotionResetView *)motion)->velocityX = 0;
        ((AnimationSequenceState *)sequence)->timer.unsignedTicks = 0;
        ((AnimationSequenceState *)sequence)->phase++;
        return;

    case 1:
        if ((s16)++((AnimationSequenceState *)sequence)->timer.unsignedTicks == 4 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 = D_8016EE1C;
            func_80047784(sprite,
                D_8016EE1C[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((AnimationSequenceState *)sequence)->timer.unsignedTicks = 0;
            ((AnimationSequenceState *)sequence)->phase++;
            return;
        }
        return;

    case 2:
        if ((s16)++((AnimationSequenceState *)sequence)->timer.unsignedTicks == 9 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            func_8009C12C(actor, sprite, actor->facing, 1);
            ((AnimationSequenceState *)sequence)->timer.unsignedTicks = 0;
            ((AnimationSequenceState *)sequence)->phase++;
        }
        if (((AnimationSequenceState *)sequence)->timer.signedTicks == 6) {
            func_800A56E0(0x808);
            return;
        }
        return;

    case 3:
        if ((s16)++((AnimationSequenceState *)sequence)->timer.unsignedTicks == 6) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x0800;
        }
        if (((AnimationSequenceState *)sequence)->timer.signedTicks == 15 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            ((AnimationSequenceState *)sequence)->timer.unsignedTicks = 0;
            ((AnimationSequenceState *)sequence)->phase++;
            return;
        }
        return;

    case 4:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            func_800AD594(actor, 0x100);
            ((AnimationSequenceState *)sequence)->nextBehavior = &D_8016B728;
            dungeonStatus.unk_0C = 0;
            func_800A4ACC(actor);
            actor->unk_46 &= 0x7FFF;
        }
    default:
        return;
    }
}
