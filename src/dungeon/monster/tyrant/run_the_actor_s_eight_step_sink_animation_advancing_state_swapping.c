#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80173C5C_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    u8 pad_A4[0xA];
    s16 unk_AE;
} S_80173C5C_0;   /* work in run_the_actor_s_eight_step_sink_animation_advancing_state_swapping */

extern u8 D_80173FD0[];
extern u8 D_80173FB8[];
extern s32 D_80170F68;
void set_record_integer_tile_center();
s16 set_or_clear_actor_status_slot();
s32 advance_status_timers();
s32 play_sound_if_enabled();
s32 generate_random_value();
extern u8 D_80173FD8;
extern M2C_UNK D_80173FE0;

/* Run the actor's eight-step sink animation, advancing its state and swapping the sprite each step. */
void run_the_actor_s_eight_step_sink_animation_advancing_state_swapping(S_80173C5C_0 *work, EntityRec *part_a, SpriteFrameState *part_b, EntityRec *actor) {
    u8 *unused_ptr;
    s32 value;
    u16 flags;
    s32 state;
    s32 accum;
    s32 timer;

    state = work->unk_9B;
    work->unk_96.s = (u16) (work->unk_96.s - 1);
    switch (state) {
    case 0:
    case 4:
        play_sound_if_enabled(0x51C);
        flags = part_b->flags;
        if (flags & 0x8000) {
            work->unk_9B = 7;
            return;
        }
        if (!(flags & 0xE000)) {
            return;
        }
        part_b->frameTable = &D_80173FD8;
        select_sprite_entry(part_b, (&D_80173FD8)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        work->unk_98 = (u16) (work->unk_98 | 8);
        part_a->flags14 = 0xFFF00000;
        actor->flags1C = (s32) (actor->flags1C & 0xF7FFFFFF);
        work->unk_A0 = 0;
        work->unk_96.s = 10;
        work->unk_9B++;
        return;
    case 1:
    case 5:
        accum = work->unk_90;
        value = work->unk_A0;
        timer = work->unk_96.u;
        work->unk_90 = accum - value;
        if (timer != 0) {
            accum = value;
            value = part_a->flags14;
            work->unk_A0 = (s32) (accum + value);
            part_a->flags14 = (s32) (part_a->flags14 + 0x30000);
        }
        accum = work->unk_90;
        value = work->unk_A0;
        timer = work->unk_96.u;
        work->unk_90 = accum + value;
        if (timer > 0) {
            return;
        }
        work->unk_90 = 0;
        work->unk_98 = (u16) (work->unk_98 & 0xFFF7);
        actor->flags1C = (s32) (actor->flags1C | 0x8000000);
        work->unk_9B++;
        return;
    case 2:
    case 6:
        work->unk_98 = (u16) (work->unk_98 & 0xFFF7);
        part_a->flags14 = 0;
        part_a->unk_10 = 0;
        part_a->unk_0C = 0;
        set_record_integer_tile_center(part_a, part_b->unk_24, part_b->unk_25);
        part_b->frameTable = &D_80173FE0;
        select_sprite_entry(part_b, ((u8 *) ((u32) ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
            + (u32) &D_80173FE0)))[0], 0);
        work->unk_9B++;
        return;
    case 3:
        if (!(part_b->flags & 0xE000)) {
            return;
        }
        part_b->frameTable = D_80173FD0;
        select_sprite_entry(part_b, D_80173FD0[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        work->unk_9B++;
        return;
    case 7:
        if (!(part_b->flags & 0xE000)) {
            return;
        }
        part_b->frameTable = D_80173FB8;
        select_sprite_entry(part_b, D_80173FB8[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        advance_status_timers(actor);
        actor->unk_6D = 0;
        actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
        work->unk_8C = &D_80170F68;
        work->unk_98 = (u16) (work->unk_98 | 0x8000);
        work->unk_AE = (s16) ((generate_random_value() & 7) + 8);
        set_or_clear_actor_status_slot(actor, 0x1A, (s8) work->unk_AE);
        return;
    default:
        return;
    }
}
