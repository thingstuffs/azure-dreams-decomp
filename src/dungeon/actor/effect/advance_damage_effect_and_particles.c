#include "common.h"
#include "dungeon/actor/effect.h"
#include "shared/sprite_frame_state.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/actor/status.h"

typedef struct S_800CABA8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[4];
    union {
        struct { u16 pad_94; s16 ticks; } half;
        s32 word;
    } timer;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x8];
    union {
        struct { s32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_AC;   /* overlapping accesses */
    u16 unk_B0;
    u8 pad_B2[0x4];
    u16 unk_B6;
    s16 unk_B8;
} S_800CABA8_0;   /* arg0 in advance_damage_effect_and_particles */

typedef struct S_800CABA8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_800CABA8_2;

void *resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
void set_record_integer_tile_center();
#include "dungeon/actor/state.h"
#include "shared/object_node.h"
void *create_source_linked_fading_effect(ObjectNodeHeader *source, s16 copy_position);
extern u8 actor_motion_resume_address;

/* Advances the actor rotation and color effect through fading and cleanup. */
void advance_damage_effect_and_particles(void *effect, s32 context, SpriteFrameState *record, void *actor) {
    s16 fade_ticks_left;
    s16 restore_ticks;
    s16 restore_ticks_left;
    s16 next_duration;
    s32 green_result;
    s32 red_result;
    s32 green_step;
    s32 red_step;
    s32 fade_ticks;
    s32 phase_or_ticks;
    s32 blue_step;
    s32 rotation_done;
    u16 effect_level;
    u16 cycles_left;
    u16 flags;
    u8 fade_blue;
    s32 restore_blue;
    s32 fade_green;
    s32 restore_green;
    u8 red;
    u8 red_2;
    u8 phase;
    void *effect_base;
    void *actor_state;
    void *actor_or_green;
    void *actor_or_green_2;

    actor_or_green_2 = actor;
    phase = ((S_800CABA8_0 *)effect)->unk_9B;
    actor_state = actor_or_green_2;
    switch (phase) {
    case 0:
        ((S_800CABA8_0 *)effect)->unk_B8 = 1;
        if (record->flags & 0x8000) {
            resolve_attack_damage_and_effects(actor_state, record, ((S_800CABA8_2 *)actor_state)->unk_2A, 0);
            ((S_800CABA8_0 *)effect)->unk_9B = 4U;
            return;
        }
        ((S_800CABA8_0 *)effect)->unk_B0 = (u16) ((S_800CABA8_2 *)actor_state)->unk_2A;
        ((S_800CABA8_0 *)effect)->unk_9B = (u8) (((S_800CABA8_0 *)effect)->unk_9B + 1);
    case 1:
        ((S_800CABA8_0 *)effect)->unk_98 |= 8;
        effect_level = ((S_800CABA8_0 *)effect)->unk_A0.at02.v + 0x10;
        ((S_800CABA8_0 *)effect)->unk_A0.at02.v = effect_level;
        if ((s16) effect_level < 0x81) {
            return;
        }
        phase_or_ticks = 0x80U;
        ((S_800CABA8_0 *)effect)->unk_A0.at02.v = phase_or_ticks;
        phase_or_ticks = ((S_800CABA8_0 *)effect)->unk_9B;
        next_duration = 8;
        ((S_800CABA8_0 *)effect)->timer.half.ticks = next_duration;
        ((S_800CABA8_0 *)effect)->unk_9B = (u8) (phase_or_ticks + 1);
        return;
    case 2:
        effect_base = effect - 0x20;
        ((S_800CABA8_0 *)effect)->unk_A0.at00.v = (s32) (((S_800CABA8_0 *)effect)->unk_A0.at00.v
            - (((S_800CABA8_0 *)effect)->unk_A0.at00.v / (s16) ((S_800CABA8_0 *)effect)->timer.half.ticks));
        spawn_salam_particles(effect_base, ((S_800CABA8_2 *)actor_state)->unk_2A, ((S_800CABA8_0 *)effect)->unk_AC.at00.v);
        create_source_linked_fading_effect(effect_base, 1);
        red_2 = (u8) ((S_800CABA8_0 *)effect)->unk_AC.at00.v;
        red_step = (s32) (0xE0 - red_2) / (s16) ((S_800CABA8_0 *)effect)->timer.half.ticks;
        fade_green = ((S_800CABA8_0 *)effect)->unk_AC.at01.v;
        fade_ticks = ((S_800CABA8_0 *)effect)->timer.word >> 16;
        green_step = (s32) (8 - fade_green) / fade_ticks;
        green_result = fade_green + green_step;
        red_result = red_2 + red_step;
        ((S_800CABA8_0 *)effect)->unk_AC.at00u.v = (u8)red_result;
        fade_blue = ((S_800CABA8_0 *)effect)->unk_AC.at02.v;
        blue_step = (s32) (8 - fade_blue) / (s16) ((S_800CABA8_0 *)effect)->timer.half.ticks;
        ((S_800CABA8_0 *)effect)->unk_AC.at01.v = (u8)green_result;
        fade_ticks_left = (u16) ((S_800CABA8_0 *)effect)->timer.half.ticks - 1;
        ((S_800CABA8_0 *)effect)->timer.half.ticks = fade_ticks_left;
        ((S_800CABA8_0 *)effect)->unk_AC.at02.v = (u8) (fade_blue + blue_step);
        if ((fade_ticks_left << 0x10) > 0) {
            return;
        }
        resolve_attack_damage_and_effects(actor_state, record, ((S_800CABA8_2 *)actor_state)->unk_2A, 0);
        phase_or_ticks = ((S_800CABA8_0 *)effect)->unk_9B;
        next_duration = 4;
        ((S_800CABA8_0 *)effect)->timer.half.ticks = next_duration;

        ((S_800CABA8_0 *)effect)->unk_9B = (u8) (phase_or_ticks + 1);
        return;
    case 3:
        if ((s16) ((S_800CABA8_0 *)effect)->unk_B0 != ((S_800CABA8_2 *)actor_state)->unk_2A) {
            ((S_800CABA8_2 *)actor_state)->unk_2A = (s16) ((u16) ((S_800CABA8_2 *)actor_state)->unk_2A + 0x200);
            rotation_done = 0;
        } else {
            rotation_done = 1;
        }
        restore_ticks = ((S_800CABA8_0 *)effect)->timer.half.ticks;
        if (restore_ticks > 0) {
            red = (u8) ((S_800CABA8_0 *)effect)->unk_AC.at00.v;
            restore_green = ((S_800CABA8_0 *)effect)->unk_AC.at01.v;
            restore_blue = ((S_800CABA8_0 *)effect)->unk_AC.at02.v;
            ((S_800CABA8_0 *)effect)->unk_AC.at00u.v = (u8) (red + ((s32) (0x40 - red) / restore_ticks));
            actor_or_green = restore_green + ((s32) (0x40
                - restore_green) / (s16) ((S_800CABA8_0 *)effect)->timer.half.ticks);
            ((S_800CABA8_0 *)effect)->unk_AC.at01.v = (u8) actor_or_green;
            ((S_800CABA8_0 *)effect)->unk_AC.at02.v = (u8) (restore_blue + ((s32) (0x40
                - restore_blue) / (s16) ((S_800CABA8_0 *)effect)->timer.half.ticks));
        } else {
            ((S_800CABA8_0 *)effect)->timer.half.ticks = 0;
        }
        phase_or_ticks = (u16) ((S_800CABA8_0 *)effect)->timer.half.ticks;
        restore_ticks_left = phase_or_ticks - 1;
        phase_or_ticks = rotation_done;
        ((S_800CABA8_0 *)effect)->timer.half.ticks = restore_ticks_left;
        if (phase_or_ticks == 0) {
            return;
        }
        phase_or_ticks = restore_ticks_left << 0x10;
        if (phase_or_ticks > 0) {
            return;
        }
        ((S_800CABA8_0 *)effect)->unk_98 = (u16) (((S_800CABA8_0 *)effect)->unk_98 & 0xFFF7);
        ((S_800CABA8_0 *)effect)->unk_9B = (u8) (((S_800CABA8_0 *)effect)->unk_9B + 1);
    case 4:
        ((S_800CABA8_0 *)effect)->unk_A0.at02.v = 0U;
        set_record_integer_tile_center(context, record->tile_x, record->tile_y);
        g_dungeon_status.active_actor = 0;
        ((S_800CABA8_2 *)actor_state)->unk_46 = (u16) ((((S_800CABA8_2 *)actor_state)->unk_46) & 0x7FFF);
        advance_status_timers(actor_state);
        cycles_left = ((S_800CABA8_0 *)effect)->unk_B6 - 1;
        ((S_800CABA8_0 *)effect)->unk_B6 = cycles_left;
        if ((cycles_left << 0x10) <= 0 || ((*(u16 *)0x80013714) & 8)) {
            set_actor_action_state_eight(effect, context, record);
        } else {
            ((S_800CABA8_0 *)effect)->unk_8C = &actor_motion_resume_address;
        }
        return;
    default:
        return;
    }
}
