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

extern s32 D_80159728;
extern u8 D_8015CE1C[];

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

void advance_actor_action_sequence(void *sequence, void *motion, void *sprite, EntityRec *actor)
{
    u8 state;

    state = ((AnimationSequenceState *)sequence)->phase;
    switch (state) {
    case 0:
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((AnimationSequenceState *)sequence)->phase = 4;
            ((SpriteFrameState *)sprite)->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
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
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            ((SpriteFrameState *)sprite)->frameTable = D_8015CE1C;
            select_sprite_entry(sprite,
                D_8015CE1C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((AnimationSequenceState *)sequence)->timer.unsignedTicks = 0;
            ((AnimationSequenceState *)sequence)->phase++;
            return;
        }
        return;

    case 2:
        if ((s16)++((AnimationSequenceState *)sequence)->timer.unsignedTicks == 9 ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            ((AnimationSequenceState *)sequence)->timer.unsignedTicks = 0;
            ((AnimationSequenceState *)sequence)->phase++;
        }
        if (((AnimationSequenceState *)sequence)->timer.signedTicks == 6) {
            play_sound_if_enabled(0x808);
            return;
        }
        return;

    case 3:
        if ((s16)++((AnimationSequenceState *)sequence)->timer.unsignedTicks == 6) {
            ((SpriteFrameState *)sprite)->flags |= 0x0800;
        }
        if (((AnimationSequenceState *)sequence)->timer.signedTicks == 15 ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            ((AnimationSequenceState *)sequence)->timer.unsignedTicks = 0;
            ((AnimationSequenceState *)sequence)->phase++;
            return;
        }
        return;

    case 4:
        if (((SpriteFrameState *)sprite)->flags & 0xE000) {
            reduce_actor_food_meter(actor, 0x100);
            ((AnimationSequenceState *)sequence)->nextBehavior = &D_80159728;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->unk_46 &= 0x7FFF;
        }
    default:
        return;
    }
}
