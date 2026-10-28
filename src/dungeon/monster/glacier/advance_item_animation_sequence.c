#include "common.h"
#include "dungeon/monster/glacier.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor/status.h"
extern u8 resident_globals_page[];

typedef struct S_80172F04_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172F04_0;   /* arg0 in advance_item_animation_sequence */

typedef struct S_80172F04_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172F04_2;   /* actor in advance_item_animation_sequence */

typedef struct S_80172F04_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172F04_3;   /* arg1 in advance_item_animation_sequence */

typedef struct S_80172F04_4 {
    u8 unk_00;
    u8 pad_01[0x3227];
    s16 unk_3228;
    u8 pad_322A[0x242];
    s32 unk_346C;
} S_80172F04_4;   /* (u8 *)work in advance_item_animation_sequence */

extern void select_sprite_entry(void *, u8, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

extern u8 D_801760CC[];

/* Advances a timed actor animation sequence and resets its action on completion. */
void advance_item_animation_sequence(S_80172F04_0 *action, S_80172F04_3 *motion, SpriteFrameState *animation, void *actor_ptr)
{
    S_80172F04_2 *actor;
    s32 state;
    u8 current_state;
    u16 timer;
    u32 work;
    void *call_actor;

    state = action->unk_9B;
    actor = actor_ptr;
    switch (state) {
    case 0:
        if (animation->flags & 0x8000) {
            action->unk_9B = 3;
            animation->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, animation, actor->unk_2A, 1);
            return;
        }
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        current_state = action->unk_9B;
        action->unk_96 = 0;
        action->unk_9B = current_state + 1;
        return;
    case 1:
        timer = action->unk_96 + 1;
        action->unk_96 = timer;
        if (((s16)timer == 4) || (animation->flags & 0x8000)) {
            animation->frameTable = D_801760CC;
            work = g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100;
            work = ((s32)work >> 9) & 7;
            work += (u32)D_801760CC;
            select_sprite_entry(animation,
                ((S_80172F04_4 *)((u8 *)work))->unk_00,
                0);
            play_sound_if_enabled(0x809);
            current_state = action->unk_9B;
            action->unk_96 = 0;
            action->unk_9B = current_state + 1;
            return;
        }
        return;
    case 2:
        timer = action->unk_96 + 1;
        action->unk_96 = timer;
        if (((s16)timer == 4) || (animation->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, animation, actor->unk_2A, 1);
            current_state = action->unk_9B;
            action->unk_96 = 0;
            action->unk_9B = current_state + 1;
            return;
        }
        return;
    case 3:
        if (animation->flags & 0xE000) {
            spend_actor_mp(actor, 0x140);
            call_actor = actor;
            action->unk_8C = (u8 *)(update_actor_timed_effects);
            ((S_80172F04_4 *)resident_globals_page)->unk_346C = 0;
            advance_status_timers(call_actor);
            actor->unk_46 &= 0x7FFF;
        }
        return;
    default:
        return;
    }
}
