#include "common.h"
#include "shared/object_node.h"
#include "dungeon/monster/kewne_uncached.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"
#include "sdk/libgte.h"

extern void func_801753DC(void *, void *);

extern s32 kewne_uncached_action_resume_address;
extern u8 D_80175C48[];
extern u8 D_80175C50[];
extern u8 D_80175C58[];


/* Updates jump movement, animation, and landing across five states. */
/* Animates Kewne's backward windup and arcing strike, applies damage at tick 10, then returns to its tile
 * and spends MP. */
void update_jump_movement_and_landing(ActorRecord *jump, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u32 step_x;
    s32 step_y;
    u8 state;

    state = jump->action_phase;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        {
            if (sprite->flags & 0x8000) {
                jump->action_phase = 4;
                sprite->flags |= 0x6000;
                resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
                return;
            }
        }

        motion->velocity_x -=
            dir_step_x[((u16)actor->facing >> 9) & 7] << 14;
        motion->velocity_y -=
            dir_step_y[((u16)actor->facing >> 9) & 7] << 14;
        jump->unk_A0.value += 0x60000;
        if (jump->unk_A0.parts.high >= 0x31) {
            jump->unk_A0.parts.high = 0x30;
        }
        if (!(sprite->flags & 0x6000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        if (jump->unk_A0.parts.high < 0x30) {
            return;
        }
        sprite->frameTable = D_80175C48;
        select_sprite_entry(sprite,
            D_80175C48[((g_game_work.view.camera_rotation.parts.viewAngle + ((s16)actor->facing) + 0x100) >> 9) & 7],
            0);
        func_801753DC(NODE_HEADER(jump), &actor->facing);
        state = jump->action_phase;
        jump->action_timer = 0;
        jump->action_phase = state + 1;
        return;

    case 1:
        {
            s16 *x_table;
            s16 *y_table;
            s16 *x_entry;
            s16 *y_entry;
            s32 arc;
            s16 timer;

            x_table = (s16 *)((s8 *)dir_step_x);
            y_entry = (s16 *)(((u16)actor->facing >> 8) & 0xE);
            x_entry = (s16 *)((s32)y_entry + (u8 *)x_table);
            y_table = (s16 *)((s8 *)dir_step_y);
            y_entry = (s16 *)((s32)y_entry + (u8 *)y_table);
            arc = *x_entry;
            y_entry = (s16 *)(*y_entry);
            step_x = arc << 16;
            step_y = (s32)y_entry << 16;
            motion->velocity_x += step_x;
            motion->velocity_y += step_y;
            arc = -rsin((jump->action_timer) * 170);
            jump->unk_A0.value = ((arc * 5) << 8) + 0x300000;
            timer = jump->action_timer + 1;
            jump->action_timer = timer;
            if (timer < 9) {
                return;
            }
        }
        sprite->frameTable = D_80175C50;
        select_sprite_entry(sprite,
            D_80175C50[((g_game_work.view.camera_rotation.parts.viewAngle + ((s16)actor->facing) + 0x100) >> 9) & 7],
            0);
        play_sound_if_enabled(0x808);
        state = jump->action_phase;
        jump->action_phase = state + 1;
        return;

    case 2:
        {
            s16 *x_table;
            s16 *y_table;
            s16 *x_entry;
            s16 *y_entry;
            s32 arc;
            s32 direction_x;
            s32 dir_offset;
            s16 timer;
            s32 velocity_x;
            s32 velocity_y;

            if ((*(s16 *)((u8 *)jump + 0x96)) == 10) {
                resolve_attack_damage_and_effects(actor, sprite, ((s16)actor->facing), 1);
            }
            x_table = (s16 *)((s8 *)dir_step_x);
            dir_offset = ((u16)actor->facing >> 8) & 0xE;
            x_entry = (s16 *)(dir_offset + (u8 *)x_table);
            y_table = (s16 *)((s8 *)dir_step_y);
            y_entry = (s16 *)(dir_offset + (u8 *)y_table);
            direction_x = *x_entry;
            arc = *y_entry;
            step_x = direction_x << 16;
            step_y = arc << 16;
            motion->velocity_x += step_x;
            motion->velocity_y += step_y;
            arc = -rsin((jump->action_timer) * 170);
            jump->unk_A0.value = ((arc * 5) << 8) + 0x300000;
            timer = jump->action_timer + 1;
            jump->action_timer = timer;
            if (timer < 13) {
                return;
            }
            sprite->frameTable = D_80175C58;
            select_sprite_entry(sprite,
                D_80175C58[((g_game_work.view.camera_rotation.parts.viewAngle + ((s16)actor->facing) + 0x100) >> 9) & 7],
                0);

            velocity_x = -*(s16 *)((u8 *)x_table +
                (((u16)actor->facing >> 8) & 0xE)) << 18;
            velocity_x += velocity_x >> 2;
            motion->velocity_x = velocity_x;

            velocity_y = -*(s16 *)((u8 *)y_table +
                (((u16)actor->facing >> 8) & 0xE)) << 18;
            velocity_y += velocity_y >> 2;
            motion->velocity_y = velocity_y;
            (*(s32 *)&jump->unk_A8) = motion->velocity_x / 24;
            jump->unk_AC.value = motion->velocity_y / 24;
        }
        jump->action_timer = 12;
        jump->action_phase++;
        return;

    case 3:
        motion->velocity_x -= (*(s32 *)&jump->unk_A8);
        motion->velocity_y -= jump->unk_AC.value;
        if (jump->unk_A0.parts.high > 0) {
            jump->unk_A0.parts.high -= 0x10;
        } else {
            jump->unk_A0.parts.high = 0;
        }
    case 4:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 0x100);
        jump->unk_8C.word_ptr = &kewne_uncached_action_resume_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        actor->action_flags &= 0x7FFF;
    }
}
