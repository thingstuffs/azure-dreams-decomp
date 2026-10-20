#include "common.h"
#include "shared/sprite_frame_state.h"
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

extern u8 D_8014FFD0[];
extern u8 D_8014FFB8[];
extern s32 D_8014CF68;
#include "dungeon/player/object/set_record_integer_tile_center_api.h"
struct Owner_800A48F0; s16 set_or_clear_actor_status_slot(struct Owner_800A48F0 *, s8, s8);
#include "dungeon/actor/state/advance_status_timers_api.h"
s32 play_sound_if_enabled();
s32 generate_random_value();
extern u8 D_8014FFD8[];
extern u8 D_8014FFE0[];

/* Run the actor's eight-step sink animation, advancing its phase and swapping the sprite each step. */
void advance_eight_step_sink_animation(SinkActionWork *work, EntityRec *motion, SpriteFrameState *sprite, EntityRec *actor) {
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
        play_sound_if_enabled(0x51C);
        flags = sprite->flags;
        if (flags & 0x8000) {
            work->phase = 7;
            return;
        }
        if (!(flags & 0xE000)) {
            return;
        }
        sprite->frameTable = D_8014FFD8;
        select_sprite_entry(sprite, D_8014FFD8[((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
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
        set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
        sprite->frameTable = D_8014FFE0;
        select_sprite_entry(sprite, D_8014FFE0[((s32)(g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        work->phase++;
        return;
    case 3:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = D_8014FFD0;
        select_sprite_entry(sprite, D_8014FFD0[((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        work->phase++;
        return;
    case 7:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = D_8014FFB8;
        select_sprite_entry(sprite, D_8014FFB8[((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) - 1);
        advance_status_timers(actor);
        actor->unk_6D = 0;
        actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
        work->handler = &D_8014CF68;
        work->actionFlags = (u16) (work->actionFlags | 0x8000);
        work->recoveryTicks = (s16) ((generate_random_value() & 7) + 8);
        set_or_clear_actor_status_slot((struct Owner_800A48F0 *)(actor), 0x1A, (s8) work->recoveryTicks);
        return;
    default:
        return;
    }
}
