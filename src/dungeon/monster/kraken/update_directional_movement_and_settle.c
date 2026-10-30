#include "common.h"
#include "dungeon/monster/kraken.h"
#include "shared/actor_action_flags.h"
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

typedef struct S_801724F4_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801724F4_1;   /* arg0 in update_directional_movement_and_settle */

extern void *actor_update_node_cursor;
extern s32 kraken_action_resume_address;
extern u8 D_8017419C[];
extern u8 kraken_frame_set_4[];

/* Updates directional movement and animation, then settles the actor on its destination tile. */
void update_directional_movement_and_settle(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 dir_x;
    s32 dir_y;
    s32 dir_offset;
    s32 ticks_left;
    s32 state;

    dir_offset = ((u16)((u16)actor->facing) >> 8) & 0xE;
    dir_x = *(s16 *)((u8 *)((s8 *)dir_step_x) + dir_offset);
    dir_y = *(s16 *)((u8 *)((s8 *)dir_step_y) + dir_offset);
    state = action->action_phase.u;
    ticks_left = action->action_timer.u - 1;
    action->action_timer.u = ticks_left;

    switch (state) {
    case 0:
        if (sprite->flags & 0x8000) {
            action->action_phase.u = 0xFF;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        sprite->frameTable = D_8017419C;
        select_sprite_entry(sprite,
            D_8017419C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->action_phase.u++;
        return;
    case 1:
        if (sprite->flags & 0xE000) {
            sprite->frameTable = kraken_frame_set_4;
            select_sprite_entry(sprite,
                kraken_frame_set_4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            motion->velocity_x = (dir_x << 18) + (dir_x << 17);
            motion->velocity_y = (dir_y << 18) + (dir_y << 17);
            action->action_timer.u = 8;
            play_sound_if_enabled(0x607);
            action->action_phase.u++;
        }
        return;
    case 2:
        if ((ticks_left << 16) <= 0) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            action->action_phase.u = 0xFF;
        }
        return;
    case 0xFF:
    {
        s32 target_x = sprite->tile_x << 6;
        s32 current_x = motion->x.w.i - 0x20;
        motion->velocity_x = ((target_x - current_x) << 0xF) >> 1;
    }
        {
            s32 target_y = sprite->tile_y << 6;
            s32 current_y = motion->y.w.i - 0x20;
            motion->velocity_y = ((target_y - current_y) << 0xF) >> 1;
        }
        if (sprite->flags & 0xE000) {
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            (*(u32 *)&actor->flags1C) |= 0x40000;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            spend_actor_mp(actor, 0x100);
            action->unk_8C.address = &kraken_action_resume_address;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            if (actor->pending_turn_updates == 0) {
                actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
            } else {
                actor_update_node_cursor = (u8 *)actor - 0x20;
            }
        }
    }
}
